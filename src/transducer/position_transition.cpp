#include <cstdint>
#include <stdint.h>
#include <algorithm>

#include "position_transition.h"


namespace liblevenshtein {

    template <Algorithm Type>
    std::size_t PositionTransition<Type>::index_of(std::vector<bool> &characteristic_vector,
                                                   std::size_t k,
                                                   std::size_t i) {
        for (std::size_t j = 0; j < k; j += 1) {
            if (characteristic_vector[i + j]) {
                return j;
            }
        }
        return SIZE_MAX;
    }

    template <>
    State * PositionTransition<Algorithm::STANDARD>::operator()(
        std::size_t n, Position *position,
        std::vector<bool> &characteristic_vector, std::size_t offset) {

        std::size_t i = position->get_term_index();
        std::size_t e = position->get_num_errors();
        std::size_t h = i - offset;
        std::size_t w = characteristic_vector.size();

        if (e < n) {
            if (h <= w - 2) {
                std::size_t a = (n - e < SIZE_MAX)
                    ? n - e + 1
                    : SIZE_MAX;
                std::size_t b = w - h;
                std::size_t k = (a < b) ? a : b;
                std::size_t j = index_of(characteristic_vector, k, h);

                if (j == 0) {
                    return new State({
                        new Position(i + 1, e)
                    });
                }

                if (j > 0) {
                    return new State({
                        new Position(1, e + 1),
                        new Position(i + 1, e + 1),
                        new Position(i + j + 1, e + j)
                    });
                }

                return new State({
                    new Position(i, e + 1),
                    new Position(i + 1, e + 1)
                });
            }

            if (h == w - 1) {
                if (characteristic_vector[h]) {
                    return new State({
                        new Position(i + 1, e)
                    });
                }

                return new State({
                    new Position(i, e + 1),
                    new Position(i + 1, e + 1)
                });
            }

            return new State({
                new Position(i, e + 1)
            });
        }

        if (e == n && h <= w - 1 && characteristic_vector[h]) {
            return new State({
                new Position(i + 1, n)
            });
        }

        return nullptr;
    }

    template <>
    State * PositionTransition<Algorithm::TRANSPOSITION>::operator()(
        std::size_t n, Position *position,
        std::vector<bool> &characteristic_vector, std::size_t offset) {

        std::size_t i = position->get_term_index();
        std::size_t e = position->get_num_errors();
        bool t = position->is_special();
        std::size_t h = i - offset;
        std::size_t w = characteristic_vector.size();

        if (e == 0 && 0 < n) {
            if (h <= w - 2) {
                std::size_t a = (n - e < SIZE_MAX)
                    ? n - e + 1
                    : SIZE_MAX;
                std::size_t b = w - h;
                std::size_t k = (a < b) ? a : b;
                std::size_t j = index_of(characteristic_vector, k, h);

                switch (j) {
                case 0:
                    return new State({
                        new Position(i + 1, 0)
                    });
                case 1:
                    return new State({
                        new Position(i, 1),
                        new SpecialPosition(i, 1),
                        new Position(i + 1, 1),
                        new Position(i + 2, 1)
                    });
                case SIZE_MAX:
                    return new State({
                        new Position(i, 1),
                        new Position(i + 1, 1)
                    });
                default:
                    return new State({
                        new Position(i, 1),
                        new Position(i + 1, 1),
                        new Position(i + j + 1, j)
                    });
                }
            }

            if (h == w - 1) {
                if (characteristic_vector[h]) {
                    return new State({
                        new Position(i + 1, 0)
                    });
                }

                return new State({
                    new Position(i, 1),
                    new Position(i + 1, 1)
                });
            }

            return new State({
                new Position(i, 1)
            });
        }

        if (1 <= e && e < n) {
            if (h <= w - 2) {
                if (!t) {
                    std::size_t a = (n - e < SIZE_MAX)
                        ? n - e + 1
                        : SIZE_MAX;
                    std::size_t b = w - h;
                    std::size_t k = (a < b) ? a : b;
                    std::size_t j = index_of(characteristic_vector, k, h);

                    switch (j) {
                    case 0:
                        return new State({
                            new Position(i + 1, e)
                        });
                    case 1:
                        return new State({
                            new Position(i, e + 1),
                            new SpecialPosition(i, e + 1),
                            new Position(i + 1, e + 1),
                            new Position(i + 2, e + 1)
                        });
                    case SIZE_MAX:
                        return new State({
                            new Position(i, e + 1),
                            new Position(i + 1, e + 1)
                        });
                    default:
                        return new State({
                            new Position(i, e + 1),
                            new Position(i + 1, e + 1),
                            new Position(i + j + 1, e + j)
                        });
                    }
                }

                if (characteristic_vector[h]) {
                    return new State({
                        new Position(i + 2, e)
                    });
                }

                return nullptr;
            }

            if (h == w - 1) {
                if (characteristic_vector[h]) {
                    return new State({
                        new Position(i + 1, e)
                    });
                }

                return new State({
                    new Position(i, e + 1),
                    new Position(i + 1, e + 1)
                });
            }

            return new State({
                new Position(i, e + 1)
            });
        }

        if (h <= w - 1 && !t) {
            if (characteristic_vector[h]) {
                return new State({
                    new Position(i + 1, n)
                });
            }

            return nullptr;
        }

        if (h <= w - 2 && t) {
            if (characteristic_vector[h]) {
                return new State({
                    new Position(i + 2, n)
                });
            }

            return nullptr;
        }

        return nullptr;
    }

