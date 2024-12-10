#include <iostream>

#include "benchmark.h"
#include "callocator.h"
#include "common.h"
#include "io.h"

int main(int argc, char** argv) {
  const size_t alignment = 16;
  const size_t addr = 13;

  int* a = new int(1);

  printf("src:          0x%p\n", a);
  printf("aligned up:   0x%p\n", fcpp::AlignUp(a + 1, alignment));
  printf("aligned down: 0x%p\n", fcpp::AlignDown(a - 1, alignment));

  delete a;

  const std::size_t A = static_cast<std::size_t>(1e9);
  const std::size_t B = static_cast<std::size_t>(1e8);

  const std::vector<std::size_t> ALLOCATION_SIZES{32,   64,   256, 512,
                                                  1024, 2048, 4096};
  const std::vector<std::size_t> ALIGNMENTS{8, 8, 8, 8, 8, 8, 8};

  fcpp::Benchmark bench(OPERATIONS);

  {
    fcpp::Allocator* callocator = new fcpp::CAllocator();
    // bench.MultipleAllocation(callocator, ALLOCATION_SIZES, ALIGNMENTS);
    // bench.MultipleFree(callocator, ALLOCATION_SIZES, ALIGNMENTS);
    // bench.RandomAllocation(callocator, ALLOCATION_SIZES, ALIGNMENTS);
    // bench.RandomFree(callocator, ALLOCATION_SIZES, ALIGNMENTS);
    delete callocator;
  }

  return 0;
}
