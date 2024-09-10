#include <chrono>

#include "ftxui/component/loop.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "toh/terminal_toh.h"

using namespace std;
using namespace chrono;
using namespace ftxui;
using namespace toh;

int main() {
  using Play = vector<char>;
  constexpr size_t GameSize{10};
  Play play{};
  solveToh(play, GameSize, 'a', 's', 'd');
  play.push_back('q');

  // Disable the output to prevent FTXUI component rendering during tests.
  cout.setstate(ios_base::failbit);
  high_resolution_clock::time_point start{high_resolution_clock::now()};
  {
    auto screen{ScreenInteractive::Fullscreen()};
    Game game{GameSize};
    GameViewer viewer{game};
    GameController controller{game, screen};

    auto component{viewer.createView()};
    component |= CatchEvent(controller);
    Loop loop(&screen, component);

    for (auto &&choice : play) {
      screen.PostEvent(Event::Character(choice));
      loop.RunOnce();
    }
  }
  high_resolution_clock::time_point end{high_resolution_clock::now()};
  // Enable the output
  cout.clear();

  cout << format("Total time to solve ToH for {} disks = {} (s)", GameSize,
                 duration_cast<milliseconds>(end - start).count() / 1000.0)
       << endl;
}
