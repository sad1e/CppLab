#pragma once

#include <memory>
#include "linear_allocator.h"

namespace fcpp {

template <typename T>
class SimpleAllocatorSTL {
 public:
  using value_type = T;

  LinearAllocator* linear_allocator;

  explicit SimpleAllocatorSTL(LinearAllocator& allocator)
      : linear_allocator(&allocator) {}

  T* allocate(std::size_t size) {
    void* p = linear_allocator->alloc(size * sizeof(T));
    if (!p) {
      throw std::bad_alloc();
    }
    return static_cast<T*>(p);
  }

  void deallocate(T* p, std::size_t n) noexcept {}

  bool operator==(const SimpleAllocatorSTL& other) const noexcept {
    return linear_allocator == other.linear_allocator;
  }

  bool operator!=(const SimpleAllocatorSTL& other) const noexcept {
    return !(*this == other);
  }
};
}  // namespace fcpp