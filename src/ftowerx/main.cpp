#include <memory>
#include <stdio.h>

#include <ftxui/dom/elements.hpp>  // for filler, text, hbox, vbox
#include <ftxui/dom/node.hpp>      // for Render
#include <ftxui/screen/color.hpp>  // for ftxui
#include <ftxui/screen/screen.hpp> // for Full, Screen

int main() {
  using namespace ftxui;
  auto document = hbox({
                      vbox(
                        center(text("1")) | flex,
                        separator(),
                        center(text("2"))
                      ) | flex,
                      separator(),
                      vbox(
                        center(text("1")) | flex,
                        separator(),
                        center(text("2"))
                      ) | flex,
                      separator(),
                      vbox(
                        center(text("1")) | flex,
                        separator(),
                        center(text("2"))
                      ) | flex,
                  }) |
                  border;
  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
  Render(screen, document);
  screen.Print();
 
  return 0;
}
