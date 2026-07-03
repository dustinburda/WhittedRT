//
// Created by Dustin on 8/7/24.
//


#include <gtest/gtest.h>

#include "../include/Point.h"
#include "../include/Vector.h"


TEST(VectorTest, DefaultConstructor) {
    Vector<double, 4> vec;
    Vector<double, 4> zero{0.0, 0.0, 0.0, 0.0};

    EXPECT_EQ(vec, zero);
}

TEST(VectorTest, InitializerListConstructor) {
    Vector<double, 4> vec{1.0, 2.0, 3.0, 4.0};

    EXPECT_EQ(vec[0], 1.0);
    EXPECT_EQ(vec[1], 2.0);
    EXPECT_EQ(vec[2], 3.0);
    EXPECT_EQ(vec[3], 4.0);
}

TEST(VectorTest, InitializerListConstructorThrow) {
    EXPECT_THROW((Vector<double, 4>{1.0, 2.0, 3.0}), std::logic_error);
    EXPECT_THROW((Vector<double, 2>{1.0, 2.0, 3.0}), std::logic_error);
}

TEST(VectorTest, LowerDimensionVectorConstructor) {
    Vector<double, 4> vec(Vector<double, 3>{1.0, 2.0, 3.0}, 4.0);

    EXPECT_EQ(vec[0], 1.0);
    EXPECT_EQ(vec[1], 2.0);
    EXPECT_EQ(vec[2], 3.0);
    EXPECT_EQ(vec[3], 4.0);
}

TEST(VectorTest, SubscriptOperator) {
    Vector<double, 4> vec{1.0, 2.0, 3.0, 4.0};

    EXPECT_EQ(vec[0], 1.0);
    EXPECT_EQ(vec[1], 2.0);
    EXPECT_EQ(vec[2], 3.0);
    EXPECT_EQ(vec[3], 4.0);

    vec[3] = 5.0;
    EXPECT_EQ(vec[3], 5.0);

    EXPECT_THROW((vec[4]), std::logic_error);
    EXPECT_THROW((vec[-1]), std::logic_error);

    const Vector<double, 4> c_vec{1.0, 2.0, 3.0, 4.0};
    EXPECT_EQ(c_vec[0], 1.0);
    EXPECT_EQ(c_vec[1], 2.0);
}

TEST(VectorTest, Negation) {
    Vector<double, 4> vec1 {1.0, 2.0, 3.0, 4.0 };

    auto negative = -vec1;
    Vector<double, 4> expected {-1.0, -2.0, -3.0, -4.0};

    EXPECT_TRUE(negative == expected);
}

TEST(VectorTest, InplaceAddition) {
    Vector<double, 4> vec {1.0, 2.0, 3.0, 4.0 };
    vec += Vector<double, 4>{1.0, 1.0, 1.0, 1.0};

    EXPECT_EQ(vec[0], 2.0);
    EXPECT_EQ(vec[1], 3.0);
    EXPECT_EQ(vec[2], 4.0);
    EXPECT_EQ(vec[3], 5.0);
}

TEST(VectorTest, InplaceSubtraction) {
    Vector<double, 4> vec {1.0, 2.0, 3.0, 4.0 };
    vec -= Vector<double, 4>{1.0, 1.0, 1.0, 1.0};

    EXPECT_EQ(vec[0], 0.0);
    EXPECT_EQ(vec[1], 1.0);
    EXPECT_EQ(vec[2], 2.0);
    EXPECT_EQ(vec[3], 3.0);
}

TEST(VectorTest, InplaceScalarMultiplication) {
    Vector<double, 4> vec {1.0, 2.0, 3.0, 4.0 };
    vec *= 2;

    EXPECT_EQ(vec[0], 2.0);
    EXPECT_EQ(vec[1], 4.0);
    EXPECT_EQ(vec[2], 6.0);
    EXPECT_EQ(vec[3], 8.0);
}

TEST(VectorTest, LengthSquared) {
    Vector<double, 4> vec {1.0, 2.0, 3.0, 4.0 };
    EXPECT_EQ(vec.LengthSquared(), 30.0);
}

TEST(VectorTest, Length) {
    Vector<double, 4> vec {1.0, 2.0, 3.0, 4.0 };
    EXPECT_NEAR(vec.Length(), std::sqrt(30.0), 1e-5);
}

