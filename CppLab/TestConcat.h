#pragma once

enum ETestEnum {
  FOO0_BAR0 = 0,
  FOO0_BAR1 = 1,
  FOO1_BAR0 = 2,
  FOO1_BAR1 = 3,
};

#define ContructTestEnum(x, y) FOO##x##_BAR##y

template <int TFoo, int TBar>
ETestEnum
TConstructTestEnum() {
  return FOO1_BAR1;
  // return ContructTestEnum(TFoo, TBar); // error!
}

void
GetEnumFromVariable() {
  int a = 0;
  int b = 1;

  // ETestEnum te0 = TConstructTestEnum<0, 1>();

  int c = 100;
  ETestEnum te = (ETestEnum)c;
  switch (te) {
    case FOO0_BAR0:
      printf("FOO0_BAR0.\n");
    case FOO0_BAR1:
      printf("FOO0_BAR1.\n");
    case FOO1_BAR0:
      printf("FOO1_BAR0.\n");
    case FOO1_BAR1:
      printf("FOO1_BAR1.\n");
    default:
      printf("default.\n");
  }
}
