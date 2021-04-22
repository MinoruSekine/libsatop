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
class SubTest
    : public ::testing::Test {
 protected:
  using type = T;
  using Limits = std::numeric_limits<T>;
};

using MyTypes = ::testing::Types<uint8_t, uint16_t, uint32_t>;
// This strange 3rd argument omission is quick hack
// for warning with Google Test Framework.
// See https://github.com/google/googletest/issues/2271#issuecomment-665742471 .
// cppcheck-suppress syntaxError
TYPED_TEST_SUITE(SubTest, MyTypes, );  // NOLINT

TYPED_TEST(SubTest, Saturated) {
  constexpr const auto kMinValue = TestFixture::Limits::min();
  constexpr const auto kZero = static_cast<typename TestFixture::type>(0);
  EXPECT_EQ(kZero, saturated::sub(kZero, kMinValue));
  constexpr const auto kOne  = static_cast<typename TestFixture::type>(1);
  constexpr const auto kMinValuePlusOne =
      static_cast<typename TestFixture::type>(kMinValue + kOne);
  EXPECT_EQ(kZero, saturated::sub(kMinValue, kMinValuePlusOne));
}

TYPED_TEST(SubTest, NotSaturated) {
  constexpr const auto kMinValue = TestFixture::Limits::min();
  constexpr const auto kZero = static_cast<typename TestFixture::type>(0);
  EXPECT_EQ(static_cast<typename TestFixture::type>(kMinValue - kZero),
            saturated::sub(kMinValue, kZero));
  constexpr const auto kOne  = static_cast<typename TestFixture::type>(1);
  constexpr const auto kMinValuePlusOne =
      static_cast<typename TestFixture::type>(kMinValue + kOne);
  EXPECT_EQ(static_cast<typename TestFixture::type>(kMinValuePlusOne - kZero),
            saturated::sub(kMinValuePlusOne, kZero));
  EXPECT_EQ(static_cast<typename TestFixture::type>(kMinValuePlusOne - kOne),
            saturated::sub(kMinValuePlusOne, kOne));
}
