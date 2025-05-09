#pragma once

#include <iostream>
#include <vector>

#include "callocator.h"
#include "io.h"
#include "mem_common.h"
#include "linear_allocator.h"
#include "stl_simple_allocator.h"

using namespace fcpp;

#define DEFAULT_ALIGNMENT 16u

void test_addr() {
  int* p = new int(42);

  constexpr size_t alignment = 16u;

  int* tp = p + 1;

  printf("src       p: 0x%p\n", p);
  printf("alignup   p: 0x%p\n", AlignUp(tp, alignment));
  printf("aligndown p: 0x%p\n", AlignDown(tp, alignment));
  uintptr_t fwd_p = AlignForward(reinterpret_cast<uintptr_t>(tp), alignment);
  printf("alignfwd  p: 0x%p\n", reinterpret_cast<void*>(fwd_p));

  delete p;
}

void test_linear_allocator(LinearAllocator& linear_allocator) {
  int* int_array = static_cast<int*>(
      linear_allocator.alloc(sizeof(int) * 10u, DEFAULT_ALIGNMENT));

  if (int_array) {
    for (int i = 0; i < 10; ++i) {
      int_array[i] = i * 10;
    }

    std::cout << "allocated integers: \n";
    for (int i = 0; i < 10; ++i) {
      std::cout << "\t" << int_array[i] << ", ";
    }
    std::cout << io::endl;
  }

  double* double_scalar = static_cast<double*>(
      linear_allocator.alloc(sizeof(double), DEFAULT_ALIGNMENT));
  if (double_scalar) {
    *double_scalar = 3.141592653;
    std::cout << "allocated double: " << *double_scalar << io::endl;
  }
}

struct TestStruct {};

int main(int argc, char** argv) {
  size_t total_size = 1024;

  // LinearAllocator linear_allocator(total_size);
  // SimpleAllocatorSTL<int> simple_allocator(linear_allocator);

  //   std::vector<int, SimpleAllocatorSTL<int>> int_vec(linear_allocator);
  //   for (int i = 0; i < 10; ++i) {
  //     int_vec.push_back(i * 10);
  //   }

  //   for (const auto& v : int_vec) {
  //     std::cout << v << ", ";
  //   }
  //   std::cout << io::endl;

  std::cout << alignof(TestStruct) << io::endl;

  std::cout << "sizeof(size_t): " << sizeof(std::size_t) << io::endl;
  std::cout << "sizeof(ull):    " << sizeof(unsigned long long) << io::endl;

#ifdef __cpp_char8_t
  std::cout << "__cpp_char8_t\n";
#else
  std::cout << "no __cpp_char8_t\n";
#endif

  return 0;
}