//
// Created by Dustin on 2/2/26.
//

#include <gtest/gtest.h>

#include "../include/Matrix.h"
#include "../include/Vector.h"

TEST(MatrixTest, DefaultConstructor) {
    Matrix<double, 2, 3> matrix;

    EXPECT_EQ(matrix[0][0], 0.0);
    EXPECT_EQ(matrix[0][1], 0.0);
    EXPECT_EQ(matrix[0][2], 0.0);
    EXPECT_EQ(matrix[1][0], 0.0);
    EXPECT_EQ(matrix[1][1], 0.0);
    EXPECT_EQ(matrix[1][2], 0.0);
}

TEST(MatrixTest, InitializerListConstructor) {
    Matrix<double, 2, 3> matrix{1.0, 2.0, 3.0,
                                4.0, 5.0, 6.0};

    EXPECT_EQ(matrix[0][0], 1.0);
    EXPECT_EQ(matrix[0][1], 2.0);
    EXPECT_EQ(matrix[0][2], 3.0);
    EXPECT_EQ(matrix[1][0], 4.0);
    EXPECT_EQ(matrix[1][1], 5.0);
    EXPECT_EQ(matrix[1][2], 6.0);
}

TEST(MatrixTest, InitializerListConstructorThrow) {
    EXPECT_THROW((Matrix<double, 2, 3>{1.0, 2.0, 3.0}), std::logic_error);
    EXPECT_THROW((Matrix<double, 2, 2>{1.0, 2.0, 3.0}), std::logic_error);
}

TEST(MatrixTest, SubscriptOperator) {
    Matrix<double, 2, 3> matrix{1.0, 2.0, 3.0,
                                4.0, 5.0, 6.0};

    EXPECT_EQ(matrix[0][0], 1.0);
    EXPECT_EQ(matrix[1][2], 6.0);

    matrix[1][2] = 7.0;
    EXPECT_EQ(matrix[1][2], 7.0);

    EXPECT_THROW((matrix[2]), std::logic_error);

    const Matrix<double, 2, 3> c_matrix{1.0, 2.0, 3.0,
                                        4.0, 5.0, 6.0};
    EXPECT_EQ(c_matrix[0][0], 1.0);
    EXPECT_EQ(c_matrix[1][2], 6.0);
}

TEST(MatrixTest, Equality) {
    Matrix<double, 2, 2> matrix1{1.0, 2.0,
                                 3.0, 4.0};
    Matrix<double, 2, 2> matrix2{1.0, 2.0,
                                 3.0, 4.0};
    Matrix<double, 2, 2> matrix3{1.0, 2.0,
                                 3.0, 5.0};

    EXPECT_TRUE(matrix1 == matrix2);
    EXPECT_FALSE(matrix1 == matrix3);
    EXPECT_TRUE(matrix1 != matrix3);
}

TEST(MatrixTest, Identity) {
    auto identity = Identity<double, 4>();

    EXPECT_EQ(identity[0][0], 1.0);
    EXPECT_EQ(identity[0][1], 0.0);
    EXPECT_EQ(identity[1][1], 1.0);
    EXPECT_EQ(identity[2][2], 1.0);
    EXPECT_EQ(identity[3][3], 1.0);
}

TEST(MatrixTest, Transpose) {
    Matrix<double, 2, 3> matrix{1.0, 2.0, 3.0,
                                4.0, 5.0, 6.0};

    auto transpose = Transpose(matrix);

    EXPECT_EQ(transpose[0][0], 1.0);
    EXPECT_EQ(transpose[0][1], 4.0);
    EXPECT_EQ(transpose[1][0], 2.0);
    EXPECT_EQ(transpose[1][1], 5.0);
    EXPECT_EQ(transpose[2][0], 3.0);
    EXPECT_EQ(transpose[2][1], 6.0);
}

TEST(MatrixTest, Negation) {
    const Matrix<double, 2, 2> matrix{1.0, -2.0,
                                      3.0, -4.0};

    auto negative = -matrix;

    EXPECT_EQ(negative[0][0], -1.0);
    EXPECT_EQ(negative[0][1], 2.0);
    EXPECT_EQ(negative[1][0], -3.0);
    EXPECT_EQ(negative[1][1], 4.0);
}

