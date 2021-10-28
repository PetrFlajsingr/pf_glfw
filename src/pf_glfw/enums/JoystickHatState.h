//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_ENUMS_JOYSTICKHATSTATE_H
#define PF_GLFW_ENUMS_JOYSTICKHATSTATE_H

#include <GLFW/glfw3.h>
#include <pf_glfw/_export.h>

namespace pf::glfw {
enum class PF_GLFW_EXPORT JoystickHatState {
  Centered = GLFW_HAT_CENTERED,
  Up = GLFW_HAT_UP,
  Right = GLFW_HAT_RIGHT,
  Down = GLFW_HAT_DOWN,
  Left = GLFW_HAT_LEFT,
  Right_up = GLFW_HAT_RIGHT_UP,
  Right_down = GLFW_HAT_RIGHT_DOWN,
  Left_up = GLFW_HAT_LEFT_UP,
  Left_down = GLFW_HAT_LEFT_DOWN,
};
}
#endif//PF_GLFW_ENUMS_JOYSTICKHATSTATE_H
