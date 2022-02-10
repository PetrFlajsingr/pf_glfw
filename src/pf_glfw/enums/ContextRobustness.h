//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_ENUMS_CONTEXTROBUSTNESS_H
#define PF_GLFW_ENUMS_CONTEXTROBUSTNESS_H

#include <GLFW/glfw3.h>
#include <pf_glfw/_export.h>

namespace pf::glfw {
#ifdef PF_GLFW_OPENGL
enum class PF_GLFW_EXPORT ContextRobustness {
  No = GLFW_NO_ROBUSTNESS,
  NoResetNotification = GLFW_NO_RESET_NOTIFICATION,
  LoseContextOnReset = GLFW_LOSE_CONTEXT_ON_RESET
};
#endif
}  // namespace pf::glfw

#endif  // PF_GLFW_ENUMS_CONTEXTROBUSTNESS_H
