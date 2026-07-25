//
// Created by Dustin on 2/2/26.
//

#include <gtest/gtest.h>

#include "../include/Normal.h"
#include "../include/Vector.h"

TEST(NormalTest, DefaultConstructor) {
    Normal<double, 4> normal;

    EXPECT_EQ(normal[0], 0.0);
    EXPECT_EQ(normal[1], 0.0);
    EXPECT_EQ(normal[2], 0.0);
    EXPECT_EQ(normal[3], 0.0);
}

TEST(NormalTest, InitializerListConstructor) {
    Normal<double, 4> normal{1.0, 2.0, 3.0, 4.0};

    EXPECT_EQ(normal[0], 1.0);
    EXPECT_EQ(normal[1], 2.0);
    EXPECT_EQ(normal[2], 3.0);
    EXPECT_EQ(normal[3], 4.0);
}

TEST(NormalTest, InitializerListConstructorThrow) {
    EXPECT_THROW((Normal<double, 4>{1.0, 2.0, 3.0}), std::logic_error);
    EXPECT_THROW((Normal<double, 2>{1.0, 2.0, 3.0}), std::logic_error);
}

TEST(NormalTest, SubscriptOperator) {
    Normal<double, 4> normal{1.0, 2.0, 3.0, 4.0};

    EXPECT_EQ(normal[0], 1.0);
    EXPECT_EQ(normal[1], 2.0);
    EXPECT_EQ(normal[2], 3.0);
    EXPECT_EQ(normal[3], 4.0);

    normal[3] = 5.0;
    EXPECT_EQ(normal[3], 5.0);

    EXPECT_THROW((normal[4]), std::logic_error);

    const Normal<double, 4> c_normal{1.0, 2.0, 3.0, 4.0};
    EXPECT_EQ(c_normal[0], 1.0);
    EXPECT_EQ(c_normal[1], 2.0);
}

TEST(NormalTest, Negation) {
    Normal<double, 4> normal{1.0, 2.0, 3.0, 4.0};

    auto negative = -normal;

    EXPECT_EQ(negative[0], -1.0);
    EXPECT_EQ(negative[1], -2.0);
    EXPECT_EQ(negative[2], -3.0);
    EXPECT_EQ(negative[3], -4.0);
}

TEST(NormalTest, InplaceAddition) {
    Normal<double, 4> normal{1.0, 2.0, 3.0, 4.0};
    normal += Normal<double, 4>{1.0, 1.0, 1.0, 1.0};

    EXPECT_EQ(normal[0], 2.0);
    EXPECT_EQ(normal[1], 3.0);
    EXPECT_EQ(normal[2], 4.0);
    EXPECT_EQ(normal[3], 5.0);
}

TEST(NormalTest, InplaceScalarMultiplication) {
    Normal<double, 4> normal{1.0, 2.0, 3.0, 4.0};
    normal *= 2.0;

    EXPECT_EQ(normal[0], 2.0);
    EXPECT_EQ(normal[1], 4.0);
    EXPECT_EQ(normal[2], 6.0);
    EXPECT_EQ(normal[3], 8.0);
}

TEST(NormalTest, InplaceScalarDivision) {
    Normal<double, 4> normal{1.0, 2.0, 3.0, 4.0};
    normal /= 2.0;

    EXPECT_EQ(normal[0], 0.5);
    EXPECT_EQ(normal[1], 1.0);
    EXPECT_EQ(normal[2], 1.5);
    EXPECT_EQ(normal[3], 2.0);
}

TEST(NormalTest, LengthSquared) {
    Normal<double, 4> normal{1.0, 2.0, 3.0, 4.0};

    EXPECT_EQ(normal.LengthSquared(), 30.0);
}

TEST(NormalTest, Length) {
    Normal<double, 4> normal{1.0, 2.0, 3.0, 4.0};

    EXPECT_NEAR(normal.Length(), std::sqrt(30.0), 1e-5);
}

TEST(NormalTest, UnitNormal) {
    Normal<double, 4> normal{1.0, 2.0, 3.0, 4.0};

    auto unit_normal = normal.UnitNormal();

    auto unit_normal_length = unit_normal.Length();

    EXPECT_NEAR(unit_normal.Length(), 1.0, 1e-5);
}

TEST(NormalTest, ToVector) {
    Normal<double, 4> normal{1.0, 2.0, 3.0, 4.0};

    auto vector = normal.ToVector();

    EXPECT_EQ(vector[0], 1.0);
    EXPECT_EQ(vector[1], 2.0);
    EXPECT_EQ(vector[2], 3.0);
    EXPECT_EQ(vector[3], 0.0);
}

TEST(NormalTest, ToString) {
    Normal<double, 4> normal{1.0, 2.0, 3.0, 4.0};

    EXPECT_EQ(normal.toString(), "Normal : [1, 2, 3, 4]");
}

TEST(NormalTest, Addition) {
    Normal<double, 4> normal1{1.0, 2.0, 3.0, 4.0};
    Normal<double, 4> normal2{1.0, 1.0, 1.0, 1.0};

    auto sum = normal1 + normal2;

    EXPECT_EQ(sum[0], 2.0);
    EXPECT_EQ(sum[1], 3.0);
    EXPECT_EQ(sum[2], 4.0);
    EXPECT_EQ(sum[3], 5.0);
}

TEST(NormalTest, ScalarMultiplication) {
    Normal<double, 4> normal{1.0, 2.0, 3.0, 4.0};

    auto normal_t_left = normal * 2.0;
    EXPECT_EQ(normal_t_left[0], 2.0);
    EXPECT_EQ(normal_t_left[1], 4.0);
    EXPECT_EQ(normal_t_left[2], 6.0);
    EXPECT_EQ(normal_t_left[3], 8.0);

    auto normal_t_right = 2.0 * normal;
    EXPECT_EQ(normal_t_right[0], 2.0);
    EXPECT_EQ(normal_t_right[1], 4.0);
    EXPECT_EQ(normal_t_right[2], 6.0);
    EXPECT_EQ(normal_t_right[3], 8.0);
}

TEST(NormalTest, ScalarDivision) {
    Normal<double, 4> normal{1.0, 2.0, 3.0, 4.0};

    auto quotient = normal / 2.0;

    EXPECT_EQ(quotient[0], 0.5);
    EXPECT_EQ(quotient[1], 1.0);
    EXPECT_EQ(quotient[2], 1.5);
    EXPECT_EQ(quotient[3], 2.0);
}

TEST(NormalTest, DotProduct) {
    Vector<double, 4> vector{1.0, 2.0, 3.0, 4.0};
    Normal<double, 4> normal{1.0, -1.0, -2.0, 0.0};

    EXPECT_EQ(Dot(vector, normal), -7.0);
    EXPECT_EQ(Dot(normal, vector), -7.0);
}

TEST(NormalTest, NormalVectorAddition) {
    Normal<double, 4> normal{1.0, 2.0, 3.0, 4.0};
    Vector<double, 4> vector{1.0, 1.0, 1.0, 1.0};

    auto normal_left = normal + vector;
    EXPECT_EQ(normal_left[0], 2.0);
    EXPECT_EQ(normal_left[1], 3.0);
    EXPECT_EQ(normal_left[2], 4.0);
    EXPECT_EQ(normal_left[3], 5.0);

    auto vector_left = vector + normal;
    EXPECT_EQ(vector_left[0], 2.0);
    EXPECT_EQ(vector_left[1], 3.0);
    EXPECT_EQ(vector_left[2], 4.0);
    EXPECT_EQ(vector_left[3], 5.0);
}
