#ifndef __LIBLEVENSHTEIN__SERIALIZATION__SERIALIZER_H__
#define __LIBLEVENSHTEIN__SERIALIZATION__SERIALIZER_H__

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

bool serialize_protobuf(Dawg *dawg, const fs::path &path);
bool serialize_protobuf(Dawg *dawg, const std::string &path);
bool serialize_protobuf(Dawg *dawg, const char *path);
bool serialize_protobuf(Dawg *dawg, std::ostream &output);

Dawg *deserialize_protobuf(const fs::path &path);
Dawg *deserialize_protobuf(const std::string &path);
Dawg *deserialize_protobuf(const char *path);
Dawg *deserialize_protobuf(std::istream &input);

void collect_nodes(DawgNode *dawg_node, std::set<uint64_t> &node_ids,
                   std::set<uint64_t> &final_node_ids);
void collect_edges(DawgNode *dawg_node, std::map<std::pair<uint64_t, char>, uint64_t> &edges);

llp::Dictionary *to_protobuf(Dawg *dawg);
Dawg *from_protobuf(const llp::Dictionary &dict_proto);

} // namespace liblevenshtein

#endif // __LIBLEVENSHTEIN__SERIALIZATION__SERIALIZER_H__
