//
// Created by Dustin on 8/7/24.
//


#include <gtest/gtest.h>

#include "../include/Point.h"
#include "../include/Vector.h"

TEST(VectorTest, Negation) {
    Vector<double, 4> vec1 {1.0, 2.0, 3.0, 4.0 };

    auto negative = -vec1;
    Vector<double, 4> expected {-1.0, -2.0, -3.0, -4.0};

    EXPECT_EQ(negative, expected);
}


TEST(VectorTest, Addition) {
    Vector<double, 4> vec1 {1.0, 2.0, 3.0, 4.0 };
    Vector<double, 4> vec2 {1.0, 2.0, 3.0, 4.0 };

    auto sum = vec1 + vec2;
    Vector<double, 4> expected {2.0, 4.0, 6.0, 8.0};

    EXPECT_EQ(sum, expected);
}

TEST(VectorTest, Subtraction) {
    Vector<double, 4> vec1 {1.0, 2.0, 3.0, 4.0 };
    Vector<double, 4> vec2 {1.0, 2.0, 3.0, 4.0 };

    auto difference = vec1 - vec2;
    Vector<double, 4> expected {0.0, 0.0, 0.0, 0.0};

    EXPECT_EQ(difference, expected);
}

TEST(VectorTest, CrossProdict) {

}

TEST(VectorTest, UnitVector) {

}