#include "benchmark/benchmark.h"
#include "terminal_toh.h"

static void BM_Terminal_TOH(benchmark::State &state) {
  std::cout.setstate(std::ios_base::failbit);
  for (auto _ : state) {
    terminalToh();
  }
  std::cout.clear();
}
BENCHMARK(BM_Terminal_TOH);
