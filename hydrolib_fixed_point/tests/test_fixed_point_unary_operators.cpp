#include <gtest/gtest.h>

#include "fixed_point_test_helpers.hpp"

using hydrolib::math::FixedPoint;

namespace
{
class TestFixedPointUnaryOperations
    : public ::testing::Test,
      public ::testing::WithParamInterface<FixedPointBase>
{
};

TEST_P(TestFixedPointUnaryOperations, ToInt)
{
    auto value = GetParam();
    EXPECT_EQ(static_cast<int>(value),
              static_cast<int>(static_cast<double>(value)));
}

TEST_P(TestFixedPointUnaryOperations, Negation)
{
    auto value = GetParam();
    auto result = -value;
    EXPECT_EQ(static_cast<double>(result), -static_cast<double>(value));
}

INSTANTIATE_TEST_SUITE_P(TestFixedPointUnaryOperations,
                         TestFixedPointUnaryOperations,
                         ::testing::ValuesIn(kFixedPointCases<16>));
} // namespace