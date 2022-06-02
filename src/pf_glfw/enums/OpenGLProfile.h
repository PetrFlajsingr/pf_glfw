//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_ENUMS_OPENGLPROFILE_H
#define PF_GLFW_ENUMS_OPENGLPROFILE_H

#include <GLFW/glfw3.h>
#include <pf_glfw/_export.h>

namespace pf::glfw {

enum class PF_GLFW_EXPORT OpenGLProfile {
  Compat = GLFW_OPENGL_COMPAT_PROFILE,
  Core = GLFW_OPENGL_CORE_PROFILE,
  Any = GLFW_OPENGL_ANY_PROFILE
};

}  // namespace pf::glfw

#endif  // PF_GLFW_ENUMS_OPENGLPROFILE_H
