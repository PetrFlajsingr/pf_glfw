//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_ENUMS_CONTEXTROBUSTNESS_H
#define PF_GLFW_ENUMS_CONTEXTROBUSTNESS_H

#include <GLFW/glfw3.h>

namespace pf::glfw {

enum class ContextRobustness {
  No = GLFW_NO_ROBUSTNESS,
  NoResetNotification = GLFW_NO_RESET_NOTIFICATION,
  LoseContextOnReset = GLFW_LOSE_CONTEXT_ON_RESET
};

}  // namespace pf::glfw

#endif  // PF_GLFW_ENUMS_CONTEXTROBUSTNESS_H
