//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_ENUMS_CONTEXTRELEASEBEHAVIOR_H
#define PF_GLFW_ENUMS_CONTEXTRELEASEBEHAVIOR_H

#include <GLFW/glfw3.h>
#include <pf_glfw/_export.h>

namespace pf::glfw {

enum class PF_GLFW_EXPORT ContextReleaseBehavior {
  Any = GLFW_ANY_RELEASE_BEHAVIOR,
  Flush = GLFW_RELEASE_BEHAVIOR_FLUSH,
  None = GLFW_RELEASE_BEHAVIOR_NONE
};

}  // namespace pf::glfw

#endif  // PF_GLFW_ENUMS_CONTEXTRELEASEBEHAVIOR_H
