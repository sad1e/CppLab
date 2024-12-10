#pragma once

#include <cmath>
#include <concepts>

#define USE_DOUBLE 1

#ifdef USE_DOUBLE
#define Float double
#else
#define Float float
#endif

namespace fmath {

template <std::floating_point T>
constexpr T clamp(T v, T mi, T ma) {
  return v <= mi ? mi : v >= ma ? ma : v;
}

template <std::floating_point T>
constexpr T saturate(T v) {
  return clamp(v, 0.0, 1.0);
}

template <std::floating_point T>
constexpr T smoothstep(T a, T b, T x) {
  T t = saturate((x - a) / (b - a));
  return t * t * (3.0 - (2.0 * t));
}

template <std::floating_point T>
constexpr T mix(T x, T y, T a) {
  return x * (1 - a) + y * a;
}

struct vec3 {
  vec3() = default;
  vec3(const vec3& v) = default;
  vec3& operator=(const vec3& v) = default;
  vec3(vec3&& v) = default;
  vec3& operator=(vec3&& v) = default;

  explicit vec3(Float v) : x{v}, y{v}, z{v} {}
  vec3(Float x_, Float y_, Float z_) : x{x_}, y{y_}, z{z_} {}

  vec3 operator+(const vec3& v) { return vec3{x + v.x, y + v.y, z + v.z}; }
  vec3& operator+=(const vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  vec3 operator+(Float c) { return vec3{x + c, y + c, z + c}; }
  vec3& operator+=(Float c) {
    x += c;
    y += c;
    z += c;
    return *this;
  }
  vec3 operator-(const vec3& v) { return vec3{x - v.x, y - v.y, z - v.z}; }
  vec3& operator-=(const vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  vec3 operator-(Float c) { return vec3{x - c, y - c, z - c}; }
  vec3& operator-=(Float c) {
    x -= c;
    y -= c;
    z -= c;
    return *this;
  }
  vec3 operator*(const vec3& v) { return vec3{x * v.x, y * v.y, z * v.z}; }
  vec3& operator*=(const vec3& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }
  vec3 operator*(Float c) { return vec3{x * c, y * c, z * c}; }
  vec3& operator*=(Float c) {
    x *= c;
    y *= c;
    z *= c;
    return *this;
  }
  vec3 operator/(const vec3& v) { return vec3{x / v.x, y / v.y, z / v.z}; }
  vec3& operator/=(const vec3& v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
  }
  vec3 operator/(Float c) { return vec3{x / c, y / c, z / c}; }
  vec3& operator/=(Float c) {
    x /= c;
    y /= c;
    z /= c;
    return *this;
  }

  vec3 operator-() { return vec3{-x, -y, -z}; }

  friend vec3 operator+(Float c, vec3 v);
  friend vec3 operator-(Float c, vec3 v);
  friend vec3 operator*(Float c, vec3 v);
  friend vec3 operator/(Float c, vec3 v);

  Float x{0}, y{0}, z{0};
};

vec3 operator+(Float c, vec3 v) { return vec3{c + v.x, c + v.y, c + v.z}; }

vec3 operator-(Float c, vec3 v) { return vec3{c - v.x, c - v.y, c - v.z}; }

vec3 operator*(Float c, vec3 v) { return vec3{c * v.x, c * v.y, c * v.z}; }

vec3 operator/(Float c, vec3 v) { return vec3{c / v.x, c / v.y, c / v.z}; }

Float dot(const vec3& v0, const vec3& v1) {
  return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

Float luminance(const vec3& v) {
  return v.x * 0.299 + v.y * 0.587 + v.z * 0.114;
}

vec3 pow(const vec3& b, const vec3& e) {
#if USE_DOUBLE
  return vec3{std::pow(b.x, e.x), std::pow(b.y, e.y), std::pow(b.z, e.z)};
#else
  return vec3{std::powf(b.x, e.x), std::powf(b.y, e.y), std::powf(b.z, e.z)};
#endif
}

vec3 sin(const vec3& v) {
#if USE_DOUBLE
  return vec3{std::sin(v.x), std::sin(v.y), std::sin(v.z)};
#else
  return vec3{std::sinf(v.x), std::sinf(v.y), std::sinf(v.z)};
#endif
}

vec3 cos(const vec3& v) {
#if USE_DOUBLE
  return vec3{std::cos(v.x), std::cos(v.y), std::cos(v.z)};
#else
  return vec3{std::cosf(v.x), std::cosf(v.y), std::cosf(v.z)};
#endif
}

vec3 mix(const vec3& x, const vec3& y, const vec3& a) {
  return vec3{
      mix(x.x, y.x, a.x),
      mix(x.y, y.y, a.y),
      mix(x.z, y.z, a.z),
  };
}

}  // namespace fmath
