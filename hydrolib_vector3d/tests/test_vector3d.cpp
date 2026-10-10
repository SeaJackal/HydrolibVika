#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <tuple>

#include "hydrolib_vector3d.hpp"

namespace
{
using hydrolib::math::Vector3D;
using Vector = Vector3D<double>;

constexpr std::array<std::tuple<Vector, Vector, double>, 6> kDotCases{{
    {Vector{.x = 1.0, .y = 0.0, .z = 0.0}, Vector{.x = 0.0, .y = 1.0, .z = 0.0},
     0.0},
    {Vector{.x = 3.0, .y = 4.0, .z = 5.0}, Vector{.x = 3.0, .y = 4.0, .z = 5.0},
     50.0},
    {Vector{.x = 1.0, .y = 2.0, .z = 3.0}, Vector{.x = 4.0, .y = 5.0, .z = 6.0},
     32.0},
    {Vector{.x = 1.0, .y = -2.0, .z = 3.0},
     Vector{.x = -1.0, .y = 2.0, .z = 1.0}, -2.0},
    {Vector{.x = 0.0, .y = 0.0, .z = 0.0},
     Vector{.x = 5.0, .y = 10.0, .z = 15.0}, 0.0},
    {Vector{.x = 3.0, .y = 4.0, .z = 0.0}, Vector{.x = 3.0, .y = 4.0, .z = 0.0},
     25.0},
}};

constexpr std::array<std::tuple<Vector, Vector, Vector>, 5> kCrossCases{{
    {Vector{.x = 1.0, .y = 0.0, .z = 0.0}, Vector{.x = 0.0, .y = 1.0, .z = 0.0},
     Vector{.x = 0.0, .y = 0.0, .z = 1.0}},
    {Vector{.x = 1.0, .y = 2.0, .z = 3.0}, Vector{.x = 4.0, .y = 5.0, .z = 6.0},
     Vector{.x = -3.0, .y = 6.0, .z = -3.0}},
    {Vector{.x = 2.0, .y = 4.0, .z = 6.0}, Vector{.x = 1.0, .y = 2.0, .z = 3.0},
     Vector{.x = 0.0, .y = 0.0, .z = 0.0}},
    {Vector{.x = 0.0, .y = 0.0, .z = 0.0},
     Vector{.x = 5.0, .y = 10.0, .z = 15.0},
     Vector{.x = 0.0, .y = 0.0, .z = 0.0}},
    {Vector{.x = 1.0, .y = 2.0, .z = 3.0}, Vector{.x = 1.0, .y = 2.0, .z = 3.0},
     Vector{.x = 0.0, .y = 0.0, .z = 0.0}},
}};

constexpr std::array<std::tuple<Vector, double>, 3> kLengthCases{{
    {Vector{.x = 3.0, .y = 4.0, .z = 0.0}, 5.0},
    {Vector{.x = 1.0, .y = 2.0, .z = 2.0}, 3.0},
    {Vector{.x = 0.0, .y = 0.0, .z = 0.0}, 0.0},
}};

constexpr std::array<std::tuple<Vector, Vector>, 3> kNormalizeCases{{
    {Vector{.x = 3.0, .y = 4.0, .z = 0.0},
     Vector{.x = 3.0 / 5.0, .y = 4.0 / 5.0, .z = 0.0}},
    {Vector{.x = -3.0, .y = -4.0, .z = 0.0},
     Vector{.x = -3.0 / 5.0, .y = -4.0 / 5.0, .z = 0.0}},
    {Vector{.x = 1.0, .y = 2.0, .z = 2.0},
     Vector{.x = 1.0 / 3.0, .y = 2.0 / 3.0, .z = 2.0 / 3.0}},
}};

constexpr std::array<std::tuple<Vector, Vector, Vector>, 6> kAdditionCases{{
    {Vector{.x = 1.0, .y = 2.0, .z = 3.0}, Vector{.x = 4.0, .y = 5.0, .z = 6.0},
     Vector{.x = 5.0, .y = 7.0, .z = 9.0}},
    {Vector{.x = -1.0, .y = -2.0, .z = -3.0},
     Vector{.x = 1.0, .y = 2.0, .z = 3.0},
     Vector{.x = 0.0, .y = 0.0, .z = 0.0}},
    {Vector{.x = 0.0, .y = 0.0, .z = 0.0}, Vector{.x = 0.0, .y = 0.0, .z = 0.0},
     Vector{.x = 0.0, .y = 0.0, .z = 0.0}},
    {Vector{.x = 0.5, .y = -0.25, .z = 0.75},
     Vector{.x = -0.5, .y = 0.25, .z = -0.75},
     Vector{.x = 0.0, .y = 0.0, .z = 0.0}},
    {Vector{.x = 10.0, .y = 20.0, .z = 30.0},
     Vector{.x = -5.0, .y = 6.0, .z = -7.0},
     Vector{.x = 5.0, .y = 26.0, .z = 23.0}},
    {Vector{.x = 1.25, .y = -2.5, .z = 3.75},
     Vector{.x = -10.5, .y = 20.25, .z = -30.75},
     Vector{.x = -9.25, .y = 17.75, .z = -27.0}},
}};

constexpr std::array<std::tuple<Vector, Vector, Vector>, 6> kSubtractionCases{{
    {Vector{.x = 10.0, .y = 20.0, .z = 30.0},
     Vector{.x = 5.0, .y = 6.0, .z = 7.0},
     Vector{.x = 5.0, .y = 14.0, .z = 23.0}},
    {Vector{.x = 1.0, .y = 2.0, .z = 3.0}, Vector{.x = 1.0, .y = 1.0, .z = 1.0},
     Vector{.x = 0.0, .y = 1.0, .z = 2.0}},
    {Vector{.x = 0.0, .y = 0.0, .z = 0.0}, Vector{.x = 1.0, .y = 2.0, .z = 3.0},
     Vector{.x = -1.0, .y = -2.0, .z = -3.0}},
    {Vector{.x = 1.0, .y = 2.0, .z = 3.0}, Vector{.x = 0.0, .y = 0.0, .z = 0.0},
     Vector{.x = 1.0, .y = 2.0, .z = 3.0}},
    {Vector{.x = 1.25, .y = -2.5, .z = 3.75},
     Vector{.x = 1.25, .y = -2.5, .z = 3.75},
     Vector{.x = 0.0, .y = 0.0, .z = 0.0}},
    {Vector{.x = -10.5, .y = 20.25, .z = -30.75},
     Vector{.x = 1.25, .y = -2.5, .z = 3.75},
     Vector{.x = -11.75, .y = 22.75, .z = -34.5}},
}};

constexpr std::array<std::tuple<Vector, Vector>, 4> kUnaryMinusCases{{
    {Vector{.x = 1.0, .y = -2.0, .z = 3.0},
     Vector{.x = -1.0, .y = 2.0, .z = -3.0}},
    {Vector{.x = 0.0, .y = 0.0, .z = 0.0},
     Vector{.x = 0.0, .y = 0.0, .z = 0.0}},
    {Vector{.x = -1.0, .y = 2.0, .z = -3.0},
     Vector{.x = 1.0, .y = -2.0, .z = 3.0}},
    {Vector{.x = 0.5, .y = -0.25, .z = 0.75},
     Vector{.x = -0.5, .y = 0.25, .z = -0.75}},
}};

constexpr std::array<std::tuple<Vector, Vector, Vector>, 3> kPlusAssignCases{{
    {Vector{.x = 1.0, .y = 2.0, .z = 3.0}, Vector{.x = 4.0, .y = 5.0, .z = 6.0},
     Vector{.x = 5.0, .y = 7.0, .z = 9.0}},
    {Vector{.x = 0.0, .y = 0.0, .z = 0.0}, Vector{.x = 1.0, .y = 2.0, .z = 3.0},
     Vector{.x = 1.0, .y = 2.0, .z = 3.0}},
    {Vector{.x = -1.0, .y = -2.0, .z = -3.0},
     Vector{.x = 1.0, .y = 2.0, .z = 3.0},
     Vector{.x = 0.0, .y = 0.0, .z = 0.0}},
}};

constexpr std::array<std::tuple<Vector, Vector, Vector>, 3> kMinusAssignCases{{
    {Vector{.x = 10.0, .y = 20.0, .z = 30.0},
     Vector{.x = 5.0, .y = 6.0, .z = 7.0},
     Vector{.x = 5.0, .y = 14.0, .z = 23.0}},
    {Vector{.x = 0.0, .y = 0.0, .z = 0.0}, Vector{.x = 1.0, .y = 2.0, .z = 3.0},
     Vector{.x = -1.0, .y = -2.0, .z = -3.0}},
    {Vector{.x = 1.0, .y = 2.0, .z = 3.0}, Vector{.x = 0.0, .y = 0.0, .z = 0.0},
     Vector{.x = 1.0, .y = 2.0, .z = 3.0}},
}};

constexpr std::array<std::tuple<Vector, double, Vector>, 6>
    kScalarMultiplicationCases{{
        {Vector{.x = 1.0, .y = 2.0, .z = 3.0}, 2.0,
         Vector{.x = 2.0, .y = 4.0, .z = 6.0}},
        {Vector{.x = 2.0, .y = 4.0, .z = 6.0}, 0.5,
         Vector{.x = 1.0, .y = 2.0, .z = 3.0}},
        {Vector{.x = 5.0, .y = 10.0, .z = 15.0}, 0.0,
         Vector{.x = 0.0, .y = 0.0, .z = 0.0}},
        {Vector{.x = 1.0, .y = -2.0, .z = 3.0}, -2.0,
         Vector{.x = -2.0, .y = 4.0, .z = -6.0}},
        {Vector{.x = 2.5, .y = 5.0, .z = 7.5}, 4.0,
         Vector{.x = 10.0, .y = 20.0, .z = 30.0}},
        {Vector{.x = 1.0, .y = 2.0, .z = 3.0}, 6.0,
         Vector{.x = 6.0, .y = 12.0, .z = 18.0}},
    }};

constexpr std::array<std::tuple<Vector, double, Vector>, 5>
    kScalarDivisionCases{{
        {Vector{.x = 6.0, .y = 8.0, .z = 10.0}, 2.0,
         Vector{.x = 3.0, .y = 4.0, .z = 5.0}},
        {Vector{.x = 9.0, .y = 12.0, .z = 15.0}, 3.0,
         Vector{.x = 3.0, .y = 4.0, .z = 5.0}},
        {Vector{.x = 1.0, .y = 2.0, .z = 3.0}, 0.5,
         Vector{.x = 2.0, .y = 4.0, .z = 6.0}},
        {Vector{.x = 10.0, .y = 20.0, .z = 30.0}, 1.0,
         Vector{.x = 10.0, .y = 20.0, .z = 30.0}},
        {Vector{.x = 0.0, .y = 0.0, .z = 0.0}, 3.0,
         Vector{.x = 0.0, .y = 0.0, .z = 0.0}},
    }};

class TestVectorDot
    : public ::testing::TestWithParam<std::tuple<Vector, Vector, double>>
{
};

INSTANTIATE_TEST_SUITE_P(Test, TestVectorDot, ::testing::ValuesIn(kDotCases));

TEST_P(TestVectorDot, Basic)
{
    auto values = GetParam();
    auto first = std::get<0>(values);
    auto second = std::get<1>(values);
    auto expected = std::get<2>(values);
    EXPECT_DOUBLE_EQ(Vector::Dot(first, second), expected);
}

class TestVectorCross
    : public ::testing::TestWithParam<std::tuple<Vector, Vector, Vector>>
{
};

INSTANTIATE_TEST_SUITE_P(Test, TestVectorCross,
                         ::testing::ValuesIn(kCrossCases));

TEST_P(TestVectorCross, Basic)
{
    auto values = GetParam();
    auto first = std::get<0>(values);
    auto second = std::get<1>(values);
    auto expected = std::get<2>(values);
    auto result = Vector::Cross(first, second);
    EXPECT_DOUBLE_EQ(result.x, expected.x);
    EXPECT_DOUBLE_EQ(result.y, expected.y);
    EXPECT_DOUBLE_EQ(result.z, expected.z);
}

class TestVectorLength
    : public ::testing::TestWithParam<std::tuple<Vector, double>>
{
};

INSTANTIATE_TEST_SUITE_P(Test, TestVectorLength,
                         ::testing::ValuesIn(kLengthCases));

TEST_P(TestVectorLength, Basic)
{
    auto values = GetParam();
    auto vector = std::get<0>(values);
    auto expected = std::get<1>(values);
    EXPECT_DOUBLE_EQ(vector.GetLength(), expected);
}

class TestVectorNormalize
    : public ::testing::TestWithParam<std::tuple<Vector, Vector>>
{
};

INSTANTIATE_TEST_SUITE_P(Test, TestVectorNormalize,
                         ::testing::ValuesIn(kNormalizeCases));

TEST_P(TestVectorNormalize, Basic)
{
    auto values = GetParam();
    auto vector = std::get<0>(values);
    auto expected = std::get<1>(values);
    vector.Normalize();
    EXPECT_DOUBLE_EQ(vector.x, expected.x);
    EXPECT_DOUBLE_EQ(vector.y, expected.y);
    EXPECT_DOUBLE_EQ(vector.z, expected.z);
}

class TestVectorAddition
    : public ::testing::TestWithParam<std::tuple<Vector, Vector, Vector>>
{
};

INSTANTIATE_TEST_SUITE_P(Test, TestVectorAddition,
                         ::testing::ValuesIn(kAdditionCases));

TEST_P(TestVectorAddition, Basic)
{
    auto values = GetParam();
    auto first = std::get<0>(values);
    auto second = std::get<1>(values);
    auto expected = std::get<2>(values);
    auto result = first + second;
    EXPECT_DOUBLE_EQ(result.x, expected.x);
    EXPECT_DOUBLE_EQ(result.y, expected.y);
    EXPECT_DOUBLE_EQ(result.z, expected.z);
}

class TestVectorSubtraction
    : public ::testing::TestWithParam<std::tuple<Vector, Vector, Vector>>
{
};

INSTANTIATE_TEST_SUITE_P(Test, TestVectorSubtraction,
                         ::testing::ValuesIn(kSubtractionCases));

TEST_P(TestVectorSubtraction, Basic)
{
    auto values = GetParam();
    auto first = std::get<0>(values);
    auto second = std::get<1>(values);
    auto expected = std::get<2>(values);
    auto result = first - second;
    EXPECT_DOUBLE_EQ(result.x, expected.x);
    EXPECT_DOUBLE_EQ(result.y, expected.y);
    EXPECT_DOUBLE_EQ(result.z, expected.z);
}

class TestVectorUnaryMinus
    : public ::testing::TestWithParam<std::tuple<Vector, Vector>>
{
};

INSTANTIATE_TEST_SUITE_P(Test, TestVectorUnaryMinus,
                         ::testing::ValuesIn(kUnaryMinusCases));

TEST_P(TestVectorUnaryMinus, Basic)
{
    auto values = GetParam();
    auto vector = std::get<0>(values);
    auto expected = std::get<1>(values);
    auto result = -vector;
    EXPECT_DOUBLE_EQ(result.x, expected.x);
    EXPECT_DOUBLE_EQ(result.y, expected.y);
    EXPECT_DOUBLE_EQ(result.z, expected.z);
}

class TestVectorPlusAssign
    : public ::testing::TestWithParam<std::tuple<Vector, Vector, Vector>>
{
};

INSTANTIATE_TEST_SUITE_P(Test, TestVectorPlusAssign,
                         ::testing::ValuesIn(kPlusAssignCases));

TEST_P(TestVectorPlusAssign, Basic)
{
    auto values = GetParam();
    auto first = std::get<0>(values);
    auto second = std::get<1>(values);
    auto expected = std::get<2>(values);
    first += second;
    EXPECT_DOUBLE_EQ(first.x, expected.x);
    EXPECT_DOUBLE_EQ(first.y, expected.y);
    EXPECT_DOUBLE_EQ(first.z, expected.z);
}

class TestVectorMinusAssign
    : public ::testing::TestWithParam<std::tuple<Vector, Vector, Vector>>
{
};

INSTANTIATE_TEST_SUITE_P(Test, TestVectorMinusAssign,
                         ::testing::ValuesIn(kMinusAssignCases));

TEST_P(TestVectorMinusAssign, Basic)
{
    auto values = GetParam();
    auto first = std::get<0>(values);
    auto second = std::get<1>(values);
    auto expected = std::get<2>(values);
    first -= second;
    EXPECT_DOUBLE_EQ(first.x, expected.x);
    EXPECT_DOUBLE_EQ(first.y, expected.y);
    EXPECT_DOUBLE_EQ(first.z, expected.z);
}

class TestVectorScalarMultiplication
    : public ::testing::TestWithParam<std::tuple<Vector, double, Vector>>
{
};

INSTANTIATE_TEST_SUITE_P(Test, TestVectorScalarMultiplication,
                         ::testing::ValuesIn(kScalarMultiplicationCases));

TEST_P(TestVectorScalarMultiplication, Basic)
{
    auto values = GetParam();
    auto vector = std::get<0>(values);
    auto scalar = std::get<1>(values);
    auto expected = std::get<2>(values);
    auto result = vector * scalar;
    EXPECT_DOUBLE_EQ(result.x, expected.x);
    EXPECT_DOUBLE_EQ(result.y, expected.y);
    EXPECT_DOUBLE_EQ(result.z, expected.z);
}

class TestVectorScalarMultiplicationAssign
    : public ::testing::TestWithParam<std::tuple<Vector, double, Vector>>
{
};

INSTANTIATE_TEST_SUITE_P(Test, TestVectorScalarMultiplicationAssign,
                         ::testing::ValuesIn(kScalarMultiplicationCases));

TEST_P(TestVectorScalarMultiplicationAssign, Basic)
{
    auto values = GetParam();
    auto vector = std::get<0>(values);
    auto scalar = std::get<1>(values);
    auto expected = std::get<2>(values);
    vector *= scalar;
    EXPECT_DOUBLE_EQ(vector.x, expected.x);
    EXPECT_DOUBLE_EQ(vector.y, expected.y);
    EXPECT_DOUBLE_EQ(vector.z, expected.z);
}

class TestVectorScalarDivision
    : public ::testing::TestWithParam<std::tuple<Vector, double, Vector>>
{
};

INSTANTIATE_TEST_SUITE_P(Test, TestVectorScalarDivision,
                         ::testing::ValuesIn(kScalarDivisionCases));

TEST_P(TestVectorScalarDivision, Basic)
{
    auto values = GetParam();
    auto vector = std::get<0>(values);
    auto divisor = std::get<1>(values);
    auto expected = std::get<2>(values);
    auto result = vector / divisor;
    EXPECT_DOUBLE_EQ(result.x, expected.x);
    EXPECT_DOUBLE_EQ(result.y, expected.y);
    EXPECT_DOUBLE_EQ(result.z, expected.z);
}

class TestVectorScalarDivisionAssign
    : public ::testing::TestWithParam<std::tuple<Vector, double, Vector>>
{
};

INSTANTIATE_TEST_SUITE_P(Test, TestVectorScalarDivisionAssign,
                         ::testing::ValuesIn(kScalarDivisionCases));

TEST_P(TestVectorScalarDivisionAssign, Basic)
{
    auto values = GetParam();
    auto vector = std::get<0>(values);
    auto divisor = std::get<1>(values);
    auto expected = std::get<2>(values);
    vector /= divisor;
    EXPECT_DOUBLE_EQ(vector.x, expected.x);
    EXPECT_DOUBLE_EQ(vector.y, expected.y);
    EXPECT_DOUBLE_EQ(vector.z, expected.z);
}

} // namespace
