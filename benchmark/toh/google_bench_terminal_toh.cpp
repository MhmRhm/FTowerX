#include "benchmark/benchmark.h"
#include "terminal_toh.h"

static void BM_getMessage(benchmark::State &state) {
  std::cout.setstate(std::ios_base::failbit);
  for (auto _ : state) {
    run_terminal_toh();
  }
  std::cout.clear();
}
BENCHMARK(BM_getMessage);
