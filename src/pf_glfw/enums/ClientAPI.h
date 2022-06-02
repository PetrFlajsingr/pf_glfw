//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_ENUMS_CLIENTAPI_H
#define PF_GLFW_ENUMS_CLIENTAPI_H

#include <GLFW/glfw3.h>
#include <pf_glfw/_export.h>

namespace pf::glfw {

enum class PF_GLFW_EXPORT ClientAPI {
  OpenGLES = GLFW_OPENGL_ES_API,
  OpenGL = GLFW_OPENGL_API,
  None = GLFW_NO_API
};

}  // namespace pf::glfw

#endif  // PF_GLFW_ENUMS_CLIENTAPI_H
