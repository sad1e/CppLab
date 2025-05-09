#include <bitset>
#include <iostream>
#include <memory>
#include <tuple>


uint32_t bitfieldExtract(uint32_t data, uint32_t offset, uint32_t numBits) {
  uint32_t mask = (1u << numBits) - 1u;
  return (data >> offset) & mask;
}

int bitfieldExtractSigned(int data, uint32_t offset, uint32_t numBits) {
  int shifted = data >> offset;
  int signBit = shifted & (1u << (numBits - 1u));
  uint32_t mask = (1u << numBits) - 1u;

  return -signBit | (shifted & mask);
}

uint32_t bitfieldInsert(uint32_t mask, uint32_t src, uint32_t dst) {
  return (src & mask) | (dst & ~mask);
}

uint32_t bitfieldInsert(uint32_t src, uint32_t data, uint32_t offset,
                        uint32_t numBits) {
  uint32_t mask = (1u << numBits) - 1u;
  src &= ~(mask << offset);
  return (src | ((data & mask) << offset));
  // return (src & mask) | (dst & ~mask);
}

std::tuple<uint32_t, uint32_t> RemapForQuad(uint32_t a) {
  return std::make_tuple(bitfieldExtract(a, 1u, 3u),
                         bitfieldInsert(bitfieldExtract(a, 3u, 3u), a, 0, 1));
}

int main(void) {
  for (int x = 0; x < 16; ++x) {
    for (int y = 0; y < 16; ++y) {
      uint32_t i = x * 16 + y;
      std::tuple<uint32_t, uint32_t> t = RemapForQuad(i);

      std::cout << "(" << std::get<0>(t) << "," << std::get<1>(t) << ")"
                << " ";
    }

    std::cout << std::endl;
  }

  return 0;
}