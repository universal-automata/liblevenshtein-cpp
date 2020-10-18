#include <stdint.h>

#include "liblevenshtein/transducer/lazy_query.h"

namespace liblevenshtein {

    template <class Result>
    LazyQuery<Result>::LazyQuery(const std::string& term,
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
        _pending.push(build_intersection('\0', root, initial_state, nullptr));
        if (root->is_final() && term.length() <= max_distance) { // special case
            std::string candidate = "";
            update_candidate(candidate, term.length());
        }
        else {
            advance();
        }
    }

    template <class Result>
    LazyQuery<Result>::~LazyQuery() {
        for (Intersection *intersection : _intersections) {
            delete intersection;
        }
    }

    template <class Result>
    void LazyQuery<Result>::advance() {
        if (!_edges.empty() || !_pending.empty()) {
            _is_complete = true;
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
                    char next_label = edge.first;
                    DawgNode *next_node = edge.second;
                    std::vector<bool> characteristic_vector =
                        this->characteristic_vector(next_label, _term, _k, _i);
                    State *next_state = transition(state, characteristic_vector);
                    if (next_state != nullptr) {
                        Intersection *next_intersection =
                            build_intersection(next_label, next_node, next_state, _intersection);
                        _pending.push(next_intersection);
                        if (next_node->is_final()) {
                            std::size_t distance = min_distance(next_state, _term.length());
                            if (distance <= _max_distance) {
                                std::string term = next_intersection->str();
                                update_candidate(term, distance);
                                _is_complete = false;
                                break;
                            }
                        }
                    }
                }
            }
            while (!_edges.empty() || !_pending.empty());
        }
        else {
            _is_complete = true;
        }
    }

    template <class Result>
    Intersection* LazyQuery<Result>::build_intersection(char label, DawgNode *node, State *state, Intersection *parent) {
        Intersection *intersection = new Intersection(label, node, state, parent);
        _intersections.push_back(intersection);
        return intersection;
    }

    template <class Result>
    LazyQuery<Result> &LazyQuery<Result>::operator++() {
        advance();
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
    const Result& LazyQuery<Result>::operator*() const {
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
    LazyIterator<Result>::LazyIterator(const std::string &term,
                                       std::size_t max_distance,
                                       DawgNode *root,
                                       State *initial_state,
                                       TransitionFn transition,
                                       DistanceFn min_distance)
        : _term(term),
          _max_distance(max_distance),
          _root(root),
          _initial_state(initial_state),
          transition(transition),
          min_distance(min_distance)
    {}

    template <class Result>
    LazyQuery<Result> LazyIterator<Result>::begin() {
        return LazyQuery<Result>(_term,
                                 _max_distance,
                                 _root,
                                 _initial_state,
                                 transition,
                                 min_distance);
    }

    template <class Result>
    LazyQuery<Result> LazyIterator<Result>::end() {
        return LazyQuery<Result>();
    }

} // namespace liblevenshtein
