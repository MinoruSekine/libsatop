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
class AddOverflowTest
    : public ::testing::Test {
 protected:
  using Limits = std::numeric_limits<T>;
  using test_target_t = T;
};

using TypesForOverflowTests = ::testing::Types<uint8_t, uint16_t, uint32_t,
                                               int8_t, int16_t, int32_t>;
// This strange 3rd argument omission is quick hack
// for warning with Google Test Framework.
// See https://github.com/google/googletest/issues/2271#issuecomment-665742471 .
// cppcheck-suppress syntaxError
TYPED_TEST_SUITE(AddOverflowTest, TypesForOverflowTests, );  // NOLINT

TYPED_TEST(AddOverflowTest, Overflow) {
  constexpr const auto kMaxValue = TestFixture::Limits::max();
  constexpr const typename TestFixture::test_target_t kPositiveMinValue(1);
  EXPECT_EQ(kMaxValue, saturated::add(kMaxValue, kPositiveMinValue));
  EXPECT_EQ(kMaxValue, saturated::add(kPositiveMinValue, kMaxValue));
  EXPECT_EQ(kMaxValue, saturated::add(kMaxValue, kMaxValue));
}

TYPED_TEST(AddOverflowTest, NotOverflow) {
  constexpr const auto x = TestFixture::Limits::max() - 2;
  constexpr const decltype(x) y = 1;
  EXPECT_EQ(x + y, saturated::add(x, y));
  EXPECT_EQ(x + y, saturated::add(y, x));
}

template <typename T>
class AddUnderflowTest
    : public ::testing::Test {
 protected:
  using Limits = std::numeric_limits<T>;
  using test_target_t = T;
};

using TypesForUnderflowTests = ::testing::Types<int8_t, int16_t, int32_t>;
// This strange 3rd argument omission is quick hack
// for warning with Google Test Framework.
// See https://github.com/google/googletest/issues/2271#issuecomment-665742471 .
TYPED_TEST_SUITE(AddUnderflowTest, TypesForUnderflowTests, );  // NOLINT

TYPED_TEST(AddUnderflowTest, Underflow) {
  constexpr const auto kLowest = TestFixture::Limits::lowest();
  constexpr const typename TestFixture::test_target_t kMinusOne(-1);
  EXPECT_EQ(kLowest, saturated::add(kLowest, kMinusOne));
  EXPECT_EQ(kLowest, saturated::add(kMinusOne, kLowest));
  EXPECT_EQ(kLowest, saturated::add(kLowest, kLowest));
}

TYPED_TEST(AddUnderflowTest, NotUnderflow) {
  constexpr const typename TestFixture::test_target_t kMinusOne(-1);
  EXPECT_EQ(
      static_cast<typename TestFixture::test_target_t>(kMinusOne + kMinusOne),
      saturated::add(kMinusOne, kMinusOne));
}
