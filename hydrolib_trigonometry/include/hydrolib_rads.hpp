#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <numbers>
#include <numeric>

#include "hydrolib_fixed_point.hpp"

namespace hydrolib::math
{
using TrigonometryResult = FixedPoint<30>;

struct CORDICTable
{
    static constexpr int kFractionalBits = 29;
    static constexpr int kAtanTableSize = 20;

    constexpr CORDICTable()
    {
        for (int i = 0; i < kAtanTableSize; i++)
        {
            atans[i] = std::atan(1.0 / (1 << i));
        }

        x_shift = std::transform_reduce(
            atans.begin(), atans.end(), 1.0, std::multiplies<>{},
            [](FixedPoint<kFractionalBits> angle)
            { return std::cos(static_cast<double>(angle)); });
    }

    std::array<FixedPoint<kFractionalBits>, kAtanTableSize> atans{};
    FixedPoint<kFractionalBits> x_shift{};
};

class Rads
{
public:
    static constexpr int kFractionalBits = 29; // sizeof(int) * CHAR_BIT -
    // static_cast<int>(std::ceil(std::log2(std::numbers::pi * 2)));
    static constexpr FixedPoint<kFractionalBits> kPi =
        FixedPoint<kFractionalBits>(std::numbers::pi);
    static constexpr FixedPoint<kFractionalBits> kMaxValue = kPi;
    static constexpr FixedPoint<kFractionalBits> kMinValue = -kPi;

    constexpr Rads(int value, int divider);
    constexpr Rads(double value);

    constexpr Rads operator+() const;
    constexpr Rads operator-() const;
    constexpr Rads &operator+=(const Rads &other);
    constexpr Rads &operator-=(const Rads &other);
    template <int kOtherFractionBits>
    constexpr Rads &operator*=(FixedPoint<kOtherFractionBits> other);
    template <int kOtherFractionBits>
    constexpr Rads &operator/=(FixedPoint<kOtherFractionBits> other);

    constexpr std::strong_ordering
    operator<=>(const Rads &other) const = default;

    constexpr void Normilize();

    [[nodiscard]] constexpr std::pair<TrigonometryResult, TrigonometryResult>
    SinCos() const;

private:
    static constexpr CORDICTable kCORDICTable{};

    FixedPoint<kFractionalBits> value_;
};

constexpr Rads operator+(Rads first, const Rads &second);
constexpr Rads operator-(Rads first, const Rads &second);
template <int kFractionBits>
constexpr Rads operator*(Rads first, FixedPoint<kFractionBits> second);
template <int kFractionBits>
constexpr Rads operator*(FixedPoint<kFractionBits> first, Rads second);
template <int kFractionBits>
constexpr Rads operator/(Rads first, FixedPoint<kFractionBits> second);

constexpr Rads::Rads(int value, int divider) : value_(value, divider) {}

constexpr Rads::Rads(double value) : value_(value) {}

constexpr Rads Rads::operator+() const
{
    assert(value_ >= kMinValue);
    assert(value_ <= kMaxValue);
    return *this;
}

constexpr Rads Rads::operator-() const
{
    assert(value_ >= kMinValue);
    assert(value_ <= kMaxValue);
    Rads result = *this;
    result.value_ = -result.value_;
    return result;
}

constexpr Rads &Rads::operator+=(const Rads &other)
{
    assert(value_ >= kMinValue);
    assert(value_ <= kMaxValue);
    assert(other.value_ >= kMinValue);
    assert(other.value_ <= kMaxValue);
    value_ += other.value_;
    return *this;
}

constexpr Rads &Rads::operator-=(const Rads &other)
{
    assert(value_ >= kMinValue);
    assert(value_ <= kMaxValue);
    assert(other.value_ >= kMinValue);
    assert(other.value_ <= kMaxValue);
    value_ -= other.value_;
    return *this;
}

template <int kOtherFractionBits>
constexpr Rads &Rads::operator*=(FixedPoint<kOtherFractionBits> other)
{
    assert(value_ >= kMinValue);
    assert(value_ <= kMaxValue);
    value_ *= other;
    return *this;
}

template <int kOtherFractionBits>
constexpr Rads &Rads::operator/=(FixedPoint<kOtherFractionBits> other)
{
    assert(value_ >= kMinValue);
    assert(value_ <= kMaxValue);
    assert(other != FixedPoint<kOtherFractionBits>(0));
    value_ /= other;
    return *this;
}

constexpr Rads operator+(Rads first, const Rads &second)
{
    first += second;
    return first;
}

constexpr Rads operator-(Rads first, const Rads &second)
{
    first -= second;
    return first;
}

template <int kFractionBits>
constexpr Rads operator*(Rads first, FixedPoint<kFractionBits> second)
{
    first *= second;
    return first;
}

template <int kFractionBits>
constexpr Rads operator*(FixedPoint<kFractionBits> first, Rads second)
{
    second *= first;
    return second;
}

template <int kFractionBits>
constexpr Rads operator/(Rads first, FixedPoint<kFractionBits> second)
{
    first /= second;
    return first;
}

constexpr void Rads::Normilize()
{
    if (value_ < -kPi)
    {
        value_ += kMaxValue;
    }
    else if (value_ > kPi)
    {
        value_ -= kMaxValue;
    }
}

constexpr std::pair<TrigonometryResult, TrigonometryResult> Rads::SinCos() const
{
    constexpr auto kHalfPi = FixedPoint<kFractionalBits>(std::numbers::pi / 2);
    auto current_diff = value_;
    if (current_diff > kHalfPi)
    {
        current_diff = kPi - current_diff;
    }
    else if (current_diff < -kHalfPi)
    {
        current_diff = -kPi - current_diff;
    }

    auto x_coordinate = kCORDICTable.x_shift;
    auto y_coordinate = FixedPoint<kFractionalBits>(0);

    for (int i = 0; i < CORDICTable::kAtanTableSize; i++)
    {
        FixedPoint<kFractionalBits> new_x_coordinate = 0;
        FixedPoint<kFractionalBits> new_y_coordinate = 0;
        if (current_diff >= 0)
        {
            current_diff -= kCORDICTable.atans[i];
            new_x_coordinate = x_coordinate - (y_coordinate >> i);
            new_y_coordinate = y_coordinate + (x_coordinate >> i);
        }
        else if (current_diff < 0)
        {
            current_diff += kCORDICTable.atans[i];
            new_x_coordinate = x_coordinate + (y_coordinate >> i);
            new_y_coordinate = y_coordinate - (x_coordinate >> i);
        }
        // else
        // {
        //     break;
        // }
        x_coordinate = new_x_coordinate;
        y_coordinate = new_y_coordinate;
    }

    TrigonometryResult cos_value = TrigonometryResult(x_coordinate);

    if (value_ > kHalfPi || value_ < -kHalfPi)
    {
        cos_value = -cos_value;
    }

    return {TrigonometryResult(y_coordinate), cos_value};
}
} // namespace hydrolib::math
