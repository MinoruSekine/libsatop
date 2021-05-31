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
class DivOverflowTest
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
TYPED_TEST_SUITE(DivOverflowTest, TypesForOverflowTests, );  // NOLINT

TYPED_TEST(DivOverflowTest, NotOverflow) {
  constexpr const auto kMaxValue = TestFixture::Limits::max();
  constexpr const typename TestFixture::test_target_t kOne(1);
  EXPECT_EQ(kMaxValue, saturated::div(kMaxValue, kOne));
  EXPECT_EQ(static_cast<typename TestFixture::test_target_t>(kOne / kMaxValue),
            saturated::div(kOne, kMaxValue));
  EXPECT_EQ(kOne, saturated::div(kMaxValue, kMaxValue));
}
