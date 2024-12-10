#include "linear_allocator.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>

#include "common.h"
#include "io.h"
#include "utils.h"

namespace fcpp {

LinearAllocator::LinearAllocator(std::size_t total_size)
    : Allocator(total_size) {}

LinearAllocator::~LinearAllocator() {
  free(start_ptr_);
  start_ptr_ = nullptr;
}

void LinearAllocator::Init() {
  if (start_ptr_ != nullptr) {
    free(start_ptr_);
  }

  start_ptr_ = malloc(total_size_);
  offset_ = 0u;
}

void* LinearAllocator::Allocate(const std::size_t size,
                                const std::size_t alignment) {
  size_t next_addr = 0u;
  size_t padding = 0u;

  const size_t current_addr = (size_t)start_ptr_ + offset_;
  if (alignment != 0 && (offset_ % alignment != 0)) {
    size_t next_aligned_addr = AlignUp(current_addr, alignment);
    padding = next_aligned_addr - current_addr;
  }

  if (next_addr + size > total_size_) {
    std::cerr << "out of memory range." << io::endl;
    return nullptr;
  }

  return (void*)next_addr;
}

void LinearAllocator::Free(void* ptr) {}

void LinearAllocator::Reset() {}

}  // namespace fcpp
