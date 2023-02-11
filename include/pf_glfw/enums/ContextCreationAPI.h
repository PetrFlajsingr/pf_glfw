//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_ENUMS_CONTEXTCREATIONAPI_H
#define PF_GLFW_ENUMS_CONTEXTCREATIONAPI_H

#include <GLFW/glfw3.h>

namespace pf::glfw {

enum class ContextCreationAPI {
  Native = GLFW_NATIVE_CONTEXT_API,
  Egl = GLFW_EGL_CONTEXT_API,
  Osmesa = GLFW_OSMESA_CONTEXT_API
};

}  // namespace pf::glfw

#endif  // PF_GLFW_ENUMS_CONTEXTCREATIONAPI_H
