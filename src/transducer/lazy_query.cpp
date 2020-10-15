#include <stdint.h>

#include "lazy_query.h"


namespace liblevenshtein {

    template <class Result>
    LazyQuery<Result>::LazyQuery(std::string& term,
                                 std::size_t max_distance,
                                 DawgNode *root,
                                 State *initial_state,
                                 TransitionFn transition,
                                 GetEdgesFn get_edges,
                                 DistanceFn min_distance)
        : term(term),
          max_distance(max_distance),
          transition(transition),
          get_edges(get_edges),
          min_distance(min_distance),
          a(max_distance < (SIZE_MAX - 1) >> 1
            ? (max_distance << 1) + 1
            : SIZE_MAX) {
        pending.push(build_intersection(nullptr, '\0', root, initial_state));
    }

    template <class Result>
    LazyQuery<Result>::~LazyQuery() {
        for (Intersection *intersection : intersections) {
            delete intersection;
        }
    }

    template <class Result>
    LazyQuery<Result> &LazyQuery<Result>::operator++() {
        if (!edges.empty() || !pending.empty()) {
            do {
                if (edges.empty()) {
                    intersection = pending.front();
                    pending.pop();
                    DawgNode *node = intersection->get_node();
                    State *state = intersection->get_state();
                    i = state->get_head()->get_term_index();
                    std::size_t b = term.length() - i;
                    k = (a < b) ? a : b;
                    edges = get_edges(node);
                }
                else {
                    DawgNode *node = intersection->get_node();
                    State *state = intersection->get_state();
                    std::pair<char, DawgNode *> edge = edges.front();
                    edges.pop();
                    char label = edge.first;
                    DawgNode *next_node = edge.second;
                    std::vector<bool> characteristic_vector =
                        this->characteristic_vector(label, term, k, i);
                    State *next_state = transition(state, characteristic_vector);
                    if (next_state != nullptr) {
                        Intersection *next_intersection =
                            build_intersection(intersection, label, next_node, next_state);
                        pending.push(next_intersection);
                        if (next_node->is_final()) {
                            std::size_t distance = min_distance(next_state, term.length());
                            if (distance <= max_distance) {
                                std::string term = next_intersection->str();
                                update_candidate(term, distance);
                            }
                        }
                    }
                    delete state;
                }
            }
            while (!edges.empty() || !pending.empty());
        }
        else {
            is_complete = true;
        }
        return *this;
    }

    template <>
    void LazyQuery<std::string>::update_candidate(std::string& term, std::size_t distance) {
        candidate = term;
    }

    template <>
    void LazyQuery<std::pair<std::string, std::size_t>>::update_candidate(std::string& term,
                                                                          std::size_t distance) {
        candidate.first = term;
        candidate.second = distance;
    }

    template <class Result>
    Result LazyQuery<Result>::operator*() const {
        return candidate;
    }

    template <class Result>
    bool LazyQuery<Result>:: operator!=(const LazyQuery<Result> &other) const {
        return !is_complete;
    }

    template <class Result>
    std::vector<bool> LazyQuery<Result>::characteristic_vector(
            char x, std::string &term, std::size_t k, std::size_t i) {
        std::vector<bool> characteristic_vector(k);
        for (int j = 0; j < k; j += 1) {
            characteristic_vector[j] = (x == term[i + j]);
        }
        return characteristic_vector;
    }

    template <class Result>
    Intersection *LazyQuery<Result>::build_intersection(
            Intersection *parent, char label, DawgNode *node, State *state) {
        Intersection *intersection = new Intersection(parent, label, node, state);
        intersections.push_back(intersection);
        return intersection;
    }

} // namespace liblevenshtein
