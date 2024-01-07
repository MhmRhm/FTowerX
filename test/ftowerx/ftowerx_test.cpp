#include "ftowerx/ftowerx.h"
#include "gtest/gtest.h"

namespace toh {

TEST(StackManagerTests, initiallyEmptyPop) {
  Stack stack{};
  ASSERT_THROW(stack.pop(), std::out_of_range);
}

TEST(StackManagerTests, initiallyEmptyPush) {
  Stack stack{};
  auto disk{std::make_unique<Disk>(0)};
  ASSERT_TRUE(stack.push(std::move(disk)));
}

TEST(StackManagerTests, pushPop) {
  Stack stack{};
  auto disk1{std::make_unique<Disk>(0)};
  Disk *disk1Ptr = disk1.get();

  ASSERT_TRUE(stack.push(std::move(disk1)));
  std::unique_ptr<Disk> disk2{stack.pop()};

  ASSERT_EQ(disk1Ptr, disk2.get());
}

TEST(StackManagerTests, ltPush) {
  Stack stack{};
  auto disk1{std::make_unique<Disk>(1)};
  auto disk2{std::make_unique<Disk>(0)};

  ASSERT_TRUE(stack.push(std::move(disk1)));
  ASSERT_TRUE(stack.push(std::move(disk2)));
}

TEST(StackManagerTests, gtPush) {
  Stack stack{};
  auto disk1{std::make_unique<Disk>(0)};
  auto disk2{std::make_unique<Disk>(1)};

  ASSERT_TRUE(stack.push(std::move(disk1)));
  ASSERT_FALSE(stack.push(std::move(disk2)));
}

TEST(StackManagerTests, eqPush) {
  Stack stack{};
  auto disk1{std::make_unique<Disk>(0)};
  auto disk2{std::make_unique<Disk>(0)};

  ASSERT_TRUE(stack.push(std::move(disk1)));
  ASSERT_FALSE(stack.push(std::move(disk2)));
}

TEST(StackManagerTests, negativePushFirst) {
  Stack stack{};
  auto disk1{std::make_unique<Disk>(-1)};
  auto disk2{std::make_unique<Disk>(1000)};

  ASSERT_TRUE(stack.push(std::move(disk1)));
  ASSERT_TRUE(stack.push(std::move(disk2)));
}

TEST(StackManagerTests, negativePushLast) {
  Stack stack{};
  auto disk1{std::make_unique<Disk>(0)};
  auto disk2{std::make_unique<Disk>(-1)};

  ASSERT_TRUE(stack.push(std::move(disk1)));
  ASSERT_FALSE(stack.push(std::move(disk2)));
}

} // namespace toh
