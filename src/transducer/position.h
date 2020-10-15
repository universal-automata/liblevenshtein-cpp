#ifndef __LIBLEVENSHTEIN__TRANSDUCER__POSITION_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__POSITION_H__

#include <cstddef>

#include "algorithm.h"


namespace liblevenshtein {

    class Position {
    public:
        Position(std::size_t term_index, std::size_t num_errors);
        ~Position();

        void set_next(Position *next);
        Position* get_next() const;

        std::size_t get_term_index() const;
        std::size_t get_num_errors() const;
        virtual bool is_special() const;
    private:
        Position* next = nullptr;
        std::size_t term_index;
        std::size_t num_errors;
    };

    class SpecialPosition : public Position {
    public:
        using Position::Position;
        bool is_special() const override;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__POSITION_H__
