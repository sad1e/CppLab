#pragma once

#include "allocator.h"

namespace fcpp {

template <typename T, typename TCAllocator>
class TCustomAllocatorSTLAdapter {
 public:
  using value_type = T;

  TCustomAllocatorSTLAdapter() = delete;
  TCustomAllocatorSTLAdapter(TCAllocator& allocator) noexcept
      : allocator_(allocator) {}

  template <typename U>
  TCustomAllocatorSTLAdapter(
      const TCustomAllocatorSTLAdapter<U, TCAllocator>& other) noexcept
      : allocator_(other.allocator_) {}

  [[nodiscard]] constexpr T* allocate(std::size_t size) {
    return reinterpret_cast<T*>(allocator_.alloc(size * sizeof(T), alignof(T)));
  }

  constexpr void deallocate(T* p, [[maybe_unused]] std::size_t size) {
    allocator_.dealloc(p);
  }

  std::size_t MaxAllocationSize() const noexcept {
    return allocator_.GetSize();
  }

  bool operator==(const TCustomAllocatorSTLAdapter<T, TCAllocator>& rhs) const noexcept {
    if constexpr (std::is_base_of_v<Allocator, TCAllocator>) {
      return allocator_.GetStart() == rhs.allocator_.GetStart();
    } else {
      
    }
  }

  TCAllocator& allocator_;
};

}  // namespace fcpp
