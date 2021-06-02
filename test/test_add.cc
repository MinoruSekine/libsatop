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
  constexpr const auto x =
      static_cast<typename TestFixture::test_target_t>(
          TestFixture::Limits::max() - 2);
  constexpr const decltype(x) y = 1;
  EXPECT_EQ(x + y, saturated::add(x, y));
  EXPECT_EQ(x + y, saturated::add(y, x));
}

template <typename T>
class AddSignedUnderflowTest
    : public ::testing::Test {
 protected:
  using Limits = std::numeric_limits<T>;
  using test_target_t = T;
};

using TypesForSignedUnderflowTests = ::testing::Types<int8_t, int16_t, int32_t>;
// This strange 3rd argument omission is quick hack
// for warning with Google Test Framework.
// See https://github.com/google/googletest/issues/2271#issuecomment-665742471 .
TYPED_TEST_SUITE(AddSignedUnderflowTest,
                 TypesForSignedUnderflowTests, );  // NOLINT

TYPED_TEST(AddSignedUnderflowTest, Underflow) {
  constexpr const auto kLowest = TestFixture::Limits::lowest();
  constexpr const typename TestFixture::test_target_t kMinusOne(-1);
  EXPECT_EQ(kLowest, saturated::add(kLowest, kMinusOne));
  EXPECT_EQ(kLowest, saturated::add(kMinusOne, kLowest));
  EXPECT_EQ(kLowest, saturated::add(kLowest, kLowest));
}

TYPED_TEST(AddSignedUnderflowTest, NotUnderflow) {
  constexpr const typename TestFixture::test_target_t kMinusOne(-1);
  EXPECT_EQ(
      static_cast<typename TestFixture::test_target_t>(kMinusOne + kMinusOne),
      saturated::add(kMinusOne, kMinusOne));
}

template <typename T>
class AddUnsignedUnderflowTest
    : public ::testing::Test {
 protected:
  using Limits = std::numeric_limits<T>;
  using test_target_t = T;
};

using TypesForUnsignedUnderflowTests =
    ::testing::Types<uint8_t, uint16_t, uint32_t>;
// This strange 3rd argument omission is quick hack
// for warning with Google Test Framework.
// See https://github.com/google/googletest/issues/2271#issuecomment-665742471 .
TYPED_TEST_SUITE(AddUnsignedUnderflowTest,
                 TypesForUnsignedUnderflowTests, );  // NOLINT

TYPED_TEST(AddUnsignedUnderflowTest, NotUnderflow) {
  constexpr const typename TestFixture::test_target_t kZero(0);
  constexpr const typename TestFixture::test_target_t kOne(1);
  EXPECT_EQ(static_cast<typename TestFixture::test_target_t>(kZero + kZero),
            saturated::add(kZero, kZero));
  EXPECT_EQ(static_cast<typename TestFixture::test_target_t>(kOne + kZero),
            saturated::add(kOne, kZero));
  EXPECT_EQ(static_cast<typename TestFixture::test_target_t>(kZero + kOne),
            saturated::add(kZero, kOne));
  EXPECT_EQ(static_cast<typename TestFixture::test_target_t>(kOne + kOne),
            saturated::add(kOne, kOne));
}

template <typename T>
class AddFloatingOverflowTest
    : public ::testing::Test {
 protected:
  using Limits = std::numeric_limits<T>;
  using test_target_t = T;
};

using TypesForFloatingOverflowTest = ::testing::Types<float, double>;
// This strange 3rd argument omission is quick hack
// for warning with Google Test Framework.
// See https://github.com/google/googletest/issues/2271#issuecomment-665742471 .
TYPED_TEST_SUITE(AddFloatingOverflowTest,
                 TypesForFloatingOverflowTest, );  // NOLINT

TYPED_TEST(AddFloatingOverflowTest, NotOverflow) {
  constexpr const typename TestFixture::test_target_t kMax =
      TestFixture::Limits::max();
  constexpr const typename TestFixture::test_target_t kZero(0);
  EXPECT_DOUBLE_EQ(static_cast<double>(kMax + kZero),
                   static_cast<double>(saturated::add(kMax, kZero)));
  EXPECT_DOUBLE_EQ(static_cast<double>(kZero + kMax),
                   static_cast<double>(saturated::add(kZero, kMax)));
}

TYPED_TEST(AddFloatingOverflowTest, Overflow) {
  constexpr const typename TestFixture::test_target_t kMax =
      TestFixture::Limits::max();
  constexpr const typename TestFixture::test_target_t kMin =
      TestFixture::Limits::min();
  EXPECT_DOUBLE_EQ(static_cast<double>(kMax),
                   static_cast<double>(saturated::add(kMax, kMin)));
  EXPECT_DOUBLE_EQ(static_cast<double>(kMax),
                   static_cast<double>(saturated::add(kMin, kMax)));
}

template <typename T>
class AddFloatingUnderflowTest
    : public ::testing::Test {
 protected:
  using Limits = std::numeric_limits<T>;
  using test_target_t = T;
};

using TypesForFloatingUnderflowTest = ::testing::Types<float, double>;
// This strange 3rd argument omission is quick hack
// for warning with Google Test Framework.
// See https://github.com/google/googletest/issues/2271#issuecomment-665742471 .
TYPED_TEST_SUITE(AddFloatingUnderflowTest,
                 TypesForFloatingUnderflowTest, );  // NOLINT

TYPED_TEST(AddFloatingUnderflowTest, NotUnderflow) {
  constexpr const typename TestFixture::test_target_t kLowest =
      TestFixture::Limits::lowest();
  constexpr const typename TestFixture::test_target_t kZero(0);
  EXPECT_DOUBLE_EQ(static_cast<double>(kLowest + kZero),
                   static_cast<double>(saturated::add(kLowest, kZero)));
  EXPECT_DOUBLE_EQ(static_cast<double>(kZero + kLowest),
                   static_cast<double>(saturated::add(kZero, kLowest)));
}

TYPED_TEST(AddFloatingUnderflowTest, Underflow) {
  constexpr const typename TestFixture::test_target_t kLowest =
      TestFixture::Limits::lowest();
  constexpr const typename TestFixture::test_target_t kNegativeMax =
      -TestFixture::Limits::min();
  EXPECT_DOUBLE_EQ(static_cast<double>(kLowest),
                   static_cast<double>(saturated::add(kLowest, kNegativeMax)));
  EXPECT_DOUBLE_EQ(static_cast<double>(kLowest),
                   static_cast<double>(saturated::add(kNegativeMax, kLowest)));
}
