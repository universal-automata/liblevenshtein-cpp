#include <stdint.h>

#include "lazy_query.h"


namespace liblevenshtein {

    template <class Result>
    LazyQuery<Result>::LazyQuery(std::string& term,
                                 std::size_t max_distance,
                                 DawgNode *root,
                                 State *initial_state,
                                 TransitionFn transition,
                                 DistanceFn min_distance)
        : _term(term),
          _max_distance(max_distance),
          transition(transition),
          min_distance(min_distance),
          _a(max_distance < (SIZE_MAX - 1) >> 1
            ? (max_distance << 1) + 1
            : SIZE_MAX) {
        _pending.push(build_intersection(nullptr, '\0', root, initial_state));
    }

    template <class Result>
    LazyQuery<Result>::~LazyQuery() {
        for (Intersection *intersection : _intersections) {
            delete intersection;
        }
    }

    template <class Result>
    LazyQuery<Result> &LazyQuery<Result>::operator++() {
        if (!_edges.empty() || !_pending.empty()) {
            do {
                if (_edges.empty()) {
                    _intersection = _pending.front();
                    _pending.pop();
                    DawgNode *node = _intersection->node();
                    State *state = _intersection->state();
                    _i = state->head()->term_index();
                    std::size_t b = _term.length() - _i;
                    _k = (_a < b) ? _a : b;
                    node->for_each_edge([&](char label, DawgNode *target) {
                        _edges.push(std::pair<char, DawgNode *>(label, target));
                    });
                }
                else {
                    DawgNode *node = _intersection->node();
                    State *state = _intersection->state();
                    std::pair<char, DawgNode *> edge = _edges.front();
                    _edges.pop();
                    char label = edge.first;
                    DawgNode *next_node = edge.second;
                    std::vector<bool> characteristic_vector =
                        this->characteristic_vector(label, _term, _k, _i);
                    State *next_state = transition(state, characteristic_vector);
                    if (next_state != nullptr) {
                        Intersection *next_intersection =
                            build_intersection(_intersection, label, next_node, next_state);
                        _pending.push(next_intersection);
                        if (next_node->is_final()) {
                            std::size_t distance = min_distance(next_state, _term.length());
                            if (distance <= _max_distance) {
                                std::string term = next_intersection->str();
                                update_candidate(term, distance);
                            }
                        }
                    }
                    delete state;
                }
            }
            while (!_edges.empty() || !_pending.empty());
        }
        else {
            _is_complete = true;
        }
        return *this;
    }

    template <>
    void LazyQuery<std::string>::update_candidate(std::string& term, std::size_t distance) {
        _candidate = term;
    }

    template <>
    void LazyQuery<std::pair<std::string, std::size_t>>::update_candidate(std::string& term,
                                                                          std::size_t distance) {
        _candidate.first = term;
        _candidate.second = distance;
    }

    template <class Result>
    Result LazyQuery<Result>::operator*() const {
        return _candidate;
    }

    template <class Result>
    bool LazyQuery<Result>:: operator!=(const LazyQuery<Result> &other) const {
        return !_is_complete;
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
        _intersections.push_back(intersection);
        return intersection;
    }

} // namespace liblevenshtein
