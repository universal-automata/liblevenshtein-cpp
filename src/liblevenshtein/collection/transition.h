#ifndef LIBLEVENSHTEIN_COLLECTION_TRANSITION_H
#define LIBLEVENSHTEIN_COLLECTION_TRANSITION_H

#include "liblevenshtein/collection/dawg_node.h"


namespace liblevenshtein {

  class Transition {
  public:
    Transition(char label, DawgNode* source, DawgNode* target);
    Transition(const Transition& transition) = default;
    Transition(Transition&& transition) noexcept;

    [[nodiscard]] auto label() const -> char;

    [[nodiscard]] auto source() const -> DawgNode *;

    [[nodiscard]] auto target() const -> DawgNode *;

    auto operator==(const Transition &other) const -> bool;
    auto operator!=(const Transition &other) const -> bool;

  private:
    char _label;
    DawgNode *_source;
    DawgNode *_target;
  };
} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_COLLECTION_TRANSITION_H
