#pragma once

#include "allocator.h"

namespace fcpp {

/**
 * use the default malloc/free in c std lib.
 */
class CAllocator : public Allocator {
 public:
  CAllocator();

  virtual ~CAllocator();

  virtual void* alloc(const std::size_t size,
                      const std::size_t alignment = 0) override;

  virtual void dealloc(void* p) override;
};

}  // namespace fcpp