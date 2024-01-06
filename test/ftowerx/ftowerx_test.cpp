#include "ftowerx/ftowerx.h"
#include "gtest/gtest.h"

TEST(StackManagerTests, initiallyEmptyPop) {
  StackManager<std::unique_ptr<Disk>> stackManager{};
  ASSERT_THROW(stackManager.pop(), std::out_of_range);
}

TEST(StackManagerTests, initiallyEmptyPush) {
  StackManager<std::unique_ptr<Disk>> stackManager{};
  auto disk{std::make_unique<Disk>()};
  ASSERT_EQ(stackManager.push(std::move(disk)), true);
}

TEST(StackManagerTests, pushPop) {
  StackManager<std::unique_ptr<Disk>> stackManager{};
  auto disk1{std::make_unique<Disk>()};
  stackManager.push(std::move(disk1));
  decltype(disk1) disk2{stackManager.pop()};
  ASSERT_EQ(disk1.get(), disk2.get());
}
