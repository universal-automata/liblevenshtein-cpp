#ifndef __LIBLEVENSHTEIN__TRANSDUCER__UNSUBSUME_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__UNSUBSUME_H__

#include <cstddef>
#include <functional>

#include "position.h"
#include "state.h"
#include "subsumes.h"


namespace liblevenshtein {

    using SubsumesFn = std::function<bool(Position *, Position *, std::size_t)>;

    class UnsubsumeFn {
    public:
        UnsubsumeFn(SubsumesFn subsumes);
        void operator()(State *state, std::size_t query_length);
    private:
        SubsumesFn subsumes;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__UNSUBSUME_H__
