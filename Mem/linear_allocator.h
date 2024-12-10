#pragma once

#include "allocator.h"

namespace fcpp {

class LinearAllocator : public Allocator {
 protected:
  void* start_ptr_{nullptr};
  std::size_t offset_{0u};

 public:
  LinearAllocator(std::size_t total_size);

  virtual ~LinearAllocator();

  virtual void* Allocate(const std::size_t size,
                         const std::size_t alignment = 0) override;

  virtual void Free(void* ptr) override;

  virtual void Init() override;

  virtual void Reset();

 private:
  LinearAllocator(LinearAllocator& linear_allocator);
};

}  // namespace fcpp
