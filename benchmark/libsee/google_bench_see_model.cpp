#include "benchmark/benchmark.h"
#include "libsee/see_model.h"

static void BM_getMessage(benchmark::State &state) {
  for (auto _ : state) {
    getMessage();
  }
}
BENCHMARK(BM_getMessage);
