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

#ifndef INCLUDE_SATOP_H_
#define INCLUDE_SATOP_H_

#include <string>
#include <type_traits>

#define SATOP_INTERNAL

#include "satop_add-priv.h"
#include "satop_div-priv.h"
#include "satop_mul-priv.h"
#include "satop_sub-priv.h"

#undef SATOP_INTERNAL

#endif  // INCLUDE_SATOP_H_
