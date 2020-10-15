#include "comparator.h"


namespace liblevenshtein {

    template <Algorithm Type>
    int compare(Position *lhs, Position *rhs) {
        int comparison = lhs->get_term_index() - rhs->get_term_index();
        if (comparison != 0) {
            return comparison;
        }

        comparison = lhs->get_num_errors() - rhs->get_num_errors();
        if (comparison != 0) {
            return comparison;
        }

        return lhs->is_special() - rhs->is_special();
    }

    template <>
    int compare<Algorithm::STANDARD>(Position *lhs, Position *rhs) {
        int comparison = lhs->get_term_index() - rhs->get_term_index();
        if (comparison != 0) {
            return comparison;
        }
        return lhs->get_num_errors() - rhs->get_num_errors();
    }

} // namespace liblevenshtein
