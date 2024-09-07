#include "benchmark/benchmark.h"
#include "libtoh/toh_model.h"

using namespace std;
using namespace toh;

static void BM_Game_Play_3(benchmark::State &state) {
  bool all_finished{true};
  for (auto _ : state) {
    Game game{3};
    vector<Position> play{Left,  Right,  Left, Middle, Right, Middle, Left,
                          Right, Middle, Left, Middle, Right, Left,   Right};
    for (auto &&choice : play) {
      game.select(choice);
    }
    benchmark::DoNotOptimize(all_finished &= game.isFinished());
  }
}
BENCHMARK(BM_Game_Play_3);
