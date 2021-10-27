//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_SRC_PF_GLFW_STRUCTS_H
#define PF_GLFW_SRC_PF_GLFW_STRUCTS_H

namespace pf::glfw {

struct CursorPosition {
  double x;
  double y;
};
struct WindowPosition {
  int x;
  int y;
};
struct WindowSize {
  int width;
  int height;
};
struct MonitorPosition {
  int x;
  int y;
};
struct MonitorWorkArea {
  MonitorPosition position;
  int width;
  int height;
};
struct MonitorSize {
  int width;
  int height;
};
struct MonitorScale {
  float x;
  float y;
};
}// namespace pf::glfw

#endif//PF_GLFW_SRC_PF_GLFW_STRUCTS_H
