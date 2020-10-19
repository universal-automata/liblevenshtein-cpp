#include <gtest/gtest.h>

#include "liblevenshtein/config/rapidcheck_parser.h"


int main(int argc, char *argv[]) {
    liblevenshtein::init_rapidcheck(argv[0]);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
