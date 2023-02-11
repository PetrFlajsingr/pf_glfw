//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_STRUCTS_H
#define PF_GLFW_STRUCTS_H


namespace pf::glfw {

struct Version {
  int major;
  int minor;
  int revision;
};
template<typename T>
struct Position {
  T x;
  T y;
};
template<typename T>
struct Size {
  T width;
  T height;
};
template<typename T>
struct Area {
  Position<T> position;
  T width;
  T height;
};
template<typename T>
struct Box {
  Position<T> leftTop;
  Position<T> rightBottom;
};
struct Scale {
  float x;
  float y;
};

}  // namespace pf::glfw

#endif  // PF_GLFW_STRUCTS_H
