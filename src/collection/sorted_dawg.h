#ifndef __LIBLEVENSHTEIN__COLLECTION__SORTED_DAWG_H__
#define __LIBLEVENSHTEIN__COLLECTION__SORTED_DAWG_H__

#include <stack>
#include <unordered_map>
#include <unordered_set>

#include "dawg_node.h"
#include "dawg.h"
#include "transition.h"

namespace liblevenshtein {

    class SortedDawg : public Dawg {
    public:
        using Dawg::Dawg;
        bool add(const std::string& term) override;
        bool remove(const std::string &term) override;
        void finish();

      private:
        std::stack<Transition> unchecked_transitions;
        std::unordered_map<DawgNode, DawgNode *> minimized_nodes;
        std::string prev_term;

        std::unordered_set<DawgNode *> floating_nodes;

        void minimize(int lower_bound);
        DawgNode* get_minimized_node(DawgNode* key) const;
    };

    template <class IterType>
    SortedDawg* sorted_dawg(IterType iter, IterType end);
} // namespace liblevenshtein

#endif // __LIBLEVENSHTEIN__COLLECTION__SORTED_DAWG_H__
