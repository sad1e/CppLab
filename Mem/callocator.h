#pragma once

#include "allocator.h"

namespace fcpp {

/**
 * use the default malloc/free in c std lib.
 */
class CAllocator : public fcpp::Allocator {
 public:
  CAllocator();
  virtual ~CAllocator();

  virtual void* Allocate(const std::size_t size,
                         const std::size_t alignment = 0) override;

  virtual void Free(void* p) override;

  virtual void Init() override;
};

}  // namespace fcpp