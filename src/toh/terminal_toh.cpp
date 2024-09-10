#include "toh/terminal_toh.h"

using namespace std;
using namespace chrono;
using namespace ftxui;
using namespace toh;

namespace {
constexpr size_t MaxDisk{10};
const map<size_t, Color> ColorMap{
    {0, Color::Black},        {1, Color::YellowLight}, {2, Color::RedLight},
    {3, Color::MagentaLight}, {4, Color::GreenLight},  {5, Color::CyanLight},
    {6, Color::BlueLight},    {7, Color::GrayLight},   {8, Color::GrayDark},
    {9, Color::SandyBrown},   {10, Color::Red}};
} // namespace

GameViewer::GameViewer(const toh::Game &game) : m_game{game} {}

Component GameViewer::createView() const & {
  return Renderer([&] {
    return vbox(createTowers() | flex, separator(), createLegend()) | border;
  });
}

Element GameViewer::createLegend() const {
  updateCompletionTime();

  const string help_text{
      "(q)->quit, (+/-)->add/remove disks, (a/j)->select left, "
      "(s/k)->select middle, (d/l)->select right"};

  string duration{};
  if (m_completionDuration.count() > 0) {
    duration = formatCompletionDuration();
  }

  return hbox(text(help_text), filler(), text(duration));
}

Element GameViewer::createTowers() const {
  resetCompletionTimeIfNeeded();

  vector<Element> towers{};
  for (auto &&position : {Left, Middle, Right}) {
    towers.push_back(
        createTower(m_game.getTower(position), m_game.isSelected(position)) |
        flex | size(WIDTH, EQUAL, Terminal::Size().dimx));
  }

  return hbox(towers[Left], separator(), towers[Middle], separator(),
              towers[Right]);
}

Element GameViewer::createTower(const vector<size_t> &tower,
                                bool is_selected) const {
  vector<Element> disks{filler()};
  for (auto it{crbegin(tower)}; it != crend(tower); advance(it, 1)) {
    disks.push_back(text(std::string(*it * 2, ' ')) |
                    bgcolor(ColorMap.at(*it % MaxDisk)) | center);
    if (is_selected && disks.size() == 2) {
      disks.push_back(filler());
    }
  }
  return vbox(disks);
}

void GameViewer::resetCompletionTimeIfNeeded() const {
  if (m_completionDuration.count() && !m_game.isFinished()) {
    m_completionDuration = steady_clock::duration{};
    m_startTime = steady_clock::time_point{};
  }

  if (m_startTime == steady_clock::time_point{} && m_game.isSelected(Left)) {
    m_startTime = steady_clock::now();
  }
}

void GameViewer::updateCompletionTime() const {
  if (m_completionDuration.count() == 0 && m_game.isFinished()) {
    m_completionDuration = steady_clock::now() - m_startTime;
  }
}

string GameViewer::formatCompletionDuration() const {
  return format("Completed in {:.3f} (s)",
                duration_cast<milliseconds>(m_completionDuration).count() /
                    1000.0);
}

// GameController Implementation

GameController::GameController(toh::Game &game,
                               ftxui::ScreenInteractive &screen)
    : m_game{game}, m_screen{screen} {}

bool GameController::operator()(ftxui::Event event) & {
  if (handleMovement(event))
    return true;
  if (handleGameModification(event))
    return true;
  if (event == Event::Character('q')) {
    m_screen.Exit();
    return true;
  }
  return false;
}

bool GameController::handleMovement(ftxui::Event event) {
  if (event == Event::Character('a') || event == Event::Character('j')) {
    m_game.select(Left);
    return true;
  }
  if (event == Event::Character('s') || event == Event::Character('k')) {
    m_game.select(Middle);
    return true;
  }
  if (event == Event::Character('d') || event == Event::Character('l')) {
    m_game.select(Right);
    return true;
  }
  return false;
}

bool GameController::handleGameModification(ftxui::Event event) {
  if (event == Event::Character('+')) {
    modifyGameSize(1);
    return true;
  }
  if (event == Event::Character('-')) {
    modifyGameSize(-1);
    return true;
  }
  return false;
}

void GameController::modifyGameSize(int delta) {
  size_t size{};
  for (auto &&position : {Left, Middle, Right}) {
    size += m_game.getTower(position).size();
  }

  size = (delta > 0) ? min(size + 1, MaxDisk) : max(size - 1, size_t{1});
  m_game = Game{size};
}
