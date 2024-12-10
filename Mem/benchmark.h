#pragma once

#include <chrono>
#include <cstddef>
#include <ctime>
#include <vector>

#include "allocator.h"

#define OPERATIONS 10000

namespace fcpp {

struct BenchmarkResults {
  std::size_t Operations;
  std::chrono::milliseconds Milliseconds;
  double OperationsPerSecond;
  double TimePerOperation;
  std::size_t MemoryPeak;
};

class Benchmark {
 public:
  Benchmark() = delete;
  Benchmark(const unsigned int operation_count)
      : OperationCount(operation_count) {}

  void SingleAllocation(Allocator* allocator, const std::size_t size,
                        const std::size_t alignment);
  void SingleFree(Allocator* allocator, const std::size_t size,
                  const std::size_t alignment);

  void MultipleAllocation(Allocator* allocator,
                          const std::vector<std::size_t>& allocation_sizes,
                          const std::vector<std::size_t>& alignments);
  void MultipleFree(Allocator* allocator,
                    const std::vector<std::size_t>& allocation_sizes,
                    const std::vector<std::size_t>& alignments);

  void RandomAllocation(Allocator* allocator,
                        const std::vector<std::size_t>& allocation_sizes,
                        const std::vector<std::size_t>& alignments);

  void RandomFree(Allocator* allocator,
                  const std::vector<std::size_t>& allocation_sizes,
                  const std::vector<std::size_t>& alignments);

 private:
  void PrintBenchmarkResults(const BenchmarkResults& results) const;
  void RandomAllocationAttr(const std::vector<std::size_t>& allocationSizes,
                            const std::vector<std::size_t>& alignments,
                            std::size_t& size, std::size_t& alignment);

  const BenchmarkResults BuildResults(std::size_t operation_count,
                                      std::chrono::milliseconds&& ellapsed_time,
                                      const std::size_t memory_used) const;

  void SetStartTime() noexcept {
    Start = std::chrono::high_resolution_clock::now();
  }
  void SetFinishTime() noexcept {
    Finish = std::chrono::high_resolution_clock::now();
  }
  void SetElapsedTime() noexcept {
    TimeElapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(Finish - Start);
  }
  void StartRound() noexcept { SetStartTime(); }
  void FinishRound() noexcept {
    SetFinishTime();
    SetElapsedTime();
  }

 private:
  std::size_t OperationCount;
  std::chrono::time_point<std::chrono::high_resolution_clock> Start;
  std::chrono::time_point<std::chrono::high_resolution_clock> Finish;
  std::chrono::milliseconds TimeElapsed;
};

}  // namespace fcpp
