#include "comparator.h"


namespace liblevenshtein {

    template <Algorithm Type>
    int compare(Position *lhs, Position *rhs) {
        int comparison = lhs->term_index() - rhs->term_index();
        if (comparison != 0) {
            return comparison;
        }

        comparison = lhs->num_errors() - rhs->num_errors();
        if (comparison != 0) {
            return comparison;
        }

        return lhs->is_special() - rhs->is_special();
    }

    template <>
    int compare<Algorithm::STANDARD>(Position *lhs, Position *rhs) {
        int comparison = lhs->term_index() - rhs->term_index();
        if (comparison != 0) {
            return comparison;
        }
        return lhs->num_errors() - rhs->num_errors();
    }

} // namespace liblevenshtein
