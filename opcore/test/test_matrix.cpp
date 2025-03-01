#include <gtest/gtest.h>
#include "OpCore/Matrix.h"

// Test case for Matrix addition
TEST(MatrixTest, Addition) {
    OpCore::Matrix<float, 2, 2> mat1({1.0f, 2.0f, 3.0f, 4.0f});
    OpCore::Matrix<float, 2, 2> mat2({5.0f, 6.0f, 7.0f, 8.0f});
    auto result = mat1 + mat2;
    OpCore::Matrix<float, 2, 2> expected({6.0f, 8.0f, 10.0f, 12.0f});
    ASSERT_EQ(result, expected);
}

// Test case for Matrix multiplication
TEST(MatrixTest, Multiplication) {
    OpCore::Matrix<float, 2, 3> mat1({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f});
    OpCore::Matrix<float, 3, 2> mat2({7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f});
    auto result = mat1 * mat2;
    OpCore::Matrix<float, 2, 2> expected({58.0f, 64.0f, 139.0f, 154.0f});
    ASSERT_EQ(result, expected);
}
