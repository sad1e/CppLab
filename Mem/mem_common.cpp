#include "mem_common.h"

namespace fcpp {

uintptr_t AlignForward(uintptr_t ptr, size_t alignment) {
  uintptr_t p, a, module;
  assert(IsPowerOfTwo(alignment));

  p = ptr;
  a = (uintptr_t)alignment;
  module = p & (a - 1);
  if (module != 0) {
    p += a - module;
  }
  return p;
}
}  // namespace fcpp