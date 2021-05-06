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

#ifndef INCLUDE_SATOP_SUB_PRIV_H_
#define INCLUDE_SATOP_SUB_PRIV_H_

#ifndef SATOP_INTERNAL
#error Do not include this file directly, libsatop.h instead.
#endif

#include <limits>

namespace saturated {

namespace impl {

template <typename T>
constexpr bool is_sub_underflow(T x, T y) {
  return (x < std::numeric_limits<T>::lowest() + y);
}

}  // namespace impl

/// Subtract 2 values with saturation.
///
/// @tparam T Type of arguments and the return value
///
/// @param x Subtract from this value
/// @param y Subtract this value
///
/// @return If subtraction results causes underflow, returns min of T.
///         If no underflow, returns x - y.
template <typename T>
constexpr T sub(T x, T y) {
  return (impl::is_sub_underflow(x, y)
          ? std::numeric_limits<T>::lowest()
          : static_cast<T>(x - y));
}

}  // namespace saturated

#endif  // INCLUDE_SATOP_SUB_PRIV_H_
