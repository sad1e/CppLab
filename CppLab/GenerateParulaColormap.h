#pragma once

#include <pngwriter.h>

#include <cmath>

#include "fmath.h"

namespace parula {

Float cheaplobe(Float x, Float m, Float w) {
  return fmath::smoothstep(m - w, m, x) * fmath::smoothstep(m + w, m, x);
}

fmath::vec3 heatmap(Float c) {
  return fmath::pow(
      0.5 * (1.0 + fmath::cos(3.1 * c - fmath::vec3(2.7, 1.3, -0.2))),
      fmath::vec3(3., 3., 4.));
}

fmath::vec3 heatmap(fmath::vec3 c) {
  return fmath::pow(
      0.5 * (1.0 + fmath::cos(3.1 * c - fmath::vec3(2.7, 1.3, -0.2))),
      fmath::vec3(3., 3., 4.));
}

fmath::vec3 parula(Float c) {
  fmath::vec3 d = fmath::vec3(
      -0.1 + 0.22 * cheaplobe(c, 0.83, 0.19) - 0.07 * cheaplobe(c, 0.55, 0.16),
      0.02 - 0.21 * cheaplobe(c, 0.83, 0.26) -
          0.23 * cheaplobe(c, -0.02, 0.14) - 0.03 * cheaplobe(c, 0.59, 0.12),
      -0.11 * cheaplobe(c, 0.57, 0.2));
  fmath::vec3 w =
      fmath::vec3(0.52, 0.5, 0.53) +
      fmath::vec3(0.52, 0.52, 0.45) *
          fmath::sin(fmath::vec3(2.80, 2.80, 2.04) *
                     (fmath::vec3(c) - fmath::vec3(0.4, 0.4, -0.63)));
  fmath::vec3 p = fmath::vec3(fmath::mix(0.7, 0.8, c), fmath::mix(0.3, 0.7, c),
                              fmath::mix(2.9, 2.2, c));
  return fmath::pow(d + fmath::pow(w, p), fmath::vec3(1.5));
}

fmath::vec3 parula(fmath::vec3 c) {
  Float l = luminance(c);
  fmath::vec3 d = fmath::vec3(
      -0.1 + 0.22 * cheaplobe(l, 0.83, 0.19) - 0.07 * cheaplobe(l, 0.55, 0.16),
      0.02 - 0.21 * cheaplobe(l, 0.83, 0.26) -
          0.23 * cheaplobe(l, -0.02, 0.14) - 0.03 * cheaplobe(l, 0.59, 0.12),
      -0.11 * cheaplobe(l, 0.57, 0.2));
  fmath::vec3 w = fmath::vec3(0.52, 0.5, 0.53) +
                  fmath::vec3(0.52, 0.52, 0.45) *
                      fmath::sin(fmath::vec3(2.80, 2.80, 2.04) *
                                 (c - fmath::vec3(0.4, 0.4, -0.63)));
  fmath::vec3 p =
      fmath::vec3(fmath::mix(0.7, 0.8, c.x), fmath::mix(0.3, 0.7, c.y),
                  fmath::mix(2.9, 2.2, c.z));
  return fmath::pow(d + fmath::pow(w, p), fmath::vec3(1.5));
}

}  // namespace parula

void GenerateParulaColormap() {
  int width = 1024;
  int height = 32;

  pngwriter png(width, height, 0, "Parula.png");
  for (int i = 1; i <= width; ++i) {
    double uv_x = (double)i / width;
    fmath::vec3 v = parula::parula(uv_x);
    for (int j = 1; j <= height; ++j) {
      png.plot(i, j, v.x, v.y, v.z);
    }
  }
  png.close();
}
