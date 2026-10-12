#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

#include <cmath>
#include <tuple>

#include "fixed_point_test_helpers.hpp"

using hydrolib::math::FixedPoint;

namespace
{
class TestFixedPointShiftOperations
    : public ::testing::Test,
      public ::testing::WithParamInterface<std::tuple<FixedPointBase, int>>
{
};

INSTANTIATE_TEST_SUITE_P(
    Test, TestFixedPointShiftOperations,
    ::testing::Combine(
        ::testing::ValuesIn(kFixedPointCases<FixedPointBase::kFractionBits>),
        ::testing::Values(0, 1, 4, 8, 16, 31)));

TEST_P(TestFixedPointShiftOperations, LeftShift)
{
    auto [value, shift] = GetParam();
    double original = static_cast<double>(value);
    double expected = original * std::pow(2.0, shift);
    if (expected < FixedPointBase::kUpperNotIncludedBound &&
        expected > FixedPointBase::kLowerNotIncludedBound)
    {
        auto result = value << shift;
        EXPECT_DOUBLE_EQ(static_cast<double>(result), expected);
        EXPECT_DOUBLE_EQ(static_cast<double>(value), original);
    }
}

TEST_P(TestFixedPointShiftOperations, RightShift)
{
    auto [value, shift] = GetParam();
    double original = static_cast<double>(value);
    double expected = original / std::pow(2.0, shift);

    auto result = value >> shift;
    EXPECT_NEAR(static_cast<double>(result), expected,
                FixedPointBase::kLeastBitValue);
    EXPECT_DOUBLE_EQ(static_cast<double>(value), original);
}

TEST_P(TestFixedPointShiftOperations, LeftShiftAssignment)
{
    auto [value, shift] = GetParam();
    double expected = static_cast<double>(value) * std::pow(2.0, shift);
    if (expected < FixedPointBase::kUpperNotIncludedBound &&
        expected > FixedPointBase::kLowerNotIncludedBound)
    {
        EXPECT_EQ(&(value <<= shift), &value);
        EXPECT_DOUBLE_EQ(static_cast<double>(value), expected);
    }
}

TEST_P(TestFixedPointShiftOperations, RightShiftAssignment)
{
    auto [value, shift] = GetParam();
    double expected = static_cast<double>(value) / std::pow(2.0, shift);

    EXPECT_EQ(&(value >>= shift), &value);
    EXPECT_NEAR(static_cast<double>(value), expected,
                FixedPointBase::kLeastBitValue);
}

template <int kFractionBits>
class TestFixedPointBinaryOperations
    : public ::testing::Test,
      public ::testing::WithParamInterface<
          std::tuple<FixedPointBase, FixedPoint<kFractionBits>>>
{
public:
    static void RunMultiplicationAssignmentTest()
    {
        auto values = ::testing::WithParamInterface<
            std::tuple<FixedPointBase, FixedPoint<kFractionBits>>>::GetParam();
        auto first = std::get<0>(values);
        auto second = std::get<1>(values);

        double expected =
            static_cast<double>(first) * static_cast<double>(second);
        if (expected < FixedPointBase::kUpperNotIncludedBound &&
            expected > FixedPointBase::kLowerNotIncludedBound)
        {
            first *= second;
            EXPECT_NEAR(static_cast<double>(first), expected,
                        FixedPointBase::kLeastBitValue);
        }
    }

    static void RunDivisionAssignmentTest()
    {
        auto values = ::testing::WithParamInterface<
            std::tuple<FixedPointBase, FixedPoint<kFractionBits>>>::GetParam();
        auto first = std::get<0>(values);
        auto second = std::get<1>(values);

        if (second != 0)
        {
            double expected =
                static_cast<double>(first) / static_cast<double>(second);
            if (expected < FixedPointBase::kUpperNotIncludedBound &&
                expected > FixedPointBase::kLowerNotIncludedBound)
            {
                first /= second;
                EXPECT_NEAR(static_cast<double>(first), expected,
                            FixedPointBase::kLeastBitValue);
            }
        }
    }

    static inline auto cases = ::testing::Combine(
        ::testing::ValuesIn(kFixedPointCases<FixedPointBase::kFractionBits>),
        ::testing::ValuesIn(kFixedPointCases<kFractionBits>));
};

using TestFixedPointBinaryOperationsBase =
    TestFixedPointBinaryOperations<FixedPointBase::kFractionBits>;

INSTANTIATE_TEST_CASE_P(Test, TestFixedPointBinaryOperationsBase,
                        TestFixedPointBinaryOperationsBase::cases);

using TestFixedPointBinaryOperationsMoreFraction =
    TestFixedPointBinaryOperations<FixedPointBase::kFractionBits + 4>;

INSTANTIATE_TEST_CASE_P(Test, TestFixedPointBinaryOperationsMoreFraction,
                        TestFixedPointBinaryOperationsMoreFraction::cases);

using TestFixedPointBinaryOperationsLessFraction =
    TestFixedPointBinaryOperations<FixedPointBase::kFractionBits - 4>;

INSTANTIATE_TEST_CASE_P(Test, TestFixedPointBinaryOperationsLessFraction,
                        TestFixedPointBinaryOperationsLessFraction::cases);

TEST_P(TestFixedPointBinaryOperationsBase, AdditionAssignment)
{
    auto values = GetParam();
    auto first = std::get<0>(values);
    auto second = std::get<1>(values);

    double expected = static_cast<double>(first) + static_cast<double>(second);
    if (expected < FixedPointBase::kUpperNotIncludedBound &&
        expected > FixedPointBase::kLowerNotIncludedBound)
    {
        first += second;
        EXPECT_DOUBLE_EQ(static_cast<double>(first), expected);
    }
}

TEST_P(TestFixedPointBinaryOperationsBase, SubtractionAssignment)
{
    auto values = GetParam();
    auto first = std::get<0>(values);
    auto second = std::get<1>(values);

    double expected = static_cast<double>(first) - static_cast<double>(second);
    if (expected < FixedPointBase::kUpperNotIncludedBound &&
        expected > FixedPointBase::kLowerNotIncludedBound)
    {
        first -= second;
        EXPECT_DOUBLE_EQ(static_cast<double>(first), expected);
    }
}

TEST_P(TestFixedPointBinaryOperationsBase, MultiplicationAssignment)
{
    TestFixedPointBinaryOperationsBase::RunMultiplicationAssignmentTest();
}

TEST_P(TestFixedPointBinaryOperationsBase, DivisionAssignment)
{
    TestFixedPointBinaryOperationsBase::RunDivisionAssignmentTest();
}

TEST_P(TestFixedPointBinaryOperationsMoreFraction, MultiplicationAssignment)
{
    TestFixedPointBinaryOperationsMoreFraction::
        RunMultiplicationAssignmentTest();
}

TEST_P(TestFixedPointBinaryOperationsMoreFraction, DivisionAssignment)
{
    TestFixedPointBinaryOperationsMoreFraction::RunDivisionAssignmentTest();
}

TEST_P(TestFixedPointBinaryOperationsLessFraction, MultiplicationAssignment)
{
    TestFixedPointBinaryOperationsLessFraction::
        RunMultiplicationAssignmentTest();
}

TEST_P(TestFixedPointBinaryOperationsLessFraction, DivisionAssignment)
{
    TestFixedPointBinaryOperationsLessFraction::RunDivisionAssignmentTest();
}

TEST_P(TestFixedPointBinaryOperationsBase, SpaceShip)
{
    auto values = GetParam();
    auto first = std::get<0>(values);
    auto second = std::get<1>(values);
    auto result = first <=> second;
    if (result == 0)
    {
        EXPECT_EQ(first - second, FixedPointBase(0));
    }
    else
    {
        auto expected =
            static_cast<double>(first) <=> static_cast<double>(second);
        EXPECT_EQ(result, expected);
    }
}
} // namespace
