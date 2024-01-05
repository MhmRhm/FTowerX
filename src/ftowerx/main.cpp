#include <memory>
#include <stdio.h>
#include <iostream>

#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
 
int main(void) {
  using namespace ftxui;

  auto screen = ScreenInteractive::Fullscreen();
  Element document =
    hbox(
        vbox(
            filler(),
            text("▀▀") | color(Color::CyanLight) | center,
            text("▀▀▀▀") | color(Color::YellowLight) | center,
            text("▀▀▀▀▀▀") | color(Color::RedLight) | center
        ) | flex,
        separator(),
        vbox() | flex,
        separator(),
        vbox() | flex
    ) | border;
    screen.Loop(Renderer([&] {
        return document;
    }));

  return EXIT_SUCCESS;
}
