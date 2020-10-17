#include <gtest/gtest.h>

#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/collection/transition.h"


TEST(Transition, has_proper_copy_and_move_constructors) {
    liblevenshtein::DawgNode source, target1;
    liblevenshtein::DawgNode target2(true);
    liblevenshtein::Transition trans1('\0', &source, &target1);
    liblevenshtein::Transition trans2 = trans1;
    liblevenshtein::Transition trans3('\0', &source, &target2);
    liblevenshtein::Transition trans4('a', &source, &target1);
    EXPECT_EQ(trans1, trans2);
    EXPECT_NE(trans1, trans3);
    EXPECT_NE(trans1, trans4);
}


TEST(Transition, has_correct_getters) {
    liblevenshtein::DawgNode source;
    liblevenshtein::DawgNode target(true);
    liblevenshtein::Transition transition('\0', &source, &target);
    EXPECT_EQ('\0', transition.label());
    EXPECT_EQ(source, *(transition.source()));
    EXPECT_EQ(target, *(transition.target()));
}
