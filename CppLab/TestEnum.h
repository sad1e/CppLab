#pragma once

#include <iostream>
#include <type_traits>

template <class T, std::enable_if_t<std::is_enum_v<T>, int> = 0>
constexpr T operator|(T lhs, T rhs) {
  return static_cast<T>(static_cast<std::underlying_type<T>::type>(lhs) |
                        static_cast<std::underlying_type<T>::type>(rhs));
}

template <class T, std::enable_if_t<std::is_enum_v<T>, int> = 0>
constexpr T operator&(T lhs, T rhs) {
  return static_cast<T>(static_cast<std::underlying_type<T>::type>(lhs) &
                        static_cast<std::underlying_type<T>::type>(rhs));
}

template <class T, std::enable_if_t<std::is_enum_v<T>, int> = 0>
constexpr bool operator==(T lhs, T rhs) {
  return (static_cast<std::underlying_type<T>::type>(lhs) ==
          static_cast<std::underlying_type<T>::type>(rhs));
}

template <class T, std::enable_if_t<std::is_enum_v<T>, int> = 0>
constexpr bool operator!=(T lhs, T rhs) {
  return (static_cast<std::underlying_type<T>::type>(lhs) !=
          static_cast<std::underlying_type<T>::type>(rhs));
}

enum class EModifier : uint16_t {
  None = 0,
  LeftAlt = 0x01,
  RightAlt = 0x02,
  LeftCtrl = 0x04,
  RightCtrl = 0x08,
  LeftShift = 0x10,
  RightShift = 0x20,
  LeftMeta = 0x40,
  RightMeta = 0x80,
};

void TestEnum() {
  EModifier m0 = EModifier::LeftAlt;
  EModifier m1 = EModifier::LeftMeta;

  EModifier mr = m0 | m1;

  std::cout << static_cast<uint16_t>(mr & m1) << std::endl;
}
