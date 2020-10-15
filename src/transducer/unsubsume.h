#ifndef __LIBLEVENSHTEIN__TRANSDUCER__UNSUBSUME_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__UNSUBSUME_H__

#include <cstddef>
#include <functional>

#include "position.h"
#include "state.h"
#include "subsumes.h"


namespace liblevenshtein {

    using Subsumes = std::function<bool(Position *, Position *, std::size_t)>;

    class Unsubsume {
    public:
        Unsubsume(Subsumes subsumes);
        void operator()(State *state, std::size_t query_length);
    private:
        Subsumes subsumes;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__UNSUBSUME_H__
