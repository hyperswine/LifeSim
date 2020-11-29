#include "gtest/gtest.h"

int five(){
    return 5;
}

TEST(testerf, zero) {
    ASSERT_EQ(0, 0);
}


bool b(){
    return false;
}

TEST(TesterB, lamob) {
    ASSERT_EQ(b(), false);
}
