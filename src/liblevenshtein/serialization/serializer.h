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

/**
 * Serializes the given Dawg to protobuf at the given path.
 *
 * @param dawg Dawg to serialize.
 * @param path Path to the serialization file.
 * @return Whether the Dawg was successfully serialized to the given path.
 */
auto serialize_protobuf(Dawg *dawg, const fs::path &path) -> bool;

/**
 * Serializes the given Dawg to protobuf at the given path.
 *
 * @param dawg Dawg to serialize.
 * @param path Path to the serialization file.
 * @return Whether the Dawg was successfully serialized to the given path.
 */
auto serialize_protobuf(Dawg *dawg, const std::string &path) -> bool;

/**
 * Serializes the given Dawg to protobuf at the given path.
 *
 * @param dawg Dawg to serialize.
 * @param path Path to the serialization file.
 * @return Whether the Dawg was successfully serialized to the given path.
 */
auto serialize_protobuf(Dawg *dawg, const char *path) -> bool;

/**
 * Serializes the given Dawg to protobuf into the given output stream.
 *
 * @param dawg Dawg to serialize.
 * @param output Output stream to write the serialized protobuf.
 * @return Whether the Dawg was successfully serialized to the output stream.
 */
auto serialize_protobuf(Dawg *dawg, std::ostream &output) -> bool;

/**
 * Deserializes the protobuf containing a Dawg at the given path or returns
 * nullptr if none exists.
 *
 * @param path Path to the serialization file.
 * @return The deserialized Dawg or nullptr if none exists.
 */
auto deserialize_protobuf(const fs::path &path) -> Dawg *;

/**
 * Deserializes the protobuf containing a Dawg at the given path or returns
 * nullptr if none exists.
 *
 * @param path Path to the serialization file.
 * @return The deserialized Dawg or nullptr if none exists.
 */
auto deserialize_protobuf(const std::string &path) -> Dawg *;

/**
 * Deserializes the protobuf containing a Dawg at the given path or returns
 * nullptr if none exists.
 *
 * @param path Path to the serialization file.
 * @return A pointer to the deserialized Dawg or nullptr if none exists.
 */
auto deserialize_protobuf(const char *path) -> Dawg *;

/**
 * Deserializes the protobuf containing a Dawg from the given input stream or
 * returns nullptr if none exists.
 *
 * @param path input Input stream containing the serialized Dawg.
 * @return A pointer to the deserialized Dawg or nullptr if none exists.
 */
auto deserialize_protobuf(std::istream &input) -> Dawg *;

/**
 * Collects the DawgNode IDs and final DawgNode IDs of all nodes reachable from
 * the source.
 *
 * @param source DawgNode whose ID is to be collected.
 * @param node_ids DawgNode IDs reachable from the source.
 * @param final_node_ids Final DawgNode IDs reachable from the source.
 */
void collect_nodes(DawgNode *source, std::set<uint64_t> &node_ids,
                   std::set<uint64_t> &final_node_ids);

/**
 * Collects the transitions from each source to its destination, and the
 * respective character labels.
 *
 * @param source Initial node for the transition.
 * @param edges Transition mapping of source DawgNode IDs and labels to their
 * respective target DawgNode IDs.
 */
void collect_edges(DawgNode *source,
                   std::map<std::pair<uint64_t, char>, uint64_t> &edges);

/**
 * Serializes a Dawg to its protobuf equivalent.
 *
 * @param dawg Dawg to serialize.
 * @return A pointer to the serialized Dawg.
 */
auto to_protobuf(Dawg *dawg) -> llp::Dictionary *;

/**
 * Deserializes a Dawg from its protobuf equivalent.
 *
 * @param dict_proto Protobuf containing the serialized information necessary
 * for reconstructing the Dawg.
 * @return A pointer to the deserialized Dawg.
 */
auto from_protobuf(const llp::Dictionary &dict_proto) -> Dawg *;

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_SERIALIZATION_SERIALIZER_H
