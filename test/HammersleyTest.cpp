#include <gtest/gtest.h>

#include "../include/HammersleySampler.h"


TEST(PhiTest, SimpleTest) {
    EXPECT_EQ(phi(1), 0.5);
    EXPECT_EQ(phi(2), 0.25);
    EXPECT_EQ(phi(3), 0.75);
    EXPECT_EQ(phi(4), 0.125);
    EXPECT_EQ(phi(5), 0.625);
    EXPECT_EQ(phi(6), 0.375);
    EXPECT_EQ(phi(7), 0.875);
    EXPECT_EQ(phi(8), 0.0625);
}