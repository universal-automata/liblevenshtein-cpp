#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <utility>

#include "liblevenshtein/collection/dawg.h"
#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/collection/sorted_dawg.h"
#include "liblevenshtein/proto/liblevenshtein.pb.h"
#include "liblevenshtein/serialization/serializer.h"

namespace fs = std::filesystem;

namespace llp = liblevenshtein::proto;

namespace liblevenshtein {

#if _MSC_VER && !__INTEL_COMPILER
#pragma warning(push)
#pragma warning(disable : 4717)
#endif

auto serialize_protobuf(Dawg *dawg, const fs::path &path) -> bool {
  return serialize_protobuf(dawg, path.c_str());
}

auto serialize_protobuf(Dawg *dawg, const std::string &path) -> bool {
  return serialize_protobuf(dawg, path.c_str());
}

auto serialize_protobuf(Dawg *dawg, const char *path) -> bool {
  std::fstream output(path, std::fstream::out | std::fstream::trunc |
                                std::fstream::binary);
  bool serialized = serialize_protobuf(dawg, output);
  output.close();
  return serialized;
}

auto serialize_protobuf(Dawg *dawg, std::ostream &output) -> bool {
  llp::Dictionary *dict_proto = to_protobuf(dawg);
  bool serialized = dict_proto->SerializeToOstream(&output);
  delete dict_proto;
  return serialized;
}

auto deserialize_protobuf(const fs::path &path) -> Dawg * {
  return deserialize_protobuf(path.c_str());
}

auto deserialize_protobuf(const std::string &path) -> Dawg * {
  return deserialize_protobuf(path.c_str());
}

auto deserialize_protobuf(const char *path) -> Dawg * {
  std::fstream input(path, std::fstream::in | std::fstream::binary);
  Dawg *dawg = deserialize_protobuf(input);
  input.close();
  return dawg;
}

auto deserialize_protobuf(std::istream &input) -> Dawg * {
  Dawg *dawg = nullptr;
  llp::Dictionary dict_proto;
  if (dict_proto.ParseFromIstream(&input)) {
    dawg = from_protobuf(dict_proto);
  }
  return dawg;
}

#if _MSC_VER && !__INTEL_COMPILER
#pragma warning(pop)
#endif

void collect_nodes(DawgNode *source, std::set<uint64_t> &node_ids,
                   std::set<uint64_t> &final_node_ids) {
  auto source_id = reinterpret_cast<uint64_t>(source);
  if (!node_ids.contains(source_id)) {
    node_ids.insert(source_id);
    if (source->is_final()) {
      final_node_ids.insert(source_id);
    }
    source->for_each_edge([&](char label, DawgNode *target) {
      collect_nodes(target, node_ids, final_node_ids);
    });
  }
}

void collect_edges(DawgNode *source,
                   std::map<std::pair<uint64_t, char>, uint64_t> &edges) {
  auto source_id = reinterpret_cast<uint64_t>(source);
  source->for_each_edge([&](char label, DawgNode *target) {
    std::pair<uint64_t, char> key = std::make_pair(source_id, label);
    if (!edges.contains(key)) {
      auto target_id = reinterpret_cast<uint64_t>(target);
      edges[key] = target_id;
      collect_edges(target, edges);
    }
  });
}

auto to_protobuf(Dawg *dawg) -> llp::Dictionary * {
  auto *dict_proto = new llp::Dictionary();
  DawgNode *root = dawg->root();

  std::set<uint64_t> node_ids;
  std::set<uint64_t> final_node_ids;
  collect_nodes(root, node_ids, final_node_ids);
  for (const uint64_t &node_id : node_ids) {
    dict_proto->add_node_id(node_id);
  }
  for (const uint64_t &final_node_id : final_node_ids) {
    dict_proto->add_final_node_id(final_node_id);
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

  auto root_id = reinterpret_cast<uint64_t>(root);
  dict_proto->set_root_id(root_id);
  dict_proto->set_size(dawg->size());

  return dict_proto;
}

auto from_protobuf(const llp::Dictionary &dict_proto) -> Dawg * {
  std::set<uint64_t> final_node_ids;
  for (int index = 0; index < dict_proto.final_node_id_size(); index += 1) {
    uint64_t final_node_id = dict_proto.final_node_id(index);
    final_node_ids.insert(final_node_id);
  }

  std::map<uint64_t, DawgNode *> nodes;
  for (int index = 0; index < dict_proto.node_id_size(); index += 1) {
    uint64_t node_id = dict_proto.node_id(index);
    if (!nodes.contains(node_id)) {
      bool is_final = final_node_ids.contains(node_id);
      auto *node = new DawgNode(is_final);
      nodes[node_id] = node;
    }
  }

  for (int index = 0; index < dict_proto.edge_size(); index += 1) {
    const llp::Dictionary_Edge &edge_proto = dict_proto.edge(index);
    uint64_t source_id = edge_proto.source_id();
    char label = (char)edge_proto.label();
    uint64_t target_id = edge_proto.target_id();
    DawgNode *source = nodes[source_id];
    DawgNode *target = nodes[target_id];
    source->add_edge(label, target);
  }

  DawgNode *root = nodes[dict_proto.root_id()];
  auto *dawg = new SortedDawg(root, dict_proto.size());
  return dawg;
}

} // namespace liblevenshtein
