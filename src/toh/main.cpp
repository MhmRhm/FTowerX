#include "ftxui/component/screen_interactive.hpp"
#include "libtoh/toh_model.h"
#include "toh/terminal_toh.h"

using namespace std;
using namespace ftxui;
using namespace toh;

int main() {
  auto screen{ScreenInteractive::Fullscreen()};

  Game game{3};
  GameViewer viewer{game};
  GameController controller{game, screen};

  auto component{viewer.createView()};
  component |= CatchEvent(controller);

  screen.Loop(component);
}
