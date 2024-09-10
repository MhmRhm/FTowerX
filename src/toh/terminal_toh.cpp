#include "toh/terminal_toh.h"

using namespace std;
using namespace ftxui;
using namespace toh;

GameViewer::GameViewer(const toh::Game &game) : m_game{game} {}

Component GameViewer::createView() const & {
  return Renderer([&] { return vbox(); });
}

Element GameViewer::createLegend() const { return hbox(); }

Element GameViewer::createTowers() const { return hbox(); }

Element GameViewer::createTower(const vector<size_t> &tower,
                                bool is_selected) const {
  return vbox();
}

void GameViewer::resetCompletionTimeIfNeeded() const {}

void GameViewer::updateCompletionTime() const {}

string GameViewer::formatCompletionDuration() const { return ""; }

GameController::GameController(toh::Game &game,
                               ftxui::ScreenInteractive &screen)
    : m_game{game}, m_screen{screen} {}

bool GameController::operator()(ftxui::Event event) & { return false; }

bool GameController::handleMovement(ftxui::Event event) { return false; }

bool GameController::handleGameModification(ftxui::Event event) {
  return false;
}

void GameController::modifyGameSize(int delta) {}
