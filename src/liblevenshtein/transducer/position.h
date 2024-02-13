#ifndef LIBLEVENSHTEIN_TRANSDUCER_POSITION_H
#define LIBLEVENSHTEIN_TRANSDUCER_POSITION_H

#include <cstddef>

namespace liblevenshtein {

  class Position {
  public:
    Position(std::size_t term_index, std::size_t num_errors, bool is_special=false);
    ~Position();

    void next(Position *next);
    [[nodiscard]] auto next() const -> Position *;

    [[nodiscard]] auto term_index() const -> std::size_t;
    [[nodiscard]] auto num_errors() const -> std::size_t;
    [[nodiscard]] auto is_special() const -> bool;

  private:
    Position* _next = nullptr;
    std::size_t _term_index;
    std::size_t _num_errors;
    bool _is_special;
  };

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_POSITION_H
