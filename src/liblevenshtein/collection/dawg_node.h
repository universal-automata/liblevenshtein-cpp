#ifndef LIBLEVENSHTEIN_COLLECTION_DAWG_NODE_H
#define LIBLEVENSHTEIN_COLLECTION_DAWG_NODE_H

#include <functional>
#include <map>


namespace liblevenshtein {

  class DawgNode {
  public:
    DawgNode(bool is_final = false);
    DawgNode(std::map<char, DawgNode *>& edges, bool is_final=false);

    void is_final(bool is_final);
    [[nodiscard]] auto is_final() const -> bool;

    void for_each_edge(const std::function<void(char, DawgNode *)> &fn) const;

    [[nodiscard]] auto transition(char label) const -> DawgNode *;
    auto add_edge(char label, DawgNode *target) -> DawgNode *;

    auto operator==(const DawgNode &other) const -> bool;
    auto operator!=(const DawgNode &other) const -> bool;

  private:
    std::map<char, DawgNode *> _edges;
    bool _is_final = false;
  };
}

namespace std {

  template <>
  struct hash<liblevenshtein::DawgNode> {
    auto operator()(const liblevenshtein::DawgNode &node) const -> size_t;
  };
} // namespace std

#endif // LIBLEVENSHTEIN_COLLECTION_DAWG_NODE_H
