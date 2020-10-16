#ifndef __LIBLEVENSHTEIN__TRANSDUCER__POSITION_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__POSITION_H__

#include <cstddef>

#include "algorithm.h"


namespace liblevenshtein {

    class Position {
    public:
        Position(std::size_t term_index, std::size_t num_errors, bool is_special=false);
        ~Position();

        void next(Position *next);
        Position* next() const;

        std::size_t term_index() const;
        std::size_t num_errors() const;
        bool is_special() const;
    private:
        Position* _next = nullptr;
        std::size_t _term_index;
        std::size_t _num_errors;
        bool _is_special;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__POSITION_H__
