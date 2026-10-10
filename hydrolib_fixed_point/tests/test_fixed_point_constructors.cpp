#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

#include <climits>
#include <tuple>

#include "fixed_point_test_helpers.hpp"

using hydrolib::math::FixedPoint;

namespace
{
TEST(TestHydrolibMath, FixedPointDefaultConstructor)
{
    FixedPointBase fixed_point{};

    EXPECT_DOUBLE_EQ(static_cast<double>(fixed_point), 0);
}

class TestFixedPointConstructorInt : public ::testing::Test,
                                     public ::testing::WithParamInterface<int>
{
};

INSTANTIATE_TEST_CASE_P(
    Test, TestFixedPointConstructorInt,
    ::testing::Values(0, FixedPointBase::kUpperNotIncludedBound - 1,
                      FixedPointBase::kLowerNotIncludedBound + 1, 1, -1, 5, 7,
                      32, -15, -192, 134));

TEST_P(TestFixedPointConstructorInt, Basic)
{
    auto value = GetParam();
    FixedPointBase fixed_point(value);

    EXPECT_DOUBLE_EQ(static_cast<double>(fixed_point), value);
}

class TestFixedPointConstructorIntWithDivider
    : public ::testing::Test,
      public ::testing::WithParamInterface<std::tuple<int, int>>
{
};

INSTANTIATE_TEST_CASE_P(
    Test, TestFixedPointConstructorIntWithDivider,
    ::testing::Values(
        std::tuple<int, int>{0, 2}, std::tuple<int, int>{1, 1},
        std::tuple<int, int>{-1, 1},
        std::tuple<int, int>{INT_MAX, 1 << FixedPointBase::kFractionBits},
        std::tuple<int, int>{INT_MIN, 1 << FixedPointBase::kFractionBits},
        std::tuple<int, int>{11, 5}, std::tuple<int, int>{-17, 8},
        std::tuple<int, int>{12, 3}, std::tuple<int, int>{-196, 3},
        std::tuple<int, int>{346, 9}));

TEST_P(TestFixedPointConstructorIntWithDivider, Basic)
{
    auto values = GetParam();
    auto number = std::get<0>(values);
    auto divider = std::get<1>(values);
    FixedPointBase fixed_point(number, divider);

    EXPECT_NEAR(static_cast<double>(fixed_point),
                static_cast<double>(number) / divider,
                FixedPointBase::kLeastBitValue);
}

class TestFixedPointConstructorDouble
    : public ::testing::Test,
      public ::testing::WithParamInterface<double>
{
};

INSTANTIATE_TEST_CASE_P(
    Test, TestFixedPointConstructorDouble,
    ::testing::Values(
        0, 1, -1,
        FixedPointBase::kUpperNotIncludedBound - FixedPointBase::kLeastBitValue,
        FixedPointBase::kLowerNotIncludedBound + FixedPointBase::kLeastBitValue,
        FixedPointBase::kLeastBitValue, -FixedPointBase::kLeastBitValue, 3.5,
        -3.5, 1.25, -1.25, 0.75, -0.75, 0.25, -0.25, 0.77, -0.77, 333, -123,
        189.013));

TEST_P(TestFixedPointConstructorDouble, Basic)
{
    auto test_value = GetParam();
    FixedPointBase fixed_point(test_value);
    EXPECT_NEAR(static_cast<double>(fixed_point), test_value,
                FixedPointBase::kLeastBitValue);
}

template <int FRACTION_BITS>
class TestFixedPointConstructorFixedPoint
    : public ::testing::Test,
      public ::testing::WithParamInterface<FixedPoint<FRACTION_BITS>>
{
public:
    static void RunTest()
    {
        auto value = ::testing::WithParamInterface<
            FixedPoint<FRACTION_BITS>>::GetParam();

        if (static_cast<double>(value) <
                FixedPointBase::kUpperNotIncludedBound &&
            static_cast<double>(value) > FixedPointBase::kLowerNotIncludedBound)
        {
            auto result = FixedPointBase(value);
            EXPECT_NEAR(static_cast<double>(result), static_cast<double>(value),
                        FixedPointBase::kLeastBitValue);
        }
    }

    static inline auto cases =
        ::testing::ValuesIn(kFixedPointCases<FRACTION_BITS>);
};

using TestFixedPointConstructorFixedPointLessFraction =
    TestFixedPointConstructorFixedPoint<FixedPointBase::kFractionBits - 4>;

INSTANTIATE_TEST_CASE_P(Test, TestFixedPointConstructorFixedPointLessFraction,
                        TestFixedPointConstructorFixedPointLessFraction::cases);

TEST_P(TestFixedPointConstructorFixedPointLessFraction, Basic)
{
    TestFixedPointConstructorFixedPointLessFraction::RunTest();
}

using TestFixedPointConstructorFixedPointMoreFraction =
    TestFixedPointConstructorFixedPoint<FixedPointBase::kFractionBits + 4>;

INSTANTIATE_TEST_CASE_P(Test, TestFixedPointConstructorFixedPointMoreFraction,
                        TestFixedPointConstructorFixedPointMoreFraction::cases);

TEST_P(TestFixedPointConstructorFixedPointMoreFraction, Basic)
{
    TestFixedPointConstructorFixedPointMoreFraction::RunTest();
}

} // namespace