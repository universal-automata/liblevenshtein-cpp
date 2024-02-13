#ifndef LIBLEVENSHTEIN_TRANSDUCER_STATE_H
#define LIBLEVENSHTEIN_TRANSDUCER_STATE_H

#include <functional>
#include <initializer_list>
#include <vector>

#include "liblevenshtein/transducer/position.h"

namespace liblevenshtein {

  using Comparator = std::function<int(Position *, Position *)>;

  class StateIterator;

  class State {
  public:
    State() = default;
    State(std::initializer_list<Position *> positions);
    State(std::vector<Position *> &positions);
    ~State();

    void head(Position *head);
    [[nodiscard]] auto head() const -> Position *;

    void add(Position *next);
    void insert_after(Position *curr, Position *next);
    void remove(Position *prev, Position *curr);
    void sort(const Comparator &compare);

    auto begin() -> StateIterator;
    auto end() -> StateIterator;

  private:
    Position* _head = nullptr;

    auto merge_sort(const Comparator &compare, Position *lhs_head) -> Position *;
    static auto merge(const Comparator &compare, Position *lhs_head,
                      Position *rhs_head) -> Position *;
    static auto find_middle(Position *head) -> Position *;
  };

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_STATE_H
