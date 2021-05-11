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

namespace {

template <typename T>
T GetRootOfMax() {
  constexpr const T kMax = std::numeric_limits<T>::max();
  T root_of_max = 1;
  for (root_of_max = 1; kMax / root_of_max >= root_of_max; ++root_of_max) ;

  --root_of_max;

  return root_of_max;
}

}  // namespace

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
  constexpr const typename TestFixture::test_target_t kTwo(2);
  EXPECT_EQ(kMaxValue, saturated::mul(kMaxValue, kTwo));
  EXPECT_EQ(kMaxValue, saturated::mul(kTwo, kMaxValue));
  EXPECT_EQ(kMaxValue, saturated::mul(kMaxValue, kMaxValue));

  const auto kRootOfMax = GetRootOfMax<typename TestFixture::test_target_t>();
  const auto kRootOfMaxPlus1 =
      static_cast<typename TestFixture::test_target_t>(kRootOfMax + 1);
  EXPECT_EQ(kMaxValue, saturated::mul(kRootOfMaxPlus1, kRootOfMaxPlus1));
}

TYPED_TEST(AddOverflowTest, NotOverflow) {
  constexpr const auto kMaxValue = TestFixture::Limits::max();
  constexpr const typename TestFixture::test_target_t kOne(1);
  EXPECT_EQ(kMaxValue, saturated::mul(kMaxValue, kOne));
  EXPECT_EQ(kMaxValue, saturated::mul(kOne, kMaxValue));

  const auto kRootOfMax = GetRootOfMax<typename TestFixture::test_target_t>();
  EXPECT_EQ(kRootOfMax * kRootOfMax, saturated::mul(kRootOfMax, kRootOfMax));
}

template <typename T>
class MulUnderflowTest
    : public ::testing::Test {
 protected:
  using Limits = std::numeric_limits<T>;
  using test_target_t = T;
};

using TypesForUnderflowTests = ::testing::Types<int8_t, int16_t, int32_t>;
// This strange 3rd argument omission is quick hack
// for warning with Google Test Framework.
// See https://github.com/google/googletest/issues/2271#issuecomment-665742471 .
TYPED_TEST_SUITE(MulUnderflowTest, TypesForUnderflowTests, );  // NOLINT

TYPED_TEST(MulUnderflowTest, Underflow) {
  constexpr const auto kLowest = TestFixture::Limits::lowest();
  constexpr const typename TestFixture::test_target_t kTwo(2);
  EXPECT_EQ(kLowest, saturated::mul(kLowest, kTwo));
  EXPECT_EQ(kLowest, saturated::mul(kTwo, kLowest));
}

TYPED_TEST(MulUnderflowTest, NotUnderflow) {
  constexpr const auto kLowest = TestFixture::Limits::lowest();
  constexpr const typename TestFixture::test_target_t kThree(3);
  constexpr const typename TestFixture::test_target_t kLowestDivThree =
      static_cast<typename TestFixture::test_target_t>(kLowest / kThree);
  constexpr const typename TestFixture::test_target_t kMulResult =
      static_cast<typename TestFixture::test_target_t>(kLowestDivThree
                                                       * kThree);
  EXPECT_EQ(kMulResult, saturated::mul(kLowestDivThree, kThree));
  EXPECT_EQ(kMulResult, saturated::mul(kThree, kLowestDivThree));
}
