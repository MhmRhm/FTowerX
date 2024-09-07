#include "gtest/gtest.h"

#include "libtoh/toh_model.h"

using namespace std;
using namespace toh;

using Tower = vector<size_t>;
using Play = vector<Position>;

TEST(Toh_Model_Tests, Test_Solve_Toh_1) {
  // given
  Play expected{Left, Right};

  // when
  Play solution{};
  solveToh(solution, 1, Left, Middle, Right);

  // then
  ASSERT_EQ(solution, expected);
}

TEST(Toh_Model_Tests, Test_Solve_Toh_3) {
  // given
  Play expected{Left,  Right,  Left, Middle, Right, Middle, Left,
                Right, Middle, Left, Middle, Right, Left,   Right};

  // when
  Play solution{};
  solveToh(solution, 3, Left, Middle, Right);

  // then
  ASSERT_EQ(solution, expected);
}

TEST(Toh_Model_Tests, Test_Game_Copy_Constructor) {
  // given
  Game game{3};

  // when
  auto copy{game};

  // then
  ASSERT_EQ(copy.getTower(Left), (Tower{3, 2, 1}));
  ASSERT_EQ(copy.getTower(Middle), (Tower{}));
  ASSERT_EQ(copy.getTower(Right), (Tower{}));
  ASSERT_TRUE(copy.isSelected(End));
}

TEST(Toh_Model_Tests, Test_Game_Move_Constructor) {
  // given
  Game game{3};

  // when
  auto copy{std::move(game)};

  // then
  ASSERT_EQ(copy.getTower(Left), (Tower{3, 2, 1}));
  ASSERT_EQ(copy.getTower(Middle), (Tower{}));
  ASSERT_EQ(copy.getTower(Right), (Tower{}));
  ASSERT_TRUE(copy.isSelected(End));
}

TEST(Toh_Model_Tests, Test_Game_Copy_Assignment) {
  // given
  Game lhs{0}, rhs{3};

  // when
  lhs = rhs;

  // then
  ASSERT_EQ(lhs.getTower(Left), (Tower{3, 2, 1}));
  ASSERT_EQ(lhs.getTower(Middle), (Tower{}));
  ASSERT_EQ(lhs.getTower(Right), (Tower{}));
  ASSERT_TRUE(lhs.isSelected(End));
}

TEST(Toh_Model_Tests, Test_Game_Move_Assignment) {
  // given
  Game lhs{0}, rhs{3};

  // when
  lhs = std::move(rhs);

  // then
  ASSERT_EQ(lhs.getTower(Left), (Tower{3, 2, 1}));
  ASSERT_EQ(lhs.getTower(Middle), (Tower{}));
  ASSERT_EQ(lhs.getTower(Right), (Tower{}));
  ASSERT_TRUE(lhs.isSelected(End));
}

TEST(Toh_Model_Tests, Test_Game_Equal_To) {
  // given
  Game lhs{3}, rhs{3};

  // when
  bool is_equal{lhs == rhs};

  // then
  ASSERT_TRUE(is_equal);
}

TEST(Toh_Model_Tests, Test_Game_Not_Equal_To) {
  // given
  Game lhs{3}, rhs{4};

  // when
  bool is_not_equal{lhs != rhs};

  // then
  ASSERT_TRUE(is_not_equal);
}

TEST(Toh_Model_Tests, Test_Game_Select_Empty) {
  // given
  Game game{3};

  // when
  game.select(Middle);

  // then
  ASSERT_EQ(game.getTower(Left), (Tower{3, 2, 1}));
  ASSERT_EQ(game.getTower(Middle), (Tower{}));
  ASSERT_EQ(game.getTower(Right), (Tower{}));
  ASSERT_FALSE(game.isSelected(Middle));
  ASSERT_TRUE(game.isSelected(End));
}

TEST(Toh_Model_Tests, Test_Game_Select_Full) {
  // given
  Game game{3};

  // when
  game.select(Left);

  // then
  ASSERT_EQ(game.getTower(Left), (Tower{3, 2, 1}));
  ASSERT_EQ(game.getTower(Middle), (Tower{}));
  ASSERT_EQ(game.getTower(Right), (Tower{}));
  ASSERT_TRUE(game.isSelected(Left));
}

TEST(Toh_Model_Tests, Test_Game_Select_Empty_Full) {
  // given
  Game game{3};

  // when
  game.select(Right);
  game.select(Left);

  // then
  ASSERT_EQ(game.getTower(Left), (Tower{3, 2, 1}));
  ASSERT_EQ(game.getTower(Middle), (Tower{}));
  ASSERT_EQ(game.getTower(Right), (Tower{}));
  ASSERT_TRUE(game.isSelected(Left));
}

