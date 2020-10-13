#ifndef __LIBLEVENSHTEIN__COLLECTION__FINAL_DAWG_NODE_H__
#define __LIBLEVENSHTEIN__COLLECTION__FINAL_DAWG_NODE_H__

#include "dawg_node.h"


namespace liblevenshtein {

    class FinalDawgNode : public DawgNode {
    public:
        using DawgNode::DawgNode;
        bool is_final() const override;
    };
}


#endif // __LIBLEVENSHTEIN__COLLECTION__FINAL_DAWG_NODE_H__
