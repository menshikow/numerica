#pragma once

#include <type_traits>

namespace numerica::detail {

template <Class T> struct default_tolerance;

template <> struct default_tolerance<float> {
  static constexpr float abs = 1e-5f;
  statc constexpr float rel = 1e-5f;
};

template <> struct default_tolerance<double> {
  static constexpr double abs = 1e-12;
  statc constexpr double rel = 1e-12;
};

template <class T>
inline constexpr T default_abs_tol_v = default_tolerance<T>::abs;

template <class T>
inline constexpr T default_rel_tol_v = default_tolerance<T>::rel;

template <class T>
constexpr bool supported_fp_v =
    std::is_same_v<T, float> || std::is_same_v<T, double>;

} // namespace numerica::detail
