#ifndef LIBLEVENSHTEIN_COLLECTION_DAWG_ITERATOR_H
#define LIBLEVENSHTEIN_COLLECTION_DAWG_ITERATOR_H

#include <queue>
#include <vector>

#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/collection/prefix.h"

namespace liblevenshtein {

  class DawgIterator {
  public:
    DawgIterator(DawgNode* root);
    DawgIterator(std::size_t term_index);
    ~DawgIterator();

    auto operator++() -> DawgIterator &;
    auto operator*() const -> std::string;
    auto operator!=(const DawgIterator &other) const -> bool;

  private:
    std::vector<Prefix *> _prefixes;
    std::queue<Prefix *> _pending;
    std::string _next_value;
    std::size_t _term_index = 0;

    void advance();
  };
} // namespace DawgIterator


#endif // LIBLEVENSHTEIN_COLLECTION_DAWG_ITERATOR_H
