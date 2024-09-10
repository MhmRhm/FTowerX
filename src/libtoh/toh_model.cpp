#include "libtoh/toh_model.h"

using namespace std;
using namespace toh;

Game::Game(size_t size) {
  for (size_t i{size}; i > 0; i -= 1)
    m_towers[Left].push_back(i);
}

bool Game::move(Position from, Position to) {
  if (from == End || to == End)
    return false;

  if (!m_towers[to].empty()) {
    if (m_towers[from].back() >= m_towers[to].back())
      return false;
  }

  auto disk{m_towers[from].back()};
  m_towers[from].pop_back();
  m_towers[to].push_back(disk);
  return true;
}

void Game::select(Position position) {
  if (position == End) {
    m_selection = End;
    return;
  }
  if (m_selection == End) {
    if (!m_towers[position].empty()) {
      m_selection = position;
      return;
    }
  }
  if (m_selection == position) {
    m_selection = End;
    return;
  }
  if (move(m_selection, position)) {
    m_selection = End;
    return;
  }
}

bool Game::isFinished() const {
  return m_towers[Left].size() == 0 && m_towers[Middle].size() == 0;
}

const vector<size_t> &Game::getTower(Position position) const {
  return m_towers[position];
}

bool Game::isSelected(Position position) const {
  return position == m_selection;
}
