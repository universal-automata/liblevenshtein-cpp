#ifndef __LIBLEVENSHTEIN__TRANSDUCER__SPECIAL_POSITION_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__SPECIAL_POSITION_H__

#include "position.h"


namespace liblevenshtein {

    class SpecialPosition : public Position {
    public:
        using Position::Position;
        bool is_special() const override;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__SPECIAL_POSITION_H__
