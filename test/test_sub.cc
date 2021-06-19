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
class SubUnderflowTests
    : public ::testing::Test {
 protected:
  using type = T;
  using Limits = std::numeric_limits<T>;
};

using TypesForSubUnderflowTests = ::testing::Types<uint8_t, uint16_t, uint32_t,
                                                   int8_t, int16_t, int32_t>;
// This strange 3rd argument omission is quick hack
// for warning with Google Test Framework.
// See https://github.com/google/googletest/issues/2271#issuecomment-665742471 .
// cppcheck-suppress syntaxError
TYPED_TEST_SUITE(SubUnderflowTests, TypesForSubUnderflowTests, );  // NOLINT

TYPED_TEST(SubUnderflowTests, Underflow) {
  constexpr const auto kOne  = static_cast<typename TestFixture::type>(1);
  constexpr const auto kLowestValue = TestFixture::Limits::lowest();
  EXPECT_EQ(kLowestValue, saturated::sub(kLowestValue, kOne));
}

TYPED_TEST(SubUnderflowTests, NotUnderflow) {
  constexpr const auto kLowestValue = TestFixture::Limits::lowest();
  constexpr const auto kZero = static_cast<typename TestFixture::type>(0);
  EXPECT_EQ(static_cast<typename TestFixture::type>(kLowestValue - kZero),
            saturated::sub(kLowestValue, kZero));
  constexpr const auto kOne  = static_cast<typename TestFixture::type>(1);
  constexpr const auto kLowestValuePlusOne =
      static_cast<typename TestFixture::type>(kLowestValue + kOne);
  EXPECT_EQ(
      static_cast<typename TestFixture::type>(kLowestValuePlusOne - kZero),
      saturated::sub(kLowestValuePlusOne, kZero));
  EXPECT_EQ(static_cast<typename TestFixture::type>(kLowestValuePlusOne - kOne),
            saturated::sub(kLowestValuePlusOne, kOne));
}

template <typename T>
class SubOverflowTests
    : public ::testing::Test {
 protected:
  using type = T;
  using Limits = std::numeric_limits<T>;
};

using TypesForSubOverflowTests = ::testing::Types<int8_t, int16_t, int32_t>;
// This strange 3rd argument omission is quick hack
// for warning with Google Test Framework.
// See https://github.com/google/googletest/issues/2271#issuecomment-665742471 .
TYPED_TEST_SUITE(SubOverflowTests, TypesForSubOverflowTests, );  // NOLINT

TYPED_TEST(SubOverflowTests, Overflow) {
  constexpr const auto kOne  = static_cast<typename TestFixture::type>(1);
  constexpr const auto kLowestValue = TestFixture::Limits::lowest();
  constexpr const auto kMaxValue = TestFixture::Limits::max();
  EXPECT_EQ(kMaxValue, saturated::sub(kOne, kLowestValue));
}

TYPED_TEST(SubOverflowTests, NotOverflow) {
  constexpr const auto kMinusOne = static_cast<typename TestFixture::type>(-1);
  EXPECT_EQ(kMinusOne - kMinusOne, saturated::sub(kMinusOne, kMinusOne));
}

template <typename T>
class SubFloatingOverflowTest
    : public ::testing::Test {
 protected:
  using Limits = std::numeric_limits<T>;
  using test_target_t = T;
};

using TypesForFloatingOverflowTest = ::testing::Types<float, double>;
// This strange 3rd argument omission is quick hack
// for warning with Google Test Framework.
// See https://github.com/google/googletest/issues/2271#issuecomment-665742471 .
TYPED_TEST_SUITE(SubFloatingOverflowTest,
                 TypesForFloatingOverflowTest, );  // NOLINT

TYPED_TEST(SubFloatingOverflowTest, NotOverflow) {
  constexpr const typename TestFixture::test_target_t kMax =
      TestFixture::Limits::max();
  constexpr const typename TestFixture::test_target_t kZero(0);
  EXPECT_DOUBLE_EQ(static_cast<double>(kMax - kZero),
                   static_cast<double>(saturated::sub(kMax, kZero)));
  EXPECT_DOUBLE_EQ(static_cast<double>(kZero - kMax),
                   static_cast<double>(saturated::sub(kZero, kMax)));
  constexpr const typename TestFixture::test_target_t kHalfLowest =
      TestFixture::Limits::lowest() / typename TestFixture::test_target_t(2.0f);
  EXPECT_DOUBLE_EQ(static_cast<double>(kZero - kHalfLowest),
                   static_cast<double>(saturated::sub(kZero, kHalfLowest)));
}

TYPED_TEST(SubFloatingOverflowTest, Overflow) {
  constexpr const typename TestFixture::test_target_t kMax =
      TestFixture::Limits::max();
  constexpr const typename TestFixture::test_target_t kMinusMin =
      -TestFixture::Limits::min();
  EXPECT_DOUBLE_EQ(static_cast<double>(kMax),
                   static_cast<double>(saturated::sub(kMax, kMinusMin)));
  constexpr const typename TestFixture::test_target_t kLowest =
      TestFixture::Limits::lowest();
  EXPECT_DOUBLE_EQ(static_cast<double>(kMax),
                   static_cast<double>(saturated::sub(kMax, kLowest)));
}

template <typename T>
class SubFloatingUnderflowTest
    : public ::testing::Test {
 protected:
  using Limits = std::numeric_limits<T>;
  using test_target_t = T;
};

using TypesForFloatingUnderflowTest = ::testing::Types<float, double>;
// This strange 3rd argument omission is quick hack
// for warning with Google Test Framework.
// See https://github.com/google/googletest/issues/2271#issuecomment-665742471 .
TYPED_TEST_SUITE(SubFloatingUnderflowTest,
                 TypesForFloatingUnderflowTest, );  // NOLINT

TYPED_TEST(SubFloatingUnderflowTest, NotUnderflow) {
  constexpr const typename TestFixture::test_target_t kLowest =
      TestFixture::Limits::lowest();
  constexpr const typename TestFixture::test_target_t kZero(0);
  EXPECT_DOUBLE_EQ(static_cast<double>(kLowest - kZero),
                   static_cast<double>(saturated::sub(kLowest, kZero)));
  EXPECT_DOUBLE_EQ(static_cast<double>(kZero - kLowest),
                   static_cast<double>(saturated::sub(kZero, kLowest)));
}

TYPED_TEST(SubFloatingUnderflowTest, Underflow) {
  constexpr const typename TestFixture::test_target_t kLowest =
      TestFixture::Limits::lowest();
  constexpr const typename TestFixture::test_target_t kMin =
      TestFixture::Limits::min();
  EXPECT_DOUBLE_EQ(static_cast<double>(kLowest),
                   static_cast<double>(saturated::sub(kLowest, kMin)));
  constexpr const typename TestFixture::test_target_t kMax =
      TestFixture::Limits::max();
  EXPECT_DOUBLE_EQ(static_cast<double>(kLowest),
                   static_cast<double>(saturated::sub(kLowest, kMax)));
}
