#include "callocator.h"

#include <cstdlib>

namespace fcpp {

CAllocator::CAllocator() : Allocator(0) {}

CAllocator::~CAllocator() {}

void* CAllocator::Allocate(const std::size_t size,
                           const std::size_t alignment) {
  return std::malloc(size);
}

void CAllocator::Free(void* p) { std::free(p); }

void CAllocator::Init() {
  // do nothing.
}

}  // namespace fcpp