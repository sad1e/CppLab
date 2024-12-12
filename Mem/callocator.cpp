#include "callocator.h"

#include <cstdlib>

namespace fcpp {

CAllocator::CAllocator() : Allocator(0) {}

CAllocator::~CAllocator() {}

void* CAllocator::alloc(const std::size_t size, const std::size_t alignment) {
  return std::malloc(size);
}

void CAllocator::dealloc(void* p) { std::free(p); }

}  // namespace fcpp