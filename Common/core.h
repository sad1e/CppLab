#pragma once

#define DISABLE_CPP_COPY(T) \
  T(const T&) = delete;     \
  T& operator=(const T&) = delete

#define DISABLE_CPP_MOVE(T) \
  T(T&&) = delete;          \
  T& operator=(T&&) = delete

#define DISABLE_CPP_COPY_AND_MOVE(T) \
  DISABLE_CPP_COPY(T);               \
  DISABLE_CPP_MOVE(T)
