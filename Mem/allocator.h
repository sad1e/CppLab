#pragma once

#include <cstddef>

namespace fcpp {
class Allocator {
 protected:
  std::size_t total_size_;
  std::size_t used_;
  std::size_t peak_;

 public:
  Allocator(std::size_t total_size)
      : total_size_(total_size), used_(0), peak_(0) {}

  virtual ~Allocator() { total_size_ = 0; }

  virtual void* alloc(const std::size_t size, const std::size_t alignment) = 0;
  virtual void dealloc(void* p) = 0;

  std::size_t GetTotalSize() const { return total_size_; }
  std::size_t GetUsed() const { return used_; }
  std::size_t GetPeak() const { return peak_; }

  friend class Benchmark;
};

}  // namespace fcpp
