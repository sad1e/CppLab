#pragma once

#include <cstdio>
#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename T>
std::string type_name() {
  using TR = typename std::remove_reference<T>::type;
  std::unique_ptr<char, void (*)(void*)> own(
#ifndef _MSC_VER
      abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
#else
      nullptr,
#endif
      std::free);
  std::string r = own != nullptr ? own.get() : typeid(TR).name();
  if (std::is_const<TR>::value) r += " const";
  if (std::is_volatile<TR>::value) r += " volatile";
  if (std::is_lvalue_reference<T>::value)
    r += "&";
  else if (std::is_rvalue_reference<T>::value)
    r += "&&";
  return r;
}

template <typename T>
struct ImplementsToDevice {
  typedef char one;
  struct two {
    char x[2];
  };

  template <typename C>
  static one test(decltype(&C::ToDevice));

  template <typename C>
  static two test(...);
};

typedef char Tone;
struct Ttwo {
  char x[2];
};

template <typename C>
static Tone test(decltype(&C::ToDevice)) {
  printf("one.\n");
  return 0;
}

template <typename C>
static Ttwo test(...) {
  printf("two.\n");
  return Ttwo();
}

struct StructHasNoToDevice {};

struct StructHasToDevice {
  void ToDevice() {}
};

void SFINAE_test() {
  // the decltype(&StructHasNoToDevice::ToDevice) will failed, template function
  // cannot matched, so this expression will fall to `static Ttwo test(...)`.
  // It will print "two".
  auto t0 = test<StructHasNoToDevice>(0);
  // the decltype(&StructHasToDevice::ToDevice) will matched).
  // It will print "one".
  auto t1 = test<StructHasToDevice>(0);

  //> Not matched.
  // std::cout << type_name<decltype(&StructHasNoToDevice::ToDevice)>() << '\n';
  //> Matched.
  std::cout << type_name<decltype(&StructHasToDevice::ToDevice)>() << '\n';
}