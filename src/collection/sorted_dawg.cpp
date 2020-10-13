#include <algorithm>
#include <cstdio>
#include <list>
#include <set>
#include <vector>

#include "final_dawg_node.h"
#include "sorted_dawg.h"


namespace liblevenshtein {

    bool SortedDawg::add(const std::string &term) {
        if (term < prev_term) {
            return false;
        }

        if (term.empty()) {
            delete root;
            root = new FinalDawgNode();
            prev_term = term;
            size += 1;
            return true;
        }

        int upper_bound = std::min(term.length(), prev_term.length());

        // Find the length of the longest common prefix between term and prev_term
        int i = 0;
        while (i < upper_bound && term[i] == prev_term[i]) {
            i += 1;
        }

        // Check the unchecked nodes for redundancy from the last one down to
        // the common prefix size. Then, truncate the list at that point.
        minimize(i);

        // Add the suffix starting from the correct node min-way through the graph
        DawgNode *source = unchecked_transitions.empty()
            ? root
            : unchecked_transitions.top().get_target();

        for (int k = term.length() - 1; i < k; i += 1) {
            DawgNode *target = new DawgNode();
            floating_nodes.insert(target);
            unchecked_transitions.push(Transition(term[i], source, target));
            source = target;
        }

        if (i < term.length()) {
            DawgNode *target = new FinalDawgNode();
            floating_nodes.insert(target);
            unchecked_transitions.push(Transition(term[i], source, target));
        }

        prev_term = term;
        size += 1;
        return true;
    }

    void SortedDawg::finish() {
        minimize(0);
        for (DawgNode *node : this->all_nodes()) {
            floating_nodes.erase(node);
        }
        for (DawgNode *node : floating_nodes) {
            delete node;
        }
        floating_nodes.empty();
    }

    DawgNode* SortedDawg::get_minimized_node(DawgNode* key) const {
        auto iter = minimized_nodes.find(*key);
        if (iter != minimized_nodes.end()) {
            return iter->second;
        }
        return nullptr;
    }

    void SortedDawg::minimize(int lower_bound) {
        // proceed from the leaf up to a certain point
        for (int j = unchecked_transitions.size(); j > lower_bound; j -= 1) {
            Transition transition = unchecked_transitions.top();
            unchecked_transitions.pop();
            char label = transition.get_label();
            DawgNode* source = transition.get_source();
            DawgNode* target = transition.get_target();
            DawgNode* existing = get_minimized_node(target);
            if (existing != nullptr) {
                source->add_edge(label, existing);
            }
            else {
                source->add_edge(label, target);
                minimized_nodes[*target] = target;
            }
        }
    }

    bool SortedDawg::remove(const std::string &term) {
        return false;
    }

    template <class IterType>
    SortedDawg* sorted_dawg(IterType iter, IterType end) {
        SortedDawg *dawg = new SortedDawg();
        while (iter != end) {
            const std::string &term = *iter;
            if (!dawg->add(term)) {
                delete dawg;
                return nullptr;
            }
            ++iter;
        }
        dawg->finish();
        return dawg;
    }

    template SortedDawg *sorted_dawg(std::list<std::string>::iterator iter,
                                     std::list<std::string>::iterator end);

    template SortedDawg *sorted_dawg(std::vector<std::string>::iterator iter,
                                     std::vector<std::string>::iterator end);

    template SortedDawg *sorted_dawg(std::set<std::string>::iterator iter,
                                     std::set<std::string>::iterator end);

} // namespace liblevenshtein