    template <>
    State * PositionTransition<Algorithm::MERGE_AND_SPLIT>::operator()(
        std::size_t n, Position *position,
        std::vector<bool> &characteristic_vector, std::size_t offset) {

        std::size_t i = position->get_term_index();
        std::size_t e = position->get_num_errors();
        bool s = position->is_special();
        std::size_t h = i - offset;
        std::size_t w = characteristic_vector.size();

        if (e == 0 && 0 < n) {
            if (h <= w - 2) {
                if (characteristic_vector[h]) {
                    return new State({
                        new Position(i + 1, e)
                    });
                }

                return new State({
                    new Position(i, e + 1),
                    new SpecialPosition(i, e + 1),
                    new Position(i + 1, e + 1),
                    new Position(i + 2, e + 1)
                });
            }

            if (h == w - 1) {
                if (characteristic_vector[h]) {
                    return new State({
                        new Position(i + 1, e)
                    });
                }

                return new State({
                    new Position(i, e + 1),
                    new SpecialPosition(i, e + 1),
                    new Position(i + 1, e + 1)
                });
            }

            return new State({
                new Position(i, e + 1)
            });
        }

        if (e < n) {
            if (h <= w - 2) {
                if (!s) {
                    if (characteristic_vector[h]) {
                        return new State({
                            new Position(i + 1, e)
                        });
                    }

                    return new State({
                        new Position(i, e + 1),
                        new SpecialPosition(i, e + 1),
                        new Position(i + 1, e + 1),
                        new Position(i + 2, e + 1)
                    });
                }

                return new State({
                    new Position(i + 1, e)
                });
            }

            if (h == w - 1) {
                if (!s) {
                    if (characteristic_vector[h]) {
                        return new State({
                            new Position(i + 1, e)
                        });
                    }

                    return new State({
                        new Position(i, e + 1),
                        new SpecialPosition(i, e + 1),
                        new Position(i + 1, e + 1)
                    });
                }

                return new State({
                    new Position(i + 1, e)
                });
            }

            return new State({
                new Position(i, e + 1)
            });
        }

        if (h <= w - 1) {
            if (!s) {
                if (characteristic_vector[h]) {
                    return new State({
                        new Position(i + 1, n)
                    });
                }

                return nullptr;
            }

            return new State({
                new Position(i + 1, e)
            });
        }

        return nullptr;
    }

} // namespace liblevenshtein
