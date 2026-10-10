#pragma once

#include <climits>
#include <cmath>
#include <compare>
#include <cstdint>

namespace hydrolib::math
{

template <int kFractionBitsParam>
class FixedPoint
{
    template <int>
    friend class FixedPoint;

public:
    static constexpr int kFractionBits = kFractionBitsParam;
    static constexpr int kUpperNotIncludedBound =
        (INT_MAX >> kFractionBitsParam) + 1;
    static constexpr int kLowerNotIncludedBound = INT_MIN >> kFractionBitsParam;
    static constexpr double kLeastBitValue = 1.0 / (1 << kFractionBitsParam);

    constexpr FixedPoint();
    constexpr FixedPoint(int value); // NOLINT
    constexpr FixedPoint(int value, int divider);
    constexpr FixedPoint(float value);       // NOLINT
    constexpr FixedPoint(double value);      // NOLINT
    constexpr FixedPoint(long double value); // NOLINT
    template <int kOtherFractionBits>
    constexpr explicit FixedPoint(FixedPoint<kOtherFractionBits> value);

    explicit constexpr operator double() const;
    explicit constexpr operator int() const;

    constexpr FixedPoint &operator+=(const FixedPoint &other);
    constexpr FixedPoint &operator-=(const FixedPoint &other);
    constexpr FixedPoint operator-() const;
    template <int kOtherFractionBits>
    constexpr FixedPoint &operator*=(FixedPoint<kOtherFractionBits> other);
    template <int kOtherFractionBits>
    constexpr FixedPoint &operator/=(FixedPoint<kOtherFractionBits> other);
    constexpr FixedPoint &operator*=(int other);
    constexpr FixedPoint &operator/=(int other);

