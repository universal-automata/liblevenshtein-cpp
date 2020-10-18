#include <cstdint>
#include <stdint.h>
#include <algorithm>

#include "liblevenshtein/transducer/position_transition.h"

namespace liblevenshtein {

    std::size_t index_of(std::vector<bool> &characteristic_vector,
                         std::size_t k, std::size_t i) {
        for (std::size_t j = 0; j < k; j += 1) {
            if (characteristic_vector[i + j]) {
                return j;
            }
        }
        return SIZE_MAX;
    }

    template <>
    std::vector<Position *> position_transition<Algorithm::STANDARD>(
        std::size_t n, Position *position,
        std::vector<bool> &characteristic_vector,
        std::size_t offset) {

        std::size_t i = position->term_index();
        std::size_t e = position->num_errors();
        std::size_t h = i - offset;
        std::size_t w = characteristic_vector.size();

        if (e < n) {
            if (h + 2 <= w) {
                std::size_t a = (n - e < SIZE_MAX)
                    ? n - e + 1
                    : SIZE_MAX;
                std::size_t b = w - h;
                std::size_t k = (a < b) ? a : b;
                std::size_t j = index_of(characteristic_vector, k, h);

                if (j == 0) {
                    return {
                        new Position(i + 1, e)
                    };
                }

                if (j != SIZE_MAX) {
                    return {
                        new Position(i, e + 1),
                        new Position(i + 1, e + 1),
                        new Position(i + j + 1, e + j)
                    };
                }

                return {
                    new Position(i, e + 1),
                    new Position(i + 1, e + 1)
                };
            }

            if (h + 1 == w) {
                if (characteristic_vector[h]) {
                    return {
                        new Position(i + 1, e)
                    };
                }

                return {
                    new Position(i, e + 1),
                    new Position(i + 1, e + 1)
                };
            }

            return {
                new Position(i, e + 1)
            };
        }

        if (e == n && h + 1 <= w && characteristic_vector[h]) {
            return {
                new Position(i + 1, n)
            };
        }

        return {};
    }

    template <>
    std::vector<Position *> position_transition<Algorithm::TRANSPOSITION>(
        std::size_t n, Position *position,
        std::vector<bool> &characteristic_vector,
        std::size_t offset) {

        std::size_t i = position->term_index();
        std::size_t e = position->num_errors();
        bool t = position->is_special();
        std::size_t h = i - offset;
        std::size_t w = characteristic_vector.size();

        if (e == 0 && 0 < n) {
            if (h + 2 <= w) {
                std::size_t a = (n - e < SIZE_MAX)
                    ? n - e + 1
                    : SIZE_MAX;
                std::size_t b = w - h;
                std::size_t k = (a < b) ? a : b;
                std::size_t j = index_of(characteristic_vector, k, h);

                switch (j) {
                case 0:
                    return {
                        new Position(i + 1, 0)
                    };
                case 1:
                    return {
                        new Position(i, 1),
                        new Position(i, 1, true),
                        new Position(i + 1, 1),
                        new Position(i + 2, 1)
                    };
                case SIZE_MAX:
                    return {
                        new Position(i, 1),
                        new Position(i + 1, 1)
                    };
                default:
                    return {
                        new Position(i, 1),
                        new Position(i + 1, 1),
                        new Position(i + j + 1, j)
                    };
                }
            }

            if (h + 1 == w) {
                if (characteristic_vector[h]) {
                    return {
                        new Position(i + 1, 0)
                    };
                }

                return {
                    new Position(i, 1),
                    new Position(i + 1, 1)
                };
            }

            return {
                new Position(i, 1)
            };
        }

        if (1 <= e && e < n) {
            if (h + 2 <= w) {
                if (!t) {
                    std::size_t a = (n - e < SIZE_MAX)
                        ? n - e + 1
                        : SIZE_MAX;
                    std::size_t b = w - h;
                    std::size_t k = (a < b) ? a : b;
                    std::size_t j = index_of(characteristic_vector, k, h);

                    switch (j) {
                    case 0:
                        return {
                            new Position(i + 1, e)
                        };
                    case 1:
                        return {
                            new Position(i, e + 1),
                            new Position(i, e + 1, true),
                            new Position(i + 1, e + 1),
                            new Position(i + 2, e + 1)
                        };
                    case SIZE_MAX:
                        return {
                            new Position(i, e + 1),
                            new Position(i + 1, e + 1)
                        };
                    default:
                        return {
                            new Position(i, e + 1),
                            new Position(i + 1, e + 1),
                            new Position(i + j + 1, e + j)
                        };
                    }
                }

                if (characteristic_vector[h]) {
                    return {
                        new Position(i + 2, e)
                    };
                }

                return {};
            }

            if (h + 1 == w) {
                if (characteristic_vector[h]) {
                    return {
                        new Position(i + 1, e)
                    };
                }

                return {
                    new Position(i, e + 1),
                    new Position(i + 1, e + 1)
                };
            }

            return {
                new Position(i, e + 1)
            };
        }

        if (h + 1 <= w && !t) {
            if (characteristic_vector[h]) {
                return {
                    new Position(i + 1, n)
                };
            }

            return {};
        }

        if (h + 2 <= w && t && characteristic_vector[h]) {
            return {
                new Position(i + 2, n)
            };
        }

        return {};
    }

    template <>
    std::vector<Position *> position_transition<Algorithm::MERGE_AND_SPLIT>(
        std::size_t n, Position *position,
        std::vector<bool> &characteristic_vector,
        std::size_t offset) {

        std::size_t i = position->term_index();
        std::size_t e = position->num_errors();
        bool s = position->is_special();
        std::size_t h = i - offset;
        std::size_t w = characteristic_vector.size();

        if (e == 0 && 0 < n) {
            if (h + 2 <= w) {
                if (characteristic_vector[h]) {
                    return {
                        new Position(i + 1, e)
                    };
                }

                return {
                    new Position(i, e + 1),
                    new Position(i, e + 1, true),
                    new Position(i + 1, e + 1),
                    new Position(i + 2, e + 1)
                };
            }

            if (h + 1 == w) {
                if (characteristic_vector[h]) {
                    return {
                        new Position(i + 1, e)
                    };
                }

                return {
                    new Position(i, e + 1),
                    new Position(i, e + 1, true),
                    new Position(i + 1, e + 1)
                };
            }

            return {
                new Position(i, e + 1)
            };
        }

        if (e < n) {
            if (h + 2 <= w) {
                if (!s) {
                    if (characteristic_vector[h]) {
                        return {
                            new Position(i + 1, e)
                        };
                    }

                    return {
                        new Position(i, e + 1),
                        new Position(i, e + 1, true),
                        new Position(i + 1, e + 1),
                        new Position(i + 2, e + 1)
                    };
                }

                return {
                    new Position(i + 1, e)
                };
            }

            if (h + 1 == w) {
                if (!s) {
                    if (characteristic_vector[h]) {
                        return {
                            new Position(i + 1, e)
                        };
                    }

                    return {
                        new Position(i, e + 1),
                        new Position(i, e + 1, true),
                        new Position(i + 1, e + 1)
                    };
                }

                return {
                    new Position(i + 1, e)
                };
            }

            return {
                new Position(i, e + 1)
            };
        }

        if (h + 1 <= w) {
            if (!s) {
                if (characteristic_vector[h]) {
                    return {
                        new Position(i + 1, n)
                    };
                }

                return {};
            }

            return {
                new Position(i + 1, e)
            };
        }

        return {};
    }

} // namespace liblevenshtein
