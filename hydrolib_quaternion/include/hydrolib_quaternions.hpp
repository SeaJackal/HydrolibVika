#pragma once

#include <cassert>
#include <cmath>

#include "hydrolib_arythmetic_concept.hpp"

namespace hydrolib::math
{

template <ArithmeticConcept Number>
struct Quaternion
{
    static constexpr Number Dot(const Quaternion<Number> &first,
                                const Quaternion<Number> &second);
    static constexpr Quaternion<Number>
    Multiply(const Quaternion<Number> &first, const Quaternion<Number> &second);

    [[nodiscard]] constexpr Number GetNorm() const;
    constexpr void Normalize();
    [[nodiscard]] constexpr Quaternion<Number> GetConjugated() const;

    constexpr Quaternion<Number> operator!() const;
    constexpr Quaternion<Number> operator-() const;
    constexpr Quaternion<Number> &operator+=(const Quaternion<Number> &second);
    constexpr Quaternion<Number> &operator-=(const Quaternion<Number> &second);

    Number x;
    Number y;
    Number z;
    Number w;
};

template <ArithmeticConcept Number>
constexpr Quaternion<Number> operator+(const Quaternion<Number> &first,
                                       const Quaternion<Number> &second);
template <ArithmeticConcept Number>
constexpr Quaternion<Number> operator-(const Quaternion<Number> &first,
                                       const Quaternion<Number> &second);
template <ArithmeticConcept Number>
constexpr Quaternion<Number> operator*(Number multiplier,
                                       const Quaternion<Number> &first);
template <ArithmeticConcept Number>
constexpr Quaternion<Number> operator*(const Quaternion<Number> &first,
                                       Number multiplier);
template <ArithmeticConcept Number>
constexpr Quaternion<Number> operator/(const Quaternion<Number> &first,
                                       Number divider);

template <ArithmeticConcept Number>
constexpr Quaternion<Number> &
Quaternion<Number>::operator+=(const Quaternion<Number> &second)
{
    x += second.x;
    y += second.y;
    z += second.z;
    w += second.w;
    return *this;
}

template <ArithmeticConcept Number>
constexpr Quaternion<Number> &
Quaternion<Number>::operator-=(const Quaternion<Number> &second)
{
    *this += -second;
    return *this;
}

template <ArithmeticConcept Number>
constexpr Quaternion<Number> Quaternion<Number>::operator-() const
{
    return Quaternion<Number>({.x = -x, .y = -y, .z = -z, .w = -w});
}

template <ArithmeticConcept Number>
constexpr Quaternion<Number> operator+(const Quaternion<Number> &first,
                                       const Quaternion<Number> &second)
{
    Quaternion<Number> result = first;
    result += second;
    return result;
}

template <ArithmeticConcept Number>
constexpr Quaternion<Number> operator-(const Quaternion<Number> &first,
                                       const Quaternion<Number> &second)
{
    Quaternion<Number> result = first;
    result -= second;
    return result;
}

template <ArithmeticConcept Number>
constexpr Quaternion<Number>
Quaternion<Number>::Multiply(const Quaternion<Number> &first,
                             const Quaternion<Number> &second)
{
    return Quaternion<Number>(
        {.x = (first.x * second.w) + (first.w * second.x) +
              (first.y * second.z) - (first.z * second.y),
         .y = (first.z * second.x) + (first.y * second.w) +
              (first.w * second.y) - (first.x * second.z),
         .z = (first.w * second.z) + (first.x * second.y) -
              (first.y * second.x) + (first.z * second.w),
         .w = (first.w * second.w) - (first.y * second.y) -
              (first.z * second.z) - (first.x * second.x)});
}

template <ArithmeticConcept Number>
constexpr Quaternion<Number> Quaternion<Number>::GetConjugated() const
{
    return Quaternion<Number>({.x = -x, .y = -y, .z = -z, .w = w});
}

template <ArithmeticConcept Number>
constexpr Quaternion<Number> Quaternion<Number>::operator!() const
{
    return GetConjugated();
}

template <ArithmeticConcept Number>
constexpr Quaternion<Number> operator*(Number multiplier,
                                       const Quaternion<Number> &first)
{
    return Quaternion<Number>({.x = first.x * multiplier,
                               .y = first.y * multiplier,
                               .z = first.z * multiplier,
                               .w = first.w * multiplier});
}

template <ArithmeticConcept Number>
constexpr Quaternion<Number> operator*(const Quaternion<Number> &first,
                                       Number multiplier)
{
    return multiplier * first;
}

template <ArithmeticConcept Number>
constexpr Quaternion<Number> operator/(const Quaternion<Number> &first,
                                       Number divider)
{
    return Quaternion<Number>({.x = first.x / divider,
                               .y = first.y / divider,
                               .z = first.z / divider,
                               .w = first.w / divider});
}

template <ArithmeticConcept Number>
constexpr Number Quaternion<Number>::Dot(const Quaternion<Number> &first,
                                         const Quaternion<Number> &second)
{
    return (first.x * second.x) + (first.y * second.y) + (first.z * second.z) +
           (first.w * second.w);
}

template <ArithmeticConcept Number>
constexpr Number Quaternion<Number>::GetNorm() const
{
    return sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

template <ArithmeticConcept Number>
constexpr void Quaternion<Number>::Normalize()
{
    Number norm = GetNorm();
    assert(norm != 0);
    *this = *this / norm;
}

} // namespace hydrolib::math
