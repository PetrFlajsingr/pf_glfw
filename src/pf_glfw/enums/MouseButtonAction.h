//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_ENUMS_MOUSEBUTTONACTION_H
#define PF_GLFW_ENUMS_MOUSEBUTTONACTION_H

#include <GLFW/glfw3.h>
#include <pf_glfw/_export.h>

namespace pf::glfw {
enum class PF_GLFW_EXPORT MouseButtonAction {
  Press = GLFW_PRESS,
  Release = GLFW_RELEASE
};
}

#endif//PF_GLFW_ENUMS_MOUSEBUTTONACTION_H
