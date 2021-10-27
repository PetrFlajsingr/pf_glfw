//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_SRC_PF_GLFW_ENUMS_CURSORSHAPE_H
#define PF_GLFW_SRC_PF_GLFW_ENUMS_CURSORSHAPE_H

#include <GLFW/glfw3.h>

namespace pf::glfw {

enum class CursorShape {
  Arrow = GLFW_ARROW_CURSOR,
  IBeam = GLFW_IBEAM_CURSOR,
  Crosshair = GLFW_CROSSHAIR_CURSOR,
  Hand = GLFW_HAND_CURSOR,
  VResize = GLFW_VRESIZE_CURSOR
};

}

#endif//PF_GLFW_SRC_PF_GLFW_ENUMS_CURSORSHAPE_H
