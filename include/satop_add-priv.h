//
// Copyright 2021 Minoru Sekine
//
// This file is part of libsatop.
//
// libsatop is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libsatop is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with libsatop.  If not, see <http://www.gnu.org/licenses/>.

#ifndef INCLUDE_SATOP_ADD_PRIV_H_
#define INCLUDE_SATOP_ADD_PRIV_H_

#ifndef SATOP_INTERNAL
#error Do not include this file directly, libsatop.h instead.
#endif

#include <limits>

namespace saturated {

namespace impl {

template <typename T>
constexpr T is_add_overflow(T x, T y) {
  return ((x > 0)
          && (y > 0)
          && (x >= std::numeric_limits<T>::max() - y));
}

template <typename T>
constexpr bool is_add_underflow(
    T x,
    typename std::enable_if<std::is_unsigned<T>::value, T>::type y) {
  return static_cast<void>(x), static_cast<void>(y), false;
}

template <typename T>
constexpr bool is_add_underflow(
    T x,
    typename std::enable_if<std::is_signed<T>::value, T>::type y) {
  return ((x < 0)
          && (y < 0)
          && ((x < std::numeric_limits<T>::min() - y)
              || (y < std::numeric_limits<T>::min() - x)));
}

}  // namespace impl

/// @addtogroup libsatop
///
/// @{

/// Add 2 values with saturation.
///
/// @tparam T Type of arguments and the return value
///
/// @param x A value to add
/// @param y A value to add
///
/// @return If addition results causes overflow, returns max of T.
///         If no overflow, returns x + y.
template <typename T>
constexpr T add(T x, T y) {
  using limits = std::numeric_limits<T>;
  return (impl::is_add_overflow(x, y)
          ? limits::max()
          : (impl::is_add_underflow(x, y)
             ? limits::min()
             : static_cast<T>(x + y)));
}

/// @}

}  // namespace saturated

#endif  // INCLUDE_SATOP_ADD_PRIV_H_
