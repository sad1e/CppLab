#pragma once

#include "allocator.h"

namespace fcpp {

/**
 * The linear allocator is simple enough, the user is not allowed to free
 * certain blocks of memory. The memory is usually free all at once.
 *
 * @note: the linear allocator is obey the RAII rules, but does it really need
 * RAII?
 */
class LinearAllocator : public Allocator {
 protected:
  std::size_t prev_offset_;
  std::size_t offset_;

 public:
  LinearAllocator() = delete;
  explicit LinearAllocator(std::size_t total_size);

  DISABLE_CPP_COPY_AND_MOVE(LinearAllocator);

  virtual ~LinearAllocator();

  virtual void* alloc(const std::size_t size,
                      const std::size_t alignment = 0) override;

  virtual void dealloc(void* ptr) override;

 private:
  LinearAllocator(LinearAllocator& linear_allocator);
};

}  // namespace fcpp
