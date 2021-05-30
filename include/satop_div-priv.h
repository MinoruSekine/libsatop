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

#ifndef INCLUDE_SATOP_DIV_PRIV_H_
#define INCLUDE_SATOP_DIV_PRIV_H_

#ifndef SATOP_INTERNAL
#error Do not include this file directly, libsatop.h instead.
#endif

#include <limits>

#include "satop_sign_util-priv.h"

namespace saturated {

/// @addtogroup libsatop
///
/// @{

/// Divide 2 values with saturation.
///
/// @tparam T Type of arguments and the return value
///
/// @param x A value to divtiply
/// @param y A value to divtiply
///
/// @return If divtiply results causes overflow, returns max of T.
///         If underflow, returns min(lowest) of T.
///         If no overflow and no underflow, returns x + y.
template <typename T>
constexpr T div(T x, T y) {
  return static_cast<T>(x / y);
}

/// @}

}  // namespace saturated

#endif  // INCLUDE_SATOP_DIV_PRIV_H_
