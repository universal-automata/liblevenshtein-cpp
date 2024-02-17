#include "liblevenshtein/transducer/state.h"
#include "liblevenshtein/transducer/state_iterator.h"

namespace liblevenshtein {

State::State(std::initializer_list<Position *> positions) {
  Position *curr = nullptr;
  for (Position *next : positions) {
    insert_after(curr, next);
    curr = next;
  }
}

State::State(std::vector<Position *> &positions) {
  Position *curr = nullptr;
  for (Position *next : positions) {
    insert_after(curr, next);
    curr = next;
  }
}

State::~State() {
  delete _head;
}

void State::head(Position* head) {
  head->next(_head);
  _head = head;
}

auto State::head() const -> Position * {
  return _head;
}

void State::add(Position* next) {
  if (_head == nullptr) {
    _head = next;
  }
  else {
    Position* curr = _head;
    while (curr->next() != nullptr) {
      curr = curr->next();
    }
    curr->next(next);
  }
}

void State::insert_after(Position *curr, Position *next) {
  if (curr != nullptr) {
    next->next(curr->next());
    curr->next(next);
  }
  else {
    add(next);
  }
}

void State::remove(Position *prev, Position *curr) {
  // ASSUMPTION: prev->next() == curr
  Position* temp;
  if (prev != nullptr) {
    temp = prev->next();
    prev->next(curr->next());
  }
  else {
    temp = _head;
    _head = _head->next();
  }
  temp->next(nullptr);
  delete temp;
}

auto State::merge_sort(const Comparator &compare, Position *lower)
    -> Position * {
  if (lower == nullptr || lower->next() == nullptr) {
    return lower;
  }

  Position* middle = find_middle(lower);
  Position* upper = middle->next();
  middle->next(nullptr);

  return merge(compare,
         merge_sort(compare, lower),
         merge_sort(compare, upper));
}

auto State::merge(const Comparator &compare, Position *lower, Position *upper)
    -> Position * {
  Position temp(-1, -1);
  Position* next = &temp;
  Position* curr = next;

  while (lower != nullptr && upper != nullptr) {
    if (compare(lower, upper) < 1) {
      curr->next(lower);
      lower = lower->next();
    }
    else {
      curr->next(upper);
      upper = upper->next();
    }
    curr = curr->next();
  }

  if (upper != nullptr) {
    curr->next(upper);
  }
  else if (lower != nullptr) {
    curr->next(lower);
  }

  curr = next->next();
  temp.next(nullptr);
  return curr;
}

auto State::find_middle(Position *lower) -> Position * {
  Position* slow = lower;
  Position* fast = lower;

  while (fast->next() != nullptr && fast->next()->next() != nullptr) {
    slow = slow->next();
    fast = fast->next()->next();
  }

  return slow;
}

void State::sort(const Comparator &compare) {
  _head = merge_sort(compare, _head);
}

auto State::begin() -> StateIterator {
  return {this, _head};
}

auto State::end() -> StateIterator {
  return {this, nullptr};
}

} // namespace liblevenshtein
