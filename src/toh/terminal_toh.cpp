#include "terminal_toh.h"
#include "libtoh/toh_model.h"

using namespace std;
using namespace toh;

bool terminalToh() {
  Game game{3};
  vector<Position> play{Left,  Right,  Left, Middle, Right, Middle, Left,
                        Right, Middle, Left, Middle, Right, Left,   Right};
  for (auto &&choice : play) {
    game.select(choice);
  }
  return game.isFinished();
}
