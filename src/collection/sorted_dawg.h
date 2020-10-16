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
        ~SortedDawg();

        bool add(const std::string& term) override;
        bool remove(const std::string &term) override;

        template <class IterType>
        friend SortedDawg* sorted_dawg(IterType iter, IterType end);

    private:
        std::stack<Transition>* unchecked_transitions = nullptr;
        std::unordered_map<DawgNode, DawgNode *>* minimized_nodes = nullptr;
        std::unordered_set<DawgNode *>* floating_nodes = nullptr;
        std::string _prev_term;

        void init();
        void clean_up();

        void finish();
        void minimize(int lower_bound);
        DawgNode* minimized_node(DawgNode* key) const;
    };

    template <class IterType>
    SortedDawg* sorted_dawg(IterType iter, IterType end);
} // namespace liblevenshtein

#endif // __LIBLEVENSHTEIN__COLLECTION__SORTED_DAWG_H__
