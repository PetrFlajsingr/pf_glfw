//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_SRC_PF_GLFW_ENUMS_KEYACTION_H
#define PF_GLFW_SRC_PF_GLFW_ENUMS_KEYACTION_H

#include <GLFW/glfw3.h>

namespace pf::glfw {
enum class KeyAction {
  Press = GLFW_PRESS,
  Release = GLFW_RELEASE,
  Repeat = GLFW_REPEAT
};
}

#endif//PF_GLFW_SRC_PF_GLFW_ENUMS_KEYACTION_H
