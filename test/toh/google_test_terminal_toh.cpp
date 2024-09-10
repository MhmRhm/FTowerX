#include <ranges>

#include "gtest/gtest.h"

#include "ftxui/component/loop.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "toh/terminal_toh.h"

using namespace std;
using namespace ftxui;
using namespace toh;

namespace {
constexpr size_t MaxDisk{10};
constexpr size_t ScreenWidth{81};
constexpr size_t ScreenHeight{20};

const map<size_t, string> ColorMap{{0, "40m"},  {1, "103m"}, {2, "101m"},
                                   {3, "105m"}, {4, "102m"}, {5, "106m"},
                                   {6, "104m"}, {7, "47m"},  {8, "100m"},
                                   {9, "215m"}, {10, "41m"}};

// Break the terminal output into lines
vector<string_view> breakLines(string_view terminal_output) {
  vector<string_view> lines{};
  for (const auto line : ranges::views::split(terminal_output, '\n'))
    lines.push_back(string_view{line.begin(), line.end()});
  return lines;
}

// Assert the disk row is correct
void assertDiskRow(const vector<string_view> &lines, size_t disk, size_t row) {
  /*
   * Total number of lines in the terminal output is defined by `ScreenHeight`.
   * Out of these, 3 lines are reserved for the legend at the bottom. Line
   * numbers increase from the top of the stack to the bottom, while row numbers
   * increase from the bottom to the top. Therefore, a `-` is used in the
   * formula to account for this difference.
   */
  size_t real_row{ScreenHeight - 3 - row};
  for (size_t i{0}; i < lines.size(); i++) {
    size_t position{lines[i].find(ColorMap.at(disk % MaxDisk))};
    if (real_row == i) {
      ASSERT_NE(position, string::npos);
    } else {
      ASSERT_EQ(position, string::npos);
    }
  }
}

// Assert the disk column is correct
void assertDiskColumn(const vector<string_view> &lines, size_t disk, size_t row,
                      Position column) {
  size_t real_row{ScreenHeight - 3 - row};

  // Counting `separator`s from `position` to end of line
  size_t count = 0;
  string separator{"│"};
  size_t position{lines[real_row].find(ColorMap.at(disk % MaxDisk))};

  position = lines[real_row].find(separator, position + 1);
  while (position != string_view::npos) {
    ++count;
    position = lines[real_row].find(separator, position + 1);
  }

  ASSERT_EQ(count, 3 - column);
}

// Assert the disk location is correct
void assertDiskLocation(string_view terminal_output, size_t disk, size_t row,
                        Position column) {
  auto lines{breakLines(terminal_output)};
  assertDiskRow(lines, disk, row);
  assertDiskColumn(lines, disk, row, column);
}
} // namespace

TEST(Terminal_Toh_Tests, Test_Terminal_Toh_Viewer_Game_1) {
  // given
  Game game{1};
  GameViewer viewer{game};
  Screen screen{ScreenWidth, ScreenHeight};

  // when
  auto component{viewer.createView()};

  // then
  Render(screen, component->Render());
  auto terminal_output{screen.ToString()};

  assertDiskLocation(terminal_output, 1, 1, Left);
}

TEST(Terminal_Toh_Tests, Test_Terminal_Toh_Viewer_Game_10) {
  // given
  Game game{10};
  GameViewer viewer{game};
  Screen screen{ScreenWidth, ScreenHeight};

  // when
  auto component{viewer.createView()};

  // then
  Render(screen, component->Render());
  auto terminal_output{screen.ToString()};

  for (size_t i{0}; i < 10; i++) {
    assertDiskLocation(terminal_output, i + 1, 10 - i, Left);
  }
}

TEST(Terminal_Toh_Tests, Test_Terminal_Toh_Viewer_Game_3_Play) {
  using Play = vector<Position>;

  // given
  Game game{3};
  GameViewer viewer{game};

  Play play{Left,  Right,  Left, Middle, Right, Middle, Left,
            Right, Middle, Left, Middle, Right, Left,   Right};
  // clang-format off
  vector<vector<pair<size_t, Position>>> expected_positions
  {
    // disk 1
    {
      {1, Right}, {1, Right}, {2, Middle}, {2, Middle},
      {1, Left}, {1, Left}, {3, Right}
    },
    // disk 2
    {
      {2, Left}, {1, Middle}, {1, Middle}, {1, Middle},
      {1, Middle}, {2, Right}, {2, Right}
    },
    // disk 3
    {
      {1, Left}, {1, Left}, {1, Left}, {1, Right},
      {1, Right}, {1, Right}, {1, Right}
    }
  };
  // clang-format on

  // when
  auto component{viewer.createView()};
  for (size_t choice_idx{0}; choice_idx < play.size(); choice_idx += 2) {
    game.select(play[choice_idx]);
    game.select(play[choice_idx + 1]);

    // then
    Screen screen{ScreenWidth, ScreenHeight};
    Render(screen, component->Render());
    auto terminal_output{screen.ToString()};
    for (auto &&disk_idx : {0, 1, 2}) {
      assertDiskLocation(terminal_output, disk_idx + 1,
                         expected_positions[disk_idx][choice_idx / 2].first,
                         expected_positions[disk_idx][choice_idx / 2].second);
    }
  }
}

TEST(Terminal_Toh_Tests, Test_Terminal_Toh_Controller_Game_3_Play) {
  using Play = vector<char>;
  // Disable the output to prevent FTXUI component rendering during tests.
  std::cout.setstate(std::ios_base::failbit);

  // given
  auto screen{ScreenInteractive::FixedSize(ScreenWidth, ScreenHeight)};
  Game game{3};
  GameViewer viewer{game};
  GameController controller{game, screen};

  auto component{viewer.createView()};
  component |= CatchEvent(controller);
  Loop loop(&screen, component);

  Play play{'a', 'd', 'a', 's', 'd', 's', 'a', 'd',
            's', 'a', 's', 'd', 'a', 'd', 'q'};

  // when
  for (auto &&choice : play) {
    screen.PostEvent(Event::Character(choice));
    loop.RunOnce();
  }

  // then
  Render(screen, component->Render());
  auto terminal_output{screen.ToString()};
  for (size_t i{0}; i < 3; i++) {
    assertDiskLocation(terminal_output, i + 1, 3 - i, Right);
  }

  // Enable the output
  std::cout.clear();
  // Put cursor back
  cout << "\033[A\033[A";
}
