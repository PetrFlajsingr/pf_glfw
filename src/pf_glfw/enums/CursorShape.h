//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_ENUMS_CURSORSHAPE_H
#define PF_GLFW_ENUMS_CURSORSHAPE_H

#include <GLFW/glfw3.h>
#include <pf_glfw/_export.h>

namespace pf::glfw {

enum class PF_GLFW_EXPORT CursorShape {
  Arrow = GLFW_ARROW_CURSOR,
  IBeam = GLFW_IBEAM_CURSOR,
  Crosshair = GLFW_CROSSHAIR_CURSOR,
  Hand = GLFW_HAND_CURSOR,
  VResize = GLFW_VRESIZE_CURSOR
};

}  // namespace pf::glfw

#endif  // PF_GLFW_ENUMS_CURSORSHAPE_H
