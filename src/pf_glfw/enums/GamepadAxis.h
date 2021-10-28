//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_ENUMS_GAMEPADAXIS_H
#define PF_GLFW_ENUMS_GAMEPADAXIS_H

#include <GLFW/glfw3.h>
#include <pf_glfw/_export.h>

namespace pf::glfw {
enum class PF_GLFW_EXPORT GamepadAxis {
  LeftX = GLFW_GAMEPAD_AXIS_LEFT_X,
  LeftY = GLFW_GAMEPAD_AXIS_LEFT_Y,
  RightX = GLFW_GAMEPAD_AXIS_RIGHT_X,
  RightY = GLFW_GAMEPAD_AXIS_RIGHT_Y,
  LeftTrigger = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
  RightTrigger = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
  Last = GLFW_GAMEPAD_AXIS_LAST
};
}
#endif//PF_GLFW_ENUMS_GAMEPADAXIS_H
