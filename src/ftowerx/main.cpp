#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

int main(void) {
  using namespace ftxui;

  auto screen = ScreenInteractive::Fullscreen();

  Element document =
      hbox(vbox(filler(), text("▀▀") | color(Color::CyanLight) | center,
                text("▀▀▀▀") | color(Color::YellowLight) | center, filler(),
                text("▀▀▀▀▀▀") | color(Color::RedLight) | center) |
               flex,
           separator(), vbox() | flex, separator(), vbox() | flex) |
      border;

  auto renderer = Renderer([&] { return document; });

  auto component = CatchEvent(renderer, [&](Event event) {
    if (event == Event::Character('q')) {
      screen.ExitLoopClosure()();
      return true;
    }
    return false;
  });

  screen.Loop(component);

  return EXIT_SUCCESS;
}
