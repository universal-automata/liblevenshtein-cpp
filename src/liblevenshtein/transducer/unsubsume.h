#ifndef LIBLEVENSHTEIN_TRANSDUCER_UNSUBSUME_H
#define LIBLEVENSHTEIN_TRANSDUCER_UNSUBSUME_H

#include <cstddef>
#include <functional>

#include "liblevenshtein/transducer/position.h"
#include "liblevenshtein/transducer/state.h"

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


#endif // LIBLEVENSHTEIN_TRANSDUCER_UNSUBSUME_H
