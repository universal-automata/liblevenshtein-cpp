#ifndef LIBLEVENSHTEIN_TRANSDUCER_INTERSECTION_H
#define LIBLEVENSHTEIN_TRANSDUCER_INTERSECTION_H

#include <iostream>
#include <string>

#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/transducer/state.h"

namespace liblevenshtein {

  class Intersection {
  public:
    Intersection(char label, DawgNode *node, State *state, Intersection *parent = nullptr);
    ~Intersection();

    [[nodiscard]] auto node() const -> DawgNode *;
    [[nodiscard]] auto state() const -> State *;

    [[nodiscard]] auto str() const -> std::string;
    friend auto operator<<(std::ostream &out, const Intersection &intersection)
        -> std::ostream &;

  private:
    char _label;
    DawgNode *_node;
    State *_state;
    Intersection *_parent;
  };

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_INTERSECTION_H
