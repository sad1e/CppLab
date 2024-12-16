#pragma once

#include "../Common/core.h"
#include <cstddef>

namespace fcpp {
class Allocator {
 protected:
  std::size_t total_size_;
  std::size_t used_;
  std::size_t peak_;
  void* start_ptr_;

 public:
  explicit Allocator(std::size_t total_size)
      : total_size_(total_size), used_(0), peak_(0), start_ptr_(nullptr) {}

  virtual ~Allocator() { total_size_ = 0; }

  virtual void* alloc(const std::size_t size, const std::size_t alignment) = 0;
  virtual void dealloc(void* p) = 0;

  std::size_t GetSize() const { return total_size_; }
  std::size_t GetUsed() const { return used_; }
  std::size_t GetPeak() const { return peak_; }
  void* GetStart() const { return start_ptr_; }

  friend class Benchmark;
};

}  // namespace fcpp
