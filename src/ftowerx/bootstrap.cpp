#include "include/ftowerx/ftowerx.h"

#include <chrono>
#include <map>
#include <vector>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

ftxui::Element printTower(const toh::Stack &stack, bool isSrc = false) {
  using namespace ftxui;
  const static std::map<size_t, Color> colorMap{
      {0, Color::Black},        {1, Color::YellowLight}, {2, Color::RedLight},
      {3, Color::MagentaLight}, {4, Color::GreenLight},  {5, Color::CyanLight},
      {6, Color::BlueLight},    {7, Color::GrayLight},   {8, Color::GrayDark},
      {9, Color::SandyBrown},   {10, Color::Red}};

  std::vector<Element> disks{};
  disks.push_back(filler());
  for (int i = stack.size() - 1; i >= 0; i--) {
    disks.push_back(text(std::string(stack[i]->getSize() * 2, ' ')) |
                    bgcolor(colorMap.at(stack[i]->getSize() % 10)) | center);
    if (isSrc && disks.size() == 2) {
      disks.push_back(filler());
    }
  }

  return vbox(disks);
}

void runTOHGame(size_t size) {
  using namespace ftxui;
  using namespace toh;

  GameOfTOH got(size);
  std::chrono::time_point<std::chrono::high_resolution_clock> start{};
  std::chrono::time_point<std::chrono::high_resolution_clock> end{};
  auto timeToText{[&]() {
    using namespace std::chrono;
    auto time{end - start};
    std::stringstream stream;
    stream << "completion time = " << std::fixed << std::setprecision(3)
           << duration_cast<milliseconds>(time).count() / 1000.0 << " seconds";
    return stream.str();
  }};

  auto screen = ScreenInteractive::Fullscreen();

  auto renderer = Renderer([&] {
    return vbox(
        hbox(printTower(got.getTower(GameOfTOH::TOWER_1),
                        got.isSourceTower(GameOfTOH::TOWER_1)) |
                 flex | ftxui::size(WIDTH, EQUAL, Terminal::Size().dimx),
             separator(),
             printTower(got.getTower(GameOfTOH::TOWER_2),
                        got.isSourceTower(GameOfTOH::TOWER_2)) |
                 flex | ftxui::size(WIDTH, EQUAL, Terminal::Size().dimx),
             separator(),
             printTower(got.getTower(GameOfTOH::TOWER_3),
                        got.isSourceTower(GameOfTOH::TOWER_3)) |
                 flex | ftxui::size(WIDTH, EQUAL, Terminal::Size().dimx)) |
            border | flex,
        end != std::chrono::time_point<std::chrono::high_resolution_clock>{}
            ? text(timeToText()) | center
            : text(""));
  });

  auto component = CatchEvent(renderer, [&](Event event) {
    if (start ==
        std::chrono::time_point<std::chrono::high_resolution_clock>{}) {
      start = std::chrono::high_resolution_clock::now();
    }

    if (event == Event::Character('q')) {
      screen.ExitLoopClosure()();
      return true;
    }
    if (event == Event::ArrowLeft) {
      got.selectOrMoveToTower(GameOfTOH::TOWER_1);
    }
    if (event == Event::ArrowDown) {
      got.selectOrMoveToTower(GameOfTOH::TOWER_2);
    }
    if (event == Event::ArrowRight) {
      got.selectOrMoveToTower(GameOfTOH::TOWER_3);
    }
    if (event == Event::Escape) {
      got.selectOrMoveToTower(GameOfTOH::TOWER_END);
    }

    if (end == std::chrono::time_point<std::chrono::high_resolution_clock>{} &&
        got.getTower(GameOfTOH::TOWER_3).size() == size) {
      end = std::chrono::high_resolution_clock::now();
    }

    return false;
  });

  screen.Loop(component);
}
