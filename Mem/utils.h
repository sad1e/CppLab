#pragma once

#include <cstddef>

class Utils {
 public:
  static const std::size_t CalculatePadding(const std::size_t base_addr,
                                            const std::size_t alignment) {
    const std::size_t multiplier = (base_addr / alignment) + 1;
    const std::size_t aligned_addr = multiplier * alignment;
    const std::size_t padding = aligned_addr - base_addr;

    return padding;
  }

  static const std::size_t CalculatePaddingWithHeader(
      const std::size_t base_addr, const std::size_t alignment,
      const std::size_t header_size) {
    std::size_t padding = CalculatePadding(base_addr, alignment);
    std::size_t needed_size = header_size;

    if (padding < needed_size) {
      needed_size -= padding;
      if (needed_size % alignment > 0) {
        padding += alignment * (1 + (needed_size / alignment));
      } else {
        padding += alignment * (needed_size / alignment);
      }
    }

    return padding;
  }

  static const bool PowerOf2(std::size_t x) { return (x & (x - 1)) == 0; }
};
