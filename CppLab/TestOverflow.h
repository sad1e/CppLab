#pragma once

#include <type_traits>
#include <limits>

#define CPU_WORDSIZE 8

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;
using f32 = float;
using f64 = double;

template <int>
struct TIntegerForSize;
template <>
struct TIntegerForSize<1> {
  typedef u8 Unsigned;
  typedef s8 Signed;
};
template <>
struct TIntegerForSize<2> {
  typedef u16 Unsigned;
  typedef s16 Signed;
};
template <>
struct TIntegerForSize<4> {
  typedef u32 Unsigned;
  typedef s32 Signed;
};
template <>
struct TIntegerForSize<8> {
  typedef u64 Unsigned;
  typedef s64 Signed;
};
template <typename T>
struct TIntegerForSizeof : TIntegerForSize<sizeof(T)> {};
typedef TIntegerForSize<CPU_WORDSIZE>::Signed hregisterint_t;
typedef TIntegerForSize<CPU_WORDSIZE>::Unsigned hregisteruint_t;
typedef TIntegerForSizeof<void *>::Unsigned huintptr_t;
typedef TIntegerForSizeof<void *>::Signed hptrdiff_t;

typedef hptrdiff_t hintptr_t;
using hsize_t = TIntegerForSizeof<std::size_t>::Signed;

template <typename T>
inline typename std::enable_if_t<std::is_unsigned_v<T> || std::is_signed_v<T>,
                                 bool>
MulOverflow(T v1, T v2, T *r) {
  using LargerInt = TIntegerForSize<sizeof(T) * 2>;
  using Larger = typename std::conditional_t<std::is_signed_v<T>,
                                             typename LargerInt::Signed,
                                             typename LargerInt::Unsigned>;

  Larger l = Larger(v1) * Larger(v2);
  *r = T(l);
  return l > (std::numeric_limits<T>::max)() ||
         l < (std::numeric_limits<T>::min)();
}

hsize_t CalculateBlockSize(hsize_t element_count, hsize_t element_size,
                           hsize_t header_size) noexcept {
  size_t bytes;
  if (MulOverflow(size_t(element_size), size_t(element_count), &bytes) ||
      AddOverflow(bytes, size_t(header_size), &bytes)) {
    return -1;
  }

  if (hsize_t(bytes) < 0) {
    return -1;
  }

  return hsize_t(bytes);
}