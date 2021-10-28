//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_SRC_PF_GLFW_STRUCTS_H
#define PF_GLFW_SRC_PF_GLFW_STRUCTS_H

#include <pf_glfw/_export.h>

namespace pf::glfw {
struct PF_GLFW_EXPORT Version {
  int major;
  int minor;
  int revision;
};

struct PF_GLFW_EXPORT CursorPosition {
  double x;
  double y;
};
struct PF_GLFW_EXPORT WindowPosition {
  int x;
  int y;
};
struct PF_GLFW_EXPORT WindowSize {
  int width;
  int height;
};
struct PF_GLFW_EXPORT MonitorPosition {
  int x;
  int y;
};
struct PF_GLFW_EXPORT MonitorWorkArea {
  MonitorPosition position;
  int width;
  int height;
};
struct PF_GLFW_EXPORT MonitorSize {
  int width;
  int height;
};
struct PF_GLFW_EXPORT MonitorScale {
  float x;
  float y;
};
}// namespace pf::glfw

#endif//PF_GLFW_SRC_PF_GLFW_STRUCTS_H
