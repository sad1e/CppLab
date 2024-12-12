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
    : Allocator(total_size), prev_offset_(0u), offset_(0u) {
  // get the start address of current allocator.
  start_ptr_ = static_cast<char*>(::operator new(total_size));

  std::cout << "[LinearAllocator]: ctor, alloc space once." << io::endl;
}

LinearAllocator::~LinearAllocator() {
  // free all spaces and set `start_ptr_` to null.
  ::operator delete(start_ptr_);
  start_ptr_ = nullptr;

  std::cout << "[LinearAllocator]: dtor, dealloc space." << io::endl;
}

void* LinearAllocator::alloc(const std::size_t size,
                             const std::size_t alignment) {
  std::size_t start_addr = (std::size_t)start_ptr_;
  std::size_t curr_ptr = start_addr + offset_;
  std::size_t new_offset = AlignUp(curr_ptr, alignment) - start_addr;

  if (new_offset + size <= total_size_) {
    void* p = (void*)((std::size_t)start_ptr_ + new_offset);
    prev_offset_ = offset_;
    offset_ = new_offset;

    memset(p, 0, size);

    return p;
  } else {
    std::cerr << "LinearAllocator: alloc failed, not enough memory.\n";
  }

  return nullptr;
}

void LinearAllocator::dealloc(void* ptr) {
  // do nothing.
}

}  // namespace fcpp
