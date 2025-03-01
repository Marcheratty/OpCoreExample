#include <gtest/gtest.h>
#include "OpCore/Vector.h"

// Test case for Vector addition
TEST(VectorTest, Addition) {
    OpCore::Vector<float, 3> vec1({1.0f, 2.0f, 3.0f});
    OpCore::Vector<float, 3> vec2({4.0f, 5.0f, 6.0f});
    auto result = vec1 + vec2;
    OpCore::Vector<float, 3> expected({5.0f, 7.0f, 9.0f});
    ASSERT_EQ(result, expected);
}

// Test case for Dot product
TEST(VectorTest, DotProduct) {
    OpCore::Vector<float, 3> vec1({1.0f, 2.0f, 3.0f});
    OpCore::Vector<float, 3> vec2({4.0f, 5.0f, 6.0f});
    auto result = vec1.dot(vec2);
    float expected = 32.0f; // 1*4 + 2*5 + 3*6
    ASSERT_FLOAT_EQ(result, expected);
}