TEST(VectorTest, UnitVector) {
    Vector<double, 4> vec {1.0, 2.0, 3.0, 4.0 };
    auto normalized_vec = vec.UnitVector();

    EXPECT_NEAR(normalized_vec.Length(), 1.0, 1e-5);
}

TEST(VectorTest, UnitVectorThrow) {
    Vector<double, 4> vec {0.0, 0.0, 0.0, 0.0 };

    EXPECT_THROW((vec.UnitVector()), std::logic_error);
}

TEST(VectorTest, toString) {
    Vector<double, 4> vec {1.0, 2.0, 3.0, 4.0 };
    auto string_vec = vec.toString();

    EXPECT_EQ(string_vec, "Vector: [1, 2, 3, 4]");
}

TEST(VectorTest, Addition) {
    Vector<double, 4> vec1 {1.0, 2.0, 3.0, 4.0 };
    Vector<double, 4> vec2 {1.0, 2.0, 3.0, 4.0 };

    auto sum = vec1 + vec2;
    Vector<double, 4> expected {2.0, 4.0, 6.0, 8.0};

    EXPECT_TRUE(sum == expected);
}

TEST(VectorTest, Subtraction) {
    Vector<double, 4> vec1 {1.0, 2.0, 3.0, 4.0 };
    Vector<double, 4> vec2 {1.0, 2.0, 3.0, 4.0 };

    auto difference = vec1 - vec2;
    Vector<double, 4> expected {0.0, 0.0, 0.0, 0.0};

    EXPECT_TRUE(difference == expected);
}

TEST(VectorTest, ScalarMultiplication) {
    Vector<double, 4> vec {1.0, 2.0, 3.0, 4.0 };
    double t = 2.0;

    auto vec_t_left = vec * t;
    EXPECT_EQ(vec_t_left[0], 2.0);
    EXPECT_EQ(vec_t_left[1], 4.0);
    EXPECT_EQ(vec_t_left[2], 6.0);
    EXPECT_EQ(vec_t_left[3], 8.0);

    auto vec_t_right = t * vec;
    EXPECT_EQ(vec_t_right[0], 2.0);
    EXPECT_EQ(vec_t_right[1], 4.0);
    EXPECT_EQ(vec_t_right[2], 6.0);
    EXPECT_EQ(vec_t_right[3], 8.0);
}

TEST(VectorTest, ScalarDivision) {
    Vector<double, 4> vec {1.0, 2.0, 3.0, 4.0 };
    double t = 2.0;

    auto vec_t_left = vec / t;
    EXPECT_EQ(vec_t_left[0], 0.5);
    EXPECT_EQ(vec_t_left[1], 1.0);
    EXPECT_EQ(vec_t_left[2], 1.5);
    EXPECT_EQ(vec_t_left[3], 2.0);
}

TEST(VectorTest, DotProduct) {
    Vector<double, 4> vec1 {1.0, 2.0, 3.0, 4.0 };
    Vector<double, 4> vec2 {1.0, -1.0, -2.0, 0.0 };

    EXPECT_EQ(Dot(vec1, vec2), -7.0);


    vec1 = Vector<double, 4> {0.0, 6.0, 3.5, 4.0 };
    vec2 = Vector<double, 4> {1.0, -1.0, 2.0, 0.0 };

    EXPECT_EQ(Dot(vec1, vec2), 1.0);
}

TEST(VectorTest, CrossProduct) {
    Vector<double, 3> vec1 {1.0, 0.0, 0.0};
    Vector<double, 3> vec2 {0.0, 1.0, 0.0};

    EXPECT_EQ(Cross(vec1, vec2), (Vector<double, 3> {0.0, 0.0, 1.0}));

    vec1 = Vector<double, 3> {1.0, 2.0, 3.0};
    vec2 = Vector<double, 3> {2.0, 4.0, 6.0};

    EXPECT_EQ(Cross(vec1, vec2), (Vector<double, 3> {0.0, 0.0, 0.0}));
}

TEST(VectorTest, CrossProductThrow) {
    Vector<double, 4> vec1 {1.0, 2.0, 3.0, 4.0 };
    Vector<double, 4> vec2 {1.0, -1.0, -2.0, 0.0 };

    EXPECT_THROW(Cross(vec1, vec2), std::logic_error);


    Vector<double, 2> vec3 {1.0, 2.0};
    Vector<double, 2> vec4 {1.0, -1.0};

    EXPECT_THROW(Cross(vec3, vec4), std::logic_error);
}

TEST(VectorTest, ReflectVector) {

}