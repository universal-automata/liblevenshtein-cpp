#include "subsumes.h"


namespace liblevenshtein {

    template <>
    bool subsumes<Algorithm::STANDARD>(Position *lhs, Position *rhs, std::size_t n) {
        std::size_t i = lhs->get_term_index();
        std::size_t e = lhs->get_num_errors();
        std::size_t j = rhs->get_term_index();
        std::size_t f = rhs->get_num_errors();
        return ((i < j) ? (j - i) : (i - j)) <= (f - e);
    }

    template <>
    bool subsumes<Algorithm::TRANSPOSITION>(Position *lhs, Position *rhs, std::size_t n) {
        std::size_t i = lhs->get_term_index();
        std::size_t e = lhs->get_num_errors();
        bool s = lhs->is_special();

        std::size_t j = rhs->get_term_index();
        std::size_t f = rhs->get_num_errors();
        bool t = lhs->is_special();

        if (s) {
            if (t) {
                return (i == j);
            }

            return (f == n) && (i == j);
        }

        if (t) {
            return ((j < i) ? (i - j - 1) : (j - i + 1)) <= (f - e);
        }

        return ((i < j) ? (j - i) : (i - j)) <= (f - e);
    }

    template <>
    bool subsumes<Algorithm::MERGE_AND_SPLIT>(Position *lhs, Position *rhs, std::size_t n) {
        std::size_t i = lhs->get_term_index();
        std::size_t e = lhs->get_num_errors();
        bool s = lhs->is_special();
        std::size_t j = rhs->get_term_index();
        std::size_t f = rhs->get_num_errors();
        bool t = lhs->is_special();

        if (s && !t) {
            return false;
        }

        return ((i < j) ? (j - i) : (i - j)) <= (f - e);
    }

} // namespace liblevenshtein
