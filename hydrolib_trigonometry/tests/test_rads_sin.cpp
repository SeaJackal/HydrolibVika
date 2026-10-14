#include <gtest/gtest.h>

#include <cmath>
#include <numbers>

#include "hydrolib_rads.hpp"

using hydrolib::math::Rads;

namespace
{
constexpr double kAngleStep = 1.0 / (1 << Rads::kFractionalBits);
constexpr double kHalfPi = std::numbers::pi / 2;
constexpr double kPi = std::numbers::pi;
constexpr double kThreeHalfPi = 3 * std::numbers::pi / 2;
constexpr double kTwoPi = 2 * std::numbers::pi;
constexpr double kSinTolerance = 2e-6;

class TestRadsSin : public ::testing::Test,
                    public ::testing::WithParamInterface<double>
{
};

TEST_P(TestRadsSin, MatchesStdSin)
{
    auto value = GetParam();
    Rads angle(value);

    EXPECT_NEAR(static_cast<double>(angle.SinCos().first), std::sin(value),
                kSinTolerance);
    EXPECT_NEAR(static_cast<double>(angle.SinCos().second), std::cos(value),
                kSinTolerance);
}

INSTANTIATE_TEST_SUITE_P(
    RationalAngles, TestRadsSin,
    ::testing::Values(0.0, 1.0, -1.0, 0.5, -0.5, 0.1, -0.1, 2.0, -2.0, 3.0,
                      -3.0, std::numbers::pi / 2, -std::numbers::pi / 2,
                      std::numbers::pi / 4, -std::numbers::pi / 4));
} // namespace
