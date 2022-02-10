//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_STRUCTS_H
#define PF_GLFW_STRUCTS_H

#include <pf_glfw/_export.h>

namespace pf::glfw {

struct PF_GLFW_EXPORT Version {
  int major;
  int minor;
  int revision;
};
template<typename T>
struct PF_GLFW_EXPORT Position {
  T x;
  T y;
};
template<typename T>
struct PF_GLFW_EXPORT Size {
  T width;
  T height;
};
template<typename T>
struct PF_GLFW_EXPORT Area {
  Position<T> position;
  T width;
  T height;
};
template<typename T>
struct PF_GLFW_EXPORT Box {
  Position<T> leftTop;
  Position<T> rightBottom;
};
struct PF_GLFW_EXPORT Scale {
  float x;
  float y;
};

}  // namespace pf::glfw

#endif  // PF_GLFW_STRUCTS_H
