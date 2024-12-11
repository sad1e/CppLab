#include "benchmark.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <ratio>

#include "io.h"

namespace fcpp {

void Benchmark::SingleAllocation(Allocator* allocator, const std::size_t size,
                                 const std::size_t alignment) {
  // std::cout << "BENCHMARK: SINGLE ALLOCATION" << io::endl;
  // std::cout << "\tSize:       " << size << io::endl;
  // std::cout << "\tAlignment:  " << alignment << io::endl;

  StartRound();

  allocator->Init();

  uint32_t operations = 0u;
  while (operations < OperationCount) {
    allocator->Allocate(size, alignment);
    ++operations;
  }

  FinishRound();

  // BenchmarkResults results = BuildResults(
  //     OperationCount, std::move(TimeElapsed), allocator->GetPeak());
  // PrintBenchmarkResults(results);
}

void Benchmark::SingleFree(Allocator* allocator, const std::size_t size,
                           const std::size_t alignment) {
  // std::cout << "BENCHMARK: SINGLE FREE" << io::endl;
  // std::cout << "\tSize:        " << size << io::endl;
  // std::cout << "\tAlignment:   " << alignment << io::endl;

  void* addresses[OPERATIONS];

  StartRound();

  allocator->Init();

  uint32_t op_idx = 0u;
  while (op_idx < OperationCount) {
    addresses[op_idx] = allocator->Allocate(size, alignment);
    ++op_idx;
  }

  while (op_idx) {
    allocator->Free(addresses[--op_idx]);
  }

  FinishRound();

  // BenchmarkResults results = BuildResults(
  //     OperationCount, std::move(TimeElapsed), allocator->GetPeak());
  // PrintBenchmarkResults(results);
}

void Benchmark::MultipleAllocation(
    Allocator* allocator, const std::vector<std::size_t>& allocation_sizes,
    const std::vector<std::size_t>& alignments) {
  assert(allocation_sizes.size() == alignments.size() &&
         "allocation size and alignments size must be equal.");

  for (size_t i = 0u; i < allocation_sizes.size(); ++i) {
    SingleAllocation(allocator, allocation_sizes[i], alignments[i]);
  }
}

void Benchmark::MultipleFree(Allocator* allocator,
                             const std::vector<std::size_t>& allocation_sizes,
                             const std::vector<std::size_t>& alignments) {
  assert(allocation_sizes.size() == alignments.size() &&
         "allocation size and alignments size must be equal.");

  for (size_t i = 0u; i < allocation_sizes.size(); ++i) {
    SingleFree(allocator, allocation_sizes[i], alignments[i]);
  }
}

void Benchmark::RandomAllocation(
    Allocator* allocator, const std::vector<std::size_t>& allocation_sizes,
    const std::vector<std::size_t>& alignments) {
  // std::cout << "BENCHMARK: RANDOM ALLOCATION" << io::endl;

  std::srand(1);

  StartRound();

  size_t allocation_size;
  size_t alignment;

  allocator->Init();

  uint32_t op_idx = 0u;
  while (op_idx < OperationCount) {
    RandomAllocationAttr(allocation_sizes, alignments, allocation_size,
                         alignment);
    allocator->Allocate(allocation_size, alignment);
    ++op_idx;
  }

  FinishRound();

  // BenchmarkResults results = BuildResults(
  //     OperationCount, std::move(TimeElapsed), allocator->GetPeak());
  // PrintBenchmarkResults(results);
}

void Benchmark::RandomFree(Allocator* allocator,
                           const std::vector<std::size_t>& allocation_sizes,
                           const std::vector<std::size_t>& alignments) {
  // std::cout << "BENCHMARK: RANDOM FREE" << io::endl;

  std::srand(1);

  StartRound();

  void* addresses[OPERATIONS];
  size_t allocation_size;
  size_t alignment;

  uint32_t op_idx = 0u;
  while (op_idx < OperationCount) {
    RandomAllocationAttr(allocation_sizes, alignments, allocation_size,
                         alignment);
    addresses[op_idx] = allocator->Allocate(allocation_size, alignment);
    ++op_idx;
  }

  while (op_idx) {
    allocator->Free(addresses[--op_idx]);
  }

  FinishRound();

  // BenchmarkResults results = BuildResults(
  //     OperationCount, std::move(TimeElapsed), allocator->GetPeak());
  // PrintBenchmarkResults(results);
}

void Benchmark::PrintBenchmarkResults(const BenchmarkResults& results) const {
  std::cout << "\tRESULTS:" << io::endl;
  std::cout << "\t\tOperations:    \t" << results.Operations << io::endl;
  std::cout << "\t\tTime elapsed: \t" << results.Milliseconds.count() << " ms"
            << io::endl;
  std::cout << "\t\tOp per sec:    \t" << results.OperationsPerSecond
            << " ops/ms" << io::endl;
  std::cout << "\t\tTimer per op:  \t" << results.TimePerOperation << " ms/ops"
            << io::endl;
  std::cout << "\t\tMemory peak:   \t" << results.MemoryPeak << " bytes"
            << io::endl;

  std::cout << io::endl;
}

const BenchmarkResults Benchmark::BuildResults(
    std::size_t nOperations, std::chrono::milliseconds&& elapsedTime,
    const std::size_t memoryPeak) const {
  BenchmarkResults results;

  results.Operations = nOperations;
  results.Milliseconds = std::move(elapsedTime);
  results.OperationsPerSecond =
      results.Operations / static_cast<double>(results.Milliseconds.count());
  results.TimePerOperation = static_cast<double>(results.Milliseconds.count()) /
                             static_cast<double>(results.Operations);
  results.MemoryPeak = memoryPeak;

  return results;
}

void Benchmark::RandomAllocationAttr(
    const std::vector<std::size_t>& allocation_Sizes,
    const std::vector<std::size_t>& alignments, std::size_t& size,
    std::size_t& alignment) {
  const int r = rand() % allocation_Sizes.size();
  size = allocation_Sizes[r];
  alignment = alignments[r];
}

}  // namespace fcpp