TEST(MatrixTest, InplaceAddition) {
    Matrix<double, 2, 2> matrix{1.0, 2.0,
                                3.0, 4.0};
    matrix += Matrix<double, 2, 2>{1.0, 1.0,
                                   1.0, 1.0};

    EXPECT_EQ(matrix[0][0], 2.0);
    EXPECT_EQ(matrix[0][1], 3.0);
    EXPECT_EQ(matrix[1][0], 4.0);
    EXPECT_EQ(matrix[1][1], 5.0);
}

TEST(MatrixTest, InplaceSubtraction) {
    Matrix<double, 2, 2> matrix{1.0, 2.0,
                                3.0, 4.0};
    matrix -= Matrix<double, 2, 2>{1.0, 1.0,
                                   1.0, 1.0};

    EXPECT_EQ(matrix[0][0], 0.0);
    EXPECT_EQ(matrix[0][1], 1.0);
    EXPECT_EQ(matrix[1][0], 2.0);
    EXPECT_EQ(matrix[1][1], 3.0);
}

TEST(MatrixTest, ScalarMultiplication) {
    const Matrix<double, 2, 2> matrix{1.0, 2.0,
                                      3.0, 4.0};

    auto matrix_t_left = matrix * 2.0;
    EXPECT_EQ(matrix_t_left[0][0], 2.0);
    EXPECT_EQ(matrix_t_left[0][1], 4.0);
    EXPECT_EQ(matrix_t_left[1][0], 6.0);
    EXPECT_EQ(matrix_t_left[1][1], 8.0);

    auto matrix_t_right = 2.0 * matrix;
    EXPECT_EQ(matrix_t_right[0][0], 2.0);
    EXPECT_EQ(matrix_t_right[0][1], 4.0);
    EXPECT_EQ(matrix_t_right[1][0], 6.0);
    EXPECT_EQ(matrix_t_right[1][1], 8.0);
}

TEST(MatrixTest, ScalarDivision) {
    const Matrix<double, 2, 2> matrix{1.0, 2.0,
                                      3.0, 4.0};

    auto quotient = matrix / 2.0;

    EXPECT_EQ(quotient[0][0], 0.5);
    EXPECT_EQ(quotient[0][1], 1.0);
    EXPECT_EQ(quotient[1][0], 1.5);
    EXPECT_EQ(quotient[1][1], 2.0);
}

TEST(MatrixTest, MatrixVectorMultiplication) {
    Matrix<double, 3, 3> matrix{1.0, 2.0, 3.0,
                                4.0, 5.0, 6.0,
                                7.0, 8.0, 9.0};
    Vector<double, 3> vector{1.0, 2.0, 3.0};

    auto product = matrix * vector;

    EXPECT_EQ(product[0], 14.0);
    EXPECT_EQ(product[1], 32.0);
    EXPECT_EQ(product[2], 50.0);
}

TEST(MatrixTest, MatrixMultiplication) {
    Matrix<double, 2, 3> matrix1{1.0, 2.0, 3.0,
                                 4.0, 5.0, 6.0};
    Matrix<double, 3, 2> matrix2{7.0, 8.0,
                                 9.0, 10.0,
                                 11.0, 12.0};

    auto product = matrix1 * matrix2;

    EXPECT_EQ(product[0][0], 58.0);
    EXPECT_EQ(product[0][1], 64.0);
    EXPECT_EQ(product[1][0], 139.0);
    EXPECT_EQ(product[1][1], 154.0);
}

TEST(MatrixTest, Inverse) {
    Matrix<double, 3, 3> matrix{1.0, 2.0, 3.0,
                                0.0, 1.0, 4.0,
                                5.0, 6.0, 0.0};

    auto inverse = Inverse(matrix);

    EXPECT_NEAR(inverse[0][0], -24.0, 1e-5);
    EXPECT_NEAR(inverse[0][1], 18.0, 1e-5);
    EXPECT_NEAR(inverse[0][2], 5.0, 1e-5);
    EXPECT_NEAR(inverse[1][0], 20.0, 1e-5);
    EXPECT_NEAR(inverse[1][1], -15.0, 1e-5);
    EXPECT_NEAR(inverse[1][2], -4.0, 1e-5);
    EXPECT_NEAR(inverse[2][0], -5.0, 1e-5);
    EXPECT_NEAR(inverse[2][1], 4.0, 1e-5);
    EXPECT_NEAR(inverse[2][2], 1.0, 1e-5);
}
