//
// Created by capta on 18/11/2020.
//
#include "gtest/gtest.h"

bool b(){
    return false;
}

TEST(TesterB, lamob) {
    ASSERT_EQ(b(), false);
}
