#include "linear_allocator.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>

#include "mem_common.h"
#include "io.h"
#include "utils.h"

namespace fcpp {

LinearAllocator::LinearAllocator(std::size_t total_size)
    : Allocator(total_size), offset_(0) {
  start_ptr_ = static_cast<char*>(::operator new(total_size));
}

LinearAllocator::~LinearAllocator() {
  ::operator delete(start_ptr_);
  start_ptr_ = nullptr;
}

void* LinearAllocator::alloc(const std::size_t size,
                             const std::size_t alignment) {
  size_t next_addr = 0u;
  size_t padding = 0u;

  const size_t current_addr = (size_t)start_ptr_ + offset_;
  if (alignment != 0 && (offset_ % alignment != 0)) {
    size_t next_aligned_addr = AlignUp(current_addr, alignment);
    padding = next_aligned_addr - current_addr;
  }

  if (next_addr + size > total_size_) {
    std::cerr << "LinearAllocator: alloc failed, not enough memory.\n";
    return nullptr;
  }

  return (void*)next_addr;
}

void LinearAllocator::dealloc(void* ptr) {}

}  // namespace fcpp
