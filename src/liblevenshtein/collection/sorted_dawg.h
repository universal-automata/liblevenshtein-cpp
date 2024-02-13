#ifndef LIBLEVENSHTEIN_COLLECTION_SORTED_DAWG_H
#define LIBLEVENSHTEIN_COLLECTION_SORTED_DAWG_H

#include <stack>
#include <unordered_map>
#include <unordered_set>

#include "liblevenshtein/collection/dawg.h"
#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/collection/transition.h"

namespace liblevenshtein {

  class SortedDawg : public Dawg {
  public:
    using Dawg::Dawg;
    ~SortedDawg() override;

    auto add(const std::string &term) -> bool override;
    auto remove(const std::string &term) -> bool override;

    void init();
    void clean_up();

    void finish();
    void minimize(std::size_t lower_bound);
    auto minimized_node(DawgNode *key) const -> DawgNode *;

  private:
    std::stack<Transition> *unchecked_transitions = nullptr;
    std::unordered_map<DawgNode, DawgNode *> *minimized_nodes = nullptr;
    std::unordered_set<DawgNode *> *floating_nodes = nullptr;
    std::string _prev_term;
  };

  template <class IterType>
  auto sorted_dawg(IterType iter, IterType end) -> SortedDawg *;
} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_COLLECTION_SORTED_DAWG_H
