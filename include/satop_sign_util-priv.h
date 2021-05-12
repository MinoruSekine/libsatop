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

#ifndef INCLUDE_SATOP_SIGN_UTIL_PRIV_H_
#define INCLUDE_SATOP_SIGN_UTIL_PRIV_H_

#ifndef SATOP_INTERNAL
#error Do not include this file directly, libsatop.h instead.
#endif

#include <type_traits>

namespace saturated {

namespace impl {

template <typename T>
constexpr bool csignbit(T value) {
  return (std::is_signed<T>::value && (value < 0));
}

}  // namespace impl

}  // namespace saturated

#endif  // INCLUDE_SATOP_SIGN_UTIL_PRIV_H_
