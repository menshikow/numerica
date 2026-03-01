#pragma once

#include <cmath>
#include <type_traits>

namespace numerica::detail {

template <class T> constexpr bool is_finite(T x) noexcept {
  static_assert(std::is_floating_point_v<T>,
                "is_finite requires floating point");
  return std::isfinite(x);
}

template <class T> constexpr T abs(T x) noexcept { return x < T(0) ? -x : x; }

template <class T> constexpr T max(T a, T b) noexcept { return a < b ? b : a; }

/**
  Combined abs+rel tolerance compare for scalar values.
  |a - b| <= abs_eps + rel_eps * max(|a|, |b|)
**/

template <class T>
constexpr bool nearly_equal(T a, T b, T abs_eps, T rel_eps) noexcept {
  static_assert(std::is_floating_point_v<T>,
                "nearly_equal requires floating point");
  const T diff = abs(a - b);
  const T scale = max(abs(a), abs(b));
  return diff <= abs_eps + rel_eps * scale;
}

// TODO: get the description for every function

} // namespace numerica::detail
