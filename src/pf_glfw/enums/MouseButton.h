//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_ENUMS_MOUSEBUTTON_H
#define PF_GLFW_ENUMS_MOUSEBUTTON_H

#include <GLFW/glfw3.h>
#include <pf_glfw/_export.h>

namespace pf::glfw {

enum class PF_GLFW_EXPORT MouseButton {
  B1 = GLFW_MOUSE_BUTTON_1,
  B2 = GLFW_MOUSE_BUTTON_2,
  B3 = GLFW_MOUSE_BUTTON_3,
  B4 = GLFW_MOUSE_BUTTON_4,
  B5 = GLFW_MOUSE_BUTTON_5,
  B6 = GLFW_MOUSE_BUTTON_6,
  B7 = GLFW_MOUSE_BUTTON_7,
  B8 = GLFW_MOUSE_BUTTON_8,
  Last = GLFW_MOUSE_BUTTON_LAST,
  Left = GLFW_MOUSE_BUTTON_LEFT,
  Right = GLFW_MOUSE_BUTTON_RIGHT,
  Middle = GLFW_MOUSE_BUTTON_MIDDLE
};

}  // namespace pf::glfw

#endif  // PF_GLFW_ENUMS_MOUSEBUTTON_H
