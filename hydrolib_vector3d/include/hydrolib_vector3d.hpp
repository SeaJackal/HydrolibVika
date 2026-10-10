#pragma once

#include "hydrolib_arythmetic_concept.hpp"

namespace hydrolib::math
{
template <ArithmeticConcept Number>
struct Vector3D
{
    static constexpr Number Dot(const Vector3D &first, const Vector3D &second);
    static constexpr Vector3D Cross(const Vector3D &first,
                                    const Vector3D &second);

    [[nodiscard]] constexpr Number GetLength() const;
    constexpr void Normalize();

    constexpr Vector3D<Number> operator-() const;
    constexpr Vector3D<Number> &operator+=(const Vector3D<Number> &second);
    constexpr Vector3D<Number> &operator-=(const Vector3D<Number> &second);
    constexpr Vector3D<Number> &operator*=(Number scalar);
    constexpr Vector3D<Number> &operator/=(Number scalar);

    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
    Number x{};
    Number y{};
    Number z{};
    // NOLINTEND(misc-non-private-member-variables-in-classes)
};

template <ArithmeticConcept Number>
constexpr Vector3D<Number> operator+(const Vector3D<Number> &first,
                                     const Vector3D<Number> &second);

template <ArithmeticConcept Number>
constexpr Vector3D<Number> operator-(const Vector3D<Number> &first,
                                     const Vector3D<Number> &second);
template <ArithmeticConcept Number>
constexpr Vector3D<Number> operator*(const Vector3D<Number> &vector,
                                     Number scalar);

template <ArithmeticConcept Number>
constexpr Vector3D<Number> operator*(Number scalar,
                                     const Vector3D<Number> &vector);

template <ArithmeticConcept Number>
constexpr Vector3D<Number> operator/(const Vector3D<Number> &vector,
                                     Number scalar);

template <ArithmeticConcept Number>
constexpr Number Vector3D<Number>::Dot(const Vector3D &first,
                                       const Vector3D &second)
{
    return (first.x * second.x) + (first.y * second.y) + (first.z * second.z);
}

template <ArithmeticConcept Number>
constexpr Vector3D<Number> Vector3D<Number>::Cross(const Vector3D &first,
                                                   const Vector3D &second)
{
    return Vector3D<Number>(first.y * second.z - first.z * second.y,
                            first.z * second.x - first.x * second.z,
                            first.x * second.y - first.y * second.x);
}

template <ArithmeticConcept Number>
constexpr Number Vector3D<Number>::GetLength() const
{
    return sqrt(x * x + y * y + z * z);
}

template <ArithmeticConcept Number>
constexpr void Vector3D<Number>::Normalize()
{
    auto len = GetLength();
    assert(len != 0);
    *this /= len;
}

template <ArithmeticConcept Number>
constexpr Vector3D<Number> Vector3D<Number>::operator-() const
{
    return Vector3D<Number>(-x, -y, -z);
}

template <ArithmeticConcept Number>
constexpr Vector3D<Number> &
Vector3D<Number>::operator+=(const Vector3D<Number> &second)

{
    x += second.x;
    y += second.y;
    z += second.z;
    return *this;
}

template <ArithmeticConcept Number>
constexpr Vector3D<Number> &
Vector3D<Number>::operator-=(const Vector3D<Number> &second)
{
    *this += -second;
    return *this;
}

template <ArithmeticConcept Number>
constexpr Vector3D<Number> &Vector3D<Number>::operator*=(Number scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

template <ArithmeticConcept Number>
constexpr Vector3D<Number> &Vector3D<Number>::operator/=(Number scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

template <ArithmeticConcept Number>
constexpr Vector3D<Number> operator+(const Vector3D<Number> &first,
                                     const Vector3D<Number> &second)
{
    auto result = first;
    result += second;
    return result;
}

template <ArithmeticConcept Number>
constexpr Vector3D<Number> operator-(const Vector3D<Number> &first,
                                     const Vector3D<Number> &second)
{
    auto result = first;
    result -= second;
    return result;
}

template <ArithmeticConcept Number>
constexpr Vector3D<Number> operator*(const Vector3D<Number> &vector,
                                     Number scalar)
{
    return Vector3D<Number>(vector.x * scalar, vector.y * scalar,
                            vector.z * scalar);
}

template <ArithmeticConcept Number>
constexpr Vector3D<Number> operator*(Number scalar,
                                     const Vector3D<Number> &vector)
{
    return vector * scalar;
}

template <ArithmeticConcept Number>
constexpr Vector3D<Number> operator/(const Vector3D<Number> &vector,
                                     Number scalar)
{
    return Vector3D<Number>(vector.x / scalar, vector.y / scalar,
                            vector.z / scalar);
}
} // namespace hydrolib::math
