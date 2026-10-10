#pragma once

#include <array>
#include <ostream>

#include "hydrolib_fixed_point.hpp"

namespace hydrolib::math
{
template <int kFractionBitsParam>
void PrintTo(FixedPoint<kFractionBitsParam> point, std::ostream *os)
{
    *os << static_cast<double>(point) << "fp";
}
} // namespace hydrolib::math

using FixedPointBase = hydrolib::math::FixedPoint<16>;

template <int kFractionBits>
constexpr std::array<hydrolib::math::FixedPoint<kFractionBits>, 10>
    kFixedPointCases = {
        0,
        1,
        -1,
        hydrolib::math::FixedPoint<kFractionBits>::kUpperNotIncludedBound -
            hydrolib::math::FixedPoint<kFractionBits>::kLeastBitValue,
        hydrolib::math::FixedPoint<kFractionBits>::kLowerNotIncludedBound +
            hydrolib::math::FixedPoint<kFractionBits>::kLeastBitValue,
        hydrolib::math::FixedPoint<kFractionBits>::kLeastBitValue,
        -hydrolib::math::FixedPoint<kFractionBits>::kLeastBitValue,
        2.7568,
        -7.891,
        107.11231};
