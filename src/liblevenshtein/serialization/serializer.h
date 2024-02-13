#ifndef LIBLEVENSHTEIN_SERIALIZATION_SERIALIZER_H
#define LIBLEVENSHTEIN_SERIALIZATION_SERIALIZER_H

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <map>
#include <set>
#include <utility>

#include "liblevenshtein/collection/dawg.h"
#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/proto/liblevenshtein.pb.h"

namespace fs = std::filesystem;

namespace llp = liblevenshtein::proto;

namespace liblevenshtein {

auto serialize_protobuf(Dawg *dawg, const fs::path &path) -> bool;
auto serialize_protobuf(Dawg *dawg, const std::string &path) -> bool;
auto serialize_protobuf(Dawg *dawg, const char *path) -> bool;
auto serialize_protobuf(Dawg *dawg, std::ostream &output) -> bool;

auto deserialize_protobuf(const fs::path &path) -> Dawg *;
auto deserialize_protobuf(const std::string &path) -> Dawg *;
auto deserialize_protobuf(const char *path) -> Dawg *;
auto deserialize_protobuf(std::istream &input) -> Dawg *;

void collect_nodes(DawgNode *source, std::set<uint64_t> &node_ids,
                   std::set<uint64_t> &final_node_ids);
void collect_edges(DawgNode *source,
                   std::map<std::pair<uint64_t, char>, uint64_t> &edges);

auto to_protobuf(Dawg *dawg) -> llp::Dictionary *;
auto from_protobuf(const llp::Dictionary &dict_proto) -> Dawg *;

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_SERIALIZATION_SERIALIZER_H
