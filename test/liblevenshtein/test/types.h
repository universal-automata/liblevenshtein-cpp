#ifndef LIBLEVENSHTEIN_TEST_TYPES_H
#define LIBLEVENSHTEIN_TEST_TYPES_H

#include <string>
#include <tuple>


namespace liblevenshtein::test {

using Triple = std::tuple<std::size_t, std::size_t, bool>;

} // namespace liblevenshtein::test

#endif // LIBLEVENSHTEIN_TEST_TYPES_H
