#include "ftowerx/ftowerx.h"
#include "gtest/gtest.h"

namespace toh {

TEST(UniformStackTests, initiallyEmptyPop) {
  Stack stack{};
  ASSERT_EQ(stack.size(), 0);
  ASSERT_TRUE(stack.empty());
  ASSERT_THROW(stack.pop(), std::out_of_range);
}

TEST(UniformStackTests, initiallyEmptyPush) {
  Stack stack{};
  auto disk{std::make_unique<Disk>(0)};
  ASSERT_FALSE(stack.push(std::move(disk)));
  ASSERT_EQ(stack.size(), 1);
  ASSERT_FALSE(stack.empty());
}

TEST(UniformStackTests, pushPop) {
  Stack stack{};
  auto disk1{std::make_unique<Disk>(0)};
  Disk *disk1Ptr = disk1.get();

  stack.push(std::move(disk1));
  std::unique_ptr<Disk> disk2{stack.pop()};

  ASSERT_EQ(disk1Ptr, disk2.get());
  ASSERT_TRUE(stack.empty());
}

TEST(UniformStackTests, ltPush) {
  Stack stack{};
  auto disk1{std::make_unique<Disk>(1)};
  auto disk2{std::make_unique<Disk>(0)};
  stack.push(std::move(disk1));

  ASSERT_FALSE(stack.push(std::move(disk2)));
}

TEST(UniformStackTests, gtPush) {
  Stack stack{};
  auto disk1{std::make_unique<Disk>(0)};
  auto disk2{std::make_unique<Disk>(1)};
  stack.push(std::move(disk1));

  std::optional<std::unique_ptr<Disk>> rejectedDisk{};
  ASSERT_TRUE(rejectedDisk = stack.push(std::move(disk2)));
  ASSERT_EQ(rejectedDisk.value()->getSize(), 1);
}

TEST(UniformStackTests, eqPush) {
  Stack stack{};
  auto disk1{std::make_unique<Disk>(0)};
  auto disk2{std::make_unique<Disk>(0)};
  stack.push(std::move(disk1));

  std::optional<std::unique_ptr<Disk>> rejectedDisk{};
  ASSERT_TRUE(rejectedDisk = stack.push(std::move(disk2)));
  ASSERT_EQ(rejectedDisk.value()->getSize(), 0);
}

TEST(UniformStackTests, negativePushFirst) {
  Stack stack{};
  auto disk1{std::make_unique<Disk>(-1)};
  auto disk2{std::make_unique<Disk>(1000)};

  ASSERT_FALSE(stack.push(std::move(disk1)));
  ASSERT_FALSE(stack.push(std::move(disk2)));
}

TEST(UniformStackTests, negativePushLast) {
  Stack stack{};
  auto disk1{std::make_unique<Disk>(0)};
  auto disk2{std::make_unique<Disk>(-1)};
  stack.push(std::move(disk1));

  std::optional<std::unique_ptr<Disk>> rejectedDisk{};
  ASSERT_TRUE(rejectedDisk = stack.push(std::move(disk2)));
  ASSERT_EQ(rejectedDisk.value()->getSize(), -1);
}

TEST(GameOfTOHTests, construction) {
  size_t hight{3};
  GameOfTOH got{hight};

  for (size_t i = 0; i < hight; i++) {
    auto disk{const_cast<Stack &>(got.getTower(0)).pop()};
    ASSERT_EQ(disk->getSize(), i + 1);
  }
  ASSERT_THROW(const_cast<Stack &>(got.getTower(0)).pop(), std::out_of_range);
  ASSERT_THROW(const_cast<Stack &>(got.getTower(1)).pop(), std::out_of_range);
  ASSERT_THROW(const_cast<Stack &>(got.getTower(2)).pop(), std::out_of_range);
}

TEST(GameOfTOHTests, compliantMove) {
  GameOfTOH got{3};

  got.selectOrMoveToTower(0);
  got.selectOrMoveToTower(1);
  got.selectOrMoveToTower(0);
  got.selectOrMoveToTower(2);

  auto disk1{const_cast<Stack &>(got.getTower(1)).pop()};
  auto disk2{const_cast<Stack &>(got.getTower(2)).pop()};
  auto disk3{const_cast<Stack &>(got.getTower(0)).pop()};
  ASSERT_EQ(disk1->getSize(), 1);
  ASSERT_EQ(disk2->getSize(), 2);
  ASSERT_EQ(disk3->getSize(), 3);
  ASSERT_THROW(const_cast<Stack &>(got.getTower(0)).pop(), std::out_of_range);
  ASSERT_THROW(const_cast<Stack &>(got.getTower(1)).pop(), std::out_of_range);
  ASSERT_THROW(const_cast<Stack &>(got.getTower(2)).pop(), std::out_of_range);
}

TEST(GameOfTOHTests, noncompliantMove) {
  GameOfTOH got{3};

  got.selectOrMoveToTower(0);
  got.selectOrMoveToTower(2);
  got.selectOrMoveToTower(0);
  got.selectOrMoveToTower(2);

  auto disk1{const_cast<Stack &>(got.getTower(2)).pop()};
  auto disk2{const_cast<Stack &>(got.getTower(0)).pop()};
  auto disk3{const_cast<Stack &>(got.getTower(0)).pop()};
  ASSERT_EQ(disk1->getSize(), 1);
  ASSERT_EQ(disk2->getSize(), 2);
  ASSERT_EQ(disk3->getSize(), 3);
  ASSERT_THROW(const_cast<Stack &>(got.getTower(0)).pop(), std::out_of_range);
  ASSERT_THROW(const_cast<Stack &>(got.getTower(1)).pop(), std::out_of_range);
  ASSERT_THROW(const_cast<Stack &>(got.getTower(2)).pop(), std::out_of_range);
}

TEST(GameOfTOHTests, irrationalMove) {
  GameOfTOH got{3};

  got.selectOrMoveToTower(2);
  got.selectOrMoveToTower(1);
  got.selectOrMoveToTower(1);
  got.selectOrMoveToTower(0);

  auto disk1{const_cast<Stack &>(got.getTower(0)).pop()};
  auto disk2{const_cast<Stack &>(got.getTower(0)).pop()};
  auto disk3{const_cast<Stack &>(got.getTower(0)).pop()};
  ASSERT_EQ(disk1->getSize(), 1);
  ASSERT_EQ(disk2->getSize(), 2);
  ASSERT_EQ(disk3->getSize(), 3);
  ASSERT_THROW(const_cast<Stack &>(got.getTower(0)).pop(), std::out_of_range);
  ASSERT_THROW(const_cast<Stack &>(got.getTower(1)).pop(), std::out_of_range);
  ASSERT_THROW(const_cast<Stack &>(got.getTower(2)).pop(), std::out_of_range);
}

TEST(GameOfTOHTests, selfMove) {
  GameOfTOH got{3};

  got.selectOrMoveToTower(0);
  got.selectOrMoveToTower(0);

  auto disk1{const_cast<Stack &>(got.getTower(0)).pop()};
  auto disk2{const_cast<Stack &>(got.getTower(0)).pop()};
  auto disk3{const_cast<Stack &>(got.getTower(0)).pop()};
  ASSERT_EQ(disk1->getSize(), 1);
  ASSERT_EQ(disk2->getSize(), 2);
  ASSERT_EQ(disk3->getSize(), 3);
  ASSERT_THROW(const_cast<Stack &>(got.getTower(0)).pop(), std::out_of_range);
  ASSERT_THROW(const_cast<Stack &>(got.getTower(1)).pop(), std::out_of_range);
  ASSERT_THROW(const_cast<Stack &>(got.getTower(2)).pop(), std::out_of_range);
}

} // namespace toh
