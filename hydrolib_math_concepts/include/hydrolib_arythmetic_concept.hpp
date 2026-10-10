#pragma once

#include <concepts>

namespace hydrolib::math {
template <typename T>
concept ArithmeticConcept = requires(T first, T second) {
  { first + second } -> std::convertible_to<T>;
  { first - second } -> std::convertible_to<T>;
  { first * second } -> std::convertible_to<T>;
  { sqrt(first) } -> std::convertible_to<T>;
  { first / second } -> std::convertible_to<T>;
  { -first } -> std::convertible_to<T>;
  { first += second } -> std::same_as<T &>;
  { first -= second } -> std::same_as<T &>;
  { first *= second } -> std::same_as<T &>;
  { first /= second } -> std::same_as<T &>;
};
} // namespace hydrolib::math