TEST(Toh_Model_Tests, Test_Game_Select_Empty_Full_Empty) {
  // given
  Game game{3};

  // when
  game.select(Right);
  game.select(Left);
  game.select(Right);

  // then
  ASSERT_EQ(game.getTower(Left), (Tower{3, 2}));
  ASSERT_EQ(game.getTower(Middle), (Tower{}));
  ASSERT_EQ(game.getTower(Right), (Tower{1}));
  ASSERT_FALSE(game.isSelected(Right));
  ASSERT_TRUE(game.isSelected(End));
}

TEST(Toh_Model_Tests, Test_Game_Select_Full_Empty_Full) {
  // given
  Game game{3};

  // when
  game.select(Left);
  game.select(Right);
  game.select(Left);

  // then
  ASSERT_EQ(game.getTower(Left), (Tower{3, 2}));
  ASSERT_EQ(game.getTower(Middle), (Tower{}));
  ASSERT_EQ(game.getTower(Right), (Tower{1}));
  ASSERT_TRUE(game.isSelected(Left));
}

TEST(Toh_Model_Tests, Test_Game_Select_Unselect) {
  // given
  Game game{3};

  // when
  game.select(Left);
  game.select(Middle);
  game.select(Left);
  game.select(Left);
  game.select(Middle);
  game.select(Left);

  // then
  ASSERT_EQ(game.getTower(Left), (Tower{3, 2, 1}));
  ASSERT_EQ(game.getTower(Middle), (Tower{}));
  ASSERT_EQ(game.getTower(Right), (Tower{}));
  ASSERT_TRUE(game.isSelected(End));
}

TEST(Toh_Model_Tests, Test_Game_Select_Big_Small) {
  // given
  Game game{3};

  // when
  game.select(Left);
  game.select(Middle);

  game.select(Left);
  game.select(Right);

  game.select(Left);
  game.select(Middle);
  game.select(Right);

  // then
  ASSERT_EQ(game.getTower(Left), (Tower{3}));
  ASSERT_EQ(game.getTower(Middle), (Tower{1}));
  ASSERT_EQ(game.getTower(Right), (Tower{2}));
  ASSERT_FALSE(game.isSelected(Middle));
  ASSERT_FALSE(game.isSelected(Right));
  ASSERT_TRUE(game.isSelected(Left));
}

TEST(Toh_Model_Tests, Test_Game_Play_3) {
  // given
  Game game{3};
  Play plays{};
  solveToh(plays, 3, Left, Middle, Right);
  auto states{plays};
  for (auto it{states.begin()}; it < states.end(); advance(it, 2)) {
    *next(it) = End;
  }
  auto play{plays.begin()};
  auto state{states.begin()};

  for (; play < prev(plays.end()); advance(play, 1), advance(state, 1)) {
    // when
    game.select(*play);

    // then
    ASSERT_TRUE(game.isSelected(*state));
    ASSERT_FALSE(game.isFinished());
  }

  // when
  game.select(Right);

  // then
  ASSERT_EQ(game.getTower(Left), (Tower{}));
  ASSERT_EQ(game.getTower(Middle), (Tower{}));
  ASSERT_EQ(game.getTower(Right), (Tower{3, 2, 1}));
  ASSERT_TRUE(game.isSelected(End));
  ASSERT_TRUE(game.isFinished());
}

TEST(Toh_Model_Tests, Test_Game_Play_10) {
  // given
  Game game{10};
  Play plays{};
  solveToh(plays, 10, Left, Middle, Right);
  auto states{plays};
  for (auto it{states.begin()}; it < states.end(); advance(it, 2)) {
    *next(it) = End;
  }
  auto play{plays.begin()};
  auto state{states.begin()};

  for (; play < prev(plays.end()); advance(play, 1), advance(state, 1)) {
    // when
    game.select(*play);

    // then
    ASSERT_TRUE(game.isSelected(*state));
    ASSERT_FALSE(game.isFinished());
  }

  // when
  game.select(Right);

  // then
  ASSERT_EQ(game.getTower(Left), (Tower{}));
  ASSERT_EQ(game.getTower(Middle), (Tower{}));
  ASSERT_EQ(game.getTower(Right), (Tower{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}));
  ASSERT_TRUE(game.isSelected(End));
  ASSERT_TRUE(game.isFinished());
}
