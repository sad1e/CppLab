#include <benchmark/benchmark.h>

#include <iostream>

#include "benchmark.h"
#include "callocator.h"
#include "io.h"
#include "mem_common.h"

static void BM_MultipleAllocation(benchmark::State& state) {
  fcpp::Allocator* callocator = new fcpp::CAllocator();
  callocator->Init();

  for (auto _ : state) {
    const size_t size = static_cast<size_t>(state.range(0));
    const size_t alignment = static_cast<size_t>(state.range(1));

    void* p = callocator->Allocate(size, alignment);
    callocator->Free(p);
  }

  delete callocator;
}

// clang-format off
BENCHMARK(BM_MultipleAllocation)
  ->Args({32,   8})
  ->Args({64,   8})
  ->Args({256,  8})
  ->Args({512,  8})
  ->Args({1024, 8})
  ->Args({2048, 8})
  ->Args({4096, 8})
  ;
// clang-format on

BENCHMARK_MAIN();
