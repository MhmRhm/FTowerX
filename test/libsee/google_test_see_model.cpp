#include "libsee/see_model.h"
#include "gtest/gtest.h"

TEST(See_Model_Tests, Test_getMessage) {
  // given
  std::string msg{};

  // when
  msg = getMessage();

  // then
  ASSERT_EQ(msg, "main");
}
