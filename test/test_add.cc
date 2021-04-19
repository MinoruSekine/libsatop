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

#include <cstdint>
#include <limits>

#include "gtest_compat.h"

#include "satop.h"

template <typename T>
class AddTest
    : public ::testing::Test {
 protected:
  using Limits = std::numeric_limits<T>;
};

using MyTypes = ::testing::Types<uint8_t, uint16_t, uint32_t>;
// This strange 3rd argument omission is quick hack
// for warning with Google Test Framework.
// See https://github.com/google/googletest/issues/2271#issuecomment-665742471 .
// cppcheck-suppress syntaxError
TYPED_TEST_SUITE(AddTest, MyTypes, );  // NOLINT

TYPED_TEST(AddTest, Saturated) {
  constexpr const auto max_value = TestFixture::Limits::max();
  constexpr const auto min_value = TestFixture::Limits::min();
  EXPECT_EQ(max_value, saturated::add(max_value, min_value));
  EXPECT_EQ(max_value, saturated::add(min_value, max_value));
  EXPECT_EQ(max_value, saturated::add(max_value, max_value));
}

TYPED_TEST(AddTest, NotSaturated) {
  constexpr const auto x = TestFixture::Limits::max() - 2;
  constexpr const decltype(x) y = 1;
  EXPECT_EQ(x + y, saturated::add(x, y));
  EXPECT_EQ(x + y, saturated::add(y, x));
}
