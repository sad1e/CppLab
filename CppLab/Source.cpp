#include "stdafx.h"

#define TEST_AABB_PLANE 0
#define TEST_SINGLETON 0
#define TEST_MEM 0
#define TEST_FLOAT 1

// #include "GenerateParulaColormap.h"
// #include "TestAABBPlane.h"
// #include "TestConcat.h"
// #include "TestEnum.h"
// #include "TestFloat.h"
// #include "TestMem.h"
// #include "TestSingleton.h"

#include "TestThread.h"
#include "TestThread2.h"
#include "TestThread4.h"

int main(int argc, char** argv) {
  // GetEnumFromVariable();
  // GenerateParulaColormap();

  // TestEnum();

  // test_thread();
  test_thread2();

  return 0;
}
