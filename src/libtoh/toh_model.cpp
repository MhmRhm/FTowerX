#include "include/libtoh/toh_model.h"

using namespace std;
using namespace toh;

Game::Game([[maybe_unused]] size_t size) {}

void Game::select([[maybe_unused]] Position position) {}

bool Game::isFinished() const { return false; }

const vector<size_t> &Game::getTower(Position position) const {
  return m_towers[position];
}

bool Game::isSelected([[maybe_unused]] Position position) const {
  return false;
}