    constexpr std::strong_ordering
    operator<=>(const FixedPoint &other) const = default;

private:
    int value_;
};

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>
operator+(FixedPoint<kFractionBitsParam> first,
          FixedPoint<kFractionBitsParam> second);

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>
operator-(FixedPoint<kFractionBitsParam> first,
          FixedPoint<kFractionBitsParam> second);

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>
operator*(FixedPoint<kFractionBitsParam> first,
          FixedPoint<kFractionBitsParam> second);

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>
operator/(FixedPoint<kFractionBitsParam> first,
          FixedPoint<kFractionBitsParam> second);

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>
operator*(FixedPoint<kFractionBitsParam> first, int second);

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>
operator/(FixedPoint<kFractionBitsParam> first, int second);

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>
operator*(int first, FixedPoint<kFractionBitsParam> second);

template <int kFractionBitsParam>
constexpr int &operator*=(int &first, FixedPoint<kFractionBitsParam> second);

template <int kFractionBitsParam>
constexpr bool operator==(FixedPoint<kFractionBitsParam> first,
                          FixedPoint<kFractionBitsParam> second);
template <int kFractionBitsParam>
constexpr bool operator!=(FixedPoint<kFractionBitsParam> first,
                          FixedPoint<kFractionBitsParam> second);
template <int kFractionBitsParam>
constexpr bool operator<(FixedPoint<kFractionBitsParam> first,
                         FixedPoint<kFractionBitsParam> second);
template <int kFractionBitsParam>
constexpr bool operator<=(FixedPoint<kFractionBitsParam> first,
                          FixedPoint<kFractionBitsParam> second);
template <int kFractionBitsParam>
constexpr bool operator>(FixedPoint<kFractionBitsParam> first,
                         FixedPoint<kFractionBitsParam> second);
template <int kFractionBitsParam>
constexpr bool operator>=(FixedPoint<kFractionBitsParam> first,
                          FixedPoint<kFractionBitsParam> second);

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>::FixedPoint() : value_(0)
{
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>::FixedPoint(int value)
    : value_(value << kFractionBitsParam)
{
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>::FixedPoint(int value, int divider)
    : value_((static_cast<int64_t>(value) << kFractionBitsParam) / divider)
{
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>::FixedPoint(float value)
    : value_(static_cast<int>(value * (1 << kFractionBitsParam)))
{
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>::FixedPoint(double value)
    : value_(static_cast<int>(value * (1 << kFractionBitsParam)))
{
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>::FixedPoint(
    long double value) // NOLINT
    : value_(static_cast<int>(value * (1 << kFractionBitsParam)))
{
}

template <int kFractionBitsParam>
template <int kOtherFractionBits>
constexpr FixedPoint<kFractionBitsParam>::FixedPoint(
    FixedPoint<kOtherFractionBits> value)
    : value_(0)
{
    if constexpr (kFractionBitsParam > kOtherFractionBits)
    {
        value_ = value.value_ << (kFractionBitsParam - kOtherFractionBits);
    }
    else
    {
        value_ = value.value_ >> (kOtherFractionBits - kFractionBitsParam);
    }
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>::operator double() const
{
    return static_cast<double>(value_) / (1 << kFractionBitsParam);
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>::operator int() const
{
    if (value_ < 0)
    {
        return -((-value_) >> kFractionBitsParam);
    }
    return value_ >> kFractionBitsParam;
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>
FixedPoint<kFractionBitsParam>::operator-() const
{
    FixedPoint<kFractionBitsParam> result = *this;
    result.value_ = -result.value_;
    return result;
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam> &
FixedPoint<kFractionBitsParam>::operator+=(
    const FixedPoint<kFractionBitsParam> &other)
{
    value_ += other.value_;
    return *this;
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam> &
FixedPoint<kFractionBitsParam>::operator-=(
    const FixedPoint<kFractionBitsParam> &other)
{
    *this += -other;
    return *this;
}

template <int kFractionBitsParam>
template <int kOtherFractionBits>
constexpr FixedPoint<kFractionBitsParam> &
FixedPoint<kFractionBitsParam>::operator*=(FixedPoint<kOtherFractionBits> other)
{
    value_ =
        (static_cast<int64_t>(value_) * other.value_) >> kOtherFractionBits;
    return *this;
}

template <int kFractionBitsParam>
template <int kOtherFractionBits>
constexpr FixedPoint<kFractionBitsParam> &
FixedPoint<kFractionBitsParam>::operator/=(FixedPoint<kOtherFractionBits> other)
{
    value_ =
        (static_cast<int64_t>(value_) << kOtherFractionBits) / other.value_;
    return *this;
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam> &
FixedPoint<kFractionBitsParam>::operator*=(int other)
{
    value_ *= other;
    return *this;
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam> &
FixedPoint<kFractionBitsParam>::operator/=(int other)
{
    value_ /= other;
    return *this;
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>
operator+(FixedPoint<kFractionBitsParam> first,
          FixedPoint<kFractionBitsParam> second)
{
    FixedPoint<kFractionBitsParam> result = first;
    result += second;
    return result;
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>
operator-(FixedPoint<kFractionBitsParam> first,
          FixedPoint<kFractionBitsParam> second)
{
    FixedPoint<kFractionBitsParam> result = first;
    result -= second;
    return result;
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>
operator*(FixedPoint<kFractionBitsParam> first,
          FixedPoint<kFractionBitsParam> second)
{
    FixedPoint<kFractionBitsParam> result = first;
    result *= second;
    return result;
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>
operator/(FixedPoint<kFractionBitsParam> first,
          FixedPoint<kFractionBitsParam> second)
{
    FixedPoint<kFractionBitsParam> result = first;
    result /= second;
    return result;
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>
operator*(FixedPoint<kFractionBitsParam> first, int second)
{
    FixedPoint<kFractionBitsParam> result = first;
    result *= second;
    return result;
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>
operator/(FixedPoint<kFractionBitsParam> first, int second)
{
    FixedPoint<kFractionBitsParam> result = first;
    result /= second;
    return result;
}

template <int kFractionBitsParam>
constexpr FixedPoint<kFractionBitsParam>
operator*(int first, FixedPoint<kFractionBitsParam> second)
{
    return second * first;
}

template <int kFractionBitsParam>
constexpr int &operator*=(int &first, FixedPoint<kFractionBitsParam> second)
{
    first = first * second;
    return first;
}
} // namespace hydrolib::math
