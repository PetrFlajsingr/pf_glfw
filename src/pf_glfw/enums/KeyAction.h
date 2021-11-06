//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_ENUMS_KEYACTION_H
#define PF_GLFW_ENUMS_KEYACTION_H

#include <GLFW/glfw3.h>
#include <pf_glfw/_export.h>

namespace pf::glfw {
enum class PF_GLFW_EXPORT KeyAction {
  Down = GLFW_PRESS,
  Up = GLFW_RELEASE,
  Repeat = GLFW_REPEAT
};
}

#endif//PF_GLFW_ENUMS_KEYACTION_H
