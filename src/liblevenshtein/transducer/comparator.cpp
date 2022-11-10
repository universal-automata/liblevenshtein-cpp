#include "liblevenshtein/transducer/comparator.h"


namespace liblevenshtein {
// We have to be careful because term_index and num_errors are unsigned integer
// types, so subtracting may result in an underflow.

    template <>
    int compare<Algorithm::STANDARD>(Position *lhs, Position *rhs) {
        if (lhs->term_index() < rhs->term_index()) {
            return -1;
        }

        if (lhs->term_index() > rhs->term_index()) {
            return 1;
        }

        if (lhs->num_errors() < rhs->num_errors()) {
            return -1;
        }

        if (lhs->num_errors() > rhs->num_errors()) {
            return 1;
        }

        return 0;
    }

    template <>
    int compare<Algorithm::TRANSPOSITION>(Position *lhs, Position *rhs) {
        if (lhs->term_index() < rhs->term_index()) {
            return -1;
        }

        if (lhs->term_index() > rhs->term_index()) {
            return 1;
        }

        if (lhs->num_errors() < rhs->num_errors()) {
            return -1;
        }

        if (lhs->num_errors() > rhs->num_errors()) {
            return 1;
        }

        return lhs->is_special() - rhs->is_special();
    }

    template <>
    int compare<Algorithm::MERGE_AND_SPLIT>(Position *lhs, Position *rhs) {
        if (lhs->term_index() < rhs->term_index()) {
            return -1;
        }

        if (lhs->term_index() > rhs->term_index()) {
            return 1;
        }

        if (lhs->num_errors() < rhs->num_errors()) {
            return -1;
        }

        if (lhs->num_errors() > rhs->num_errors()) {
            return 1;
        }

        return lhs->is_special() - rhs->is_special();
    }

} // namespace liblevenshtein
