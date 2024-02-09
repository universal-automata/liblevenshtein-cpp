#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <utility>

#include "liblevenshtein/collection/dawg.h"
#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/collection/sorted_dawg.h"
#include "liblevenshtein/proto/liblevenshtein.pb.h"
#include "liblevenshtein/serialization/serializer.h"

namespace fs = std::filesystem;

namespace llp = liblevenshtein::proto;

namespace liblevenshtein {

bool serialize_protobuf(Dawg *dawg, const fs::path &path) {
    return serialize_protobuf(dawg, path.c_str());
}

bool serialize_protobuf(Dawg *dawg, const std::string &path) {
    return serialize_protobuf(dawg, path.c_str());
}

bool serialize_protobuf(Dawg *dawg, const char *path) {
    std::fstream output(path, std::fstream::out | std::fstream::trunc |
                                  std::fstream::binary);
    bool serialized = serialize_protobuf(dawg, output);
    output.close();
    return serialized;
}

bool serialize_protobuf(Dawg *dawg, std::ostream &output) {
    llp::Dictionary *dict_proto = to_protobuf(dawg);
    bool serialized = dict_proto->SerializeToOstream(&output);
    delete dict_proto;
    return serialized;
}

Dawg *deserialize_protobuf(const fs::path &path) {
    return deserialize_protobuf(path.c_str());
}

Dawg *deserialize_protobuf(const std::string &path) {
    return deserialize_protobuf(path.c_str());
}

Dawg *deserialize_protobuf(const char *path) {
    std::fstream input(path, std::fstream::in | std::fstream::binary);
    Dawg *dawg = deserialize_protobuf(input);
    input.close();
    return dawg;
}

Dawg *deserialize_protobuf(std::istream &input) {
    Dawg *dawg = nullptr;
    llp::Dictionary dict_proto;
    if (dict_proto.ParseFromIstream(&input)) {
        dawg = from_protobuf(dict_proto);
    }
    return dawg;
}

void collect_nodes(DawgNode *source, std::map<uint64_t, bool> &nodes) {
    uint64_t source_id = reinterpret_cast<uint64_t>(source);
    if (!nodes.contains(source_id)) {
        nodes[source_id] = source->is_final();
        source->for_each_edge([&](char label, DawgNode *target) {
            collect_nodes(target, nodes);
        });
    }
}

void collect_edges(DawgNode *source,
                   std::map<std::pair<uint64_t, char>, uint64_t> &edges) {
    uint64_t source_id = reinterpret_cast<uint64_t>(source);
    source->for_each_edge([&](char label, DawgNode *target) {
        std::pair<uint64_t, char> key = std::make_pair(source_id, label);
        uint64_t target_id = reinterpret_cast<uint64_t>(target);
        edges[key] = target_id;
        collect_edges(target, edges);
    });
}

llp::Dictionary *to_protobuf(Dawg *dawg){
    llp::Dictionary *dict_proto = new llp::Dictionary();
    DawgNode *root = dawg->root();

    std::map<uint64_t, bool> nodes;
    collect_nodes(root, nodes);
    for (const auto &node : nodes) {
        llp::Dictionary_Node *node_proto = dict_proto->add_node();
        node_proto->set_id(node.first);
        node_proto->set_is_final(node.second);
    }

    std::map<std::pair<uint64_t, char>, uint64_t> edges;
    collect_edges(root, edges);
    for (const auto &edge : edges) {
        uint64_t source_id = edge.first.first;
        char label = edge.first.second;
        uint64_t target_id = edge.second;
        llp::Dictionary_Edge *edge_proto = dict_proto->add_edge();
        edge_proto->set_source_id(source_id);
        edge_proto->set_label(label);
        edge_proto->set_target_id(target_id);
    }

    uint64_t root_id = reinterpret_cast<uint64_t>(root);
    dict_proto->set_root_id(root_id);
    dict_proto->set_size(dawg->size());

    return dict_proto;
}

Dawg *from_protobuf(const llp::Dictionary &dict_proto) {
    std::map<uint64_t, DawgNode*> nodes;
    for (int index = 0; index < dict_proto.node_size(); index += 1) {
        const llp::Dictionary_Node &node_proto = dict_proto.node(index);
        uint64_t node_id = node_proto.id();
        if (!nodes.contains(node_id)) {
            DawgNode *node = new DawgNode(node_proto.is_final());
            nodes[node_id] = node;
        }
    }

    for (int index = 0; index < dict_proto.edge_size(); index += 1) {
        const llp::Dictionary_Edge &edge_proto = dict_proto.edge(index);
        uint64_t source_id = edge_proto.source_id();
        char label = edge_proto.label();
        uint64_t target_id = edge_proto.target_id();
        DawgNode *source = nodes[source_id];
        DawgNode *target = nodes[target_id];
        source->add_edge(label, target);
    }

    DawgNode *root = nodes[dict_proto.root_id()];
    Dawg *dawg = new SortedDawg(root, dict_proto.size());
    return dawg;
}

} // namespace liblevenshtein
