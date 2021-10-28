//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_SRC_PF_GLFW_ENUMS_CONTEXTCREATIONAPI_H
#define PF_GLFW_SRC_PF_GLFW_ENUMS_CONTEXTCREATIONAPI_H

#include <GLFW/glfw3.h>
#include <pf_glfw/_export.h>

namespace pf::glfw {
#ifdef PF_GLFW_OPENGL
enum class PF_GLFW_EXPORT ContextCreationAPI {
  Native = GLFW_NATIVE_CONTEXT_API,
  Egl = GLFW_EGL_CONTEXT_API,
  Osmesa = GLFW_OSMESA_CONTEXT_API
};
#endif
}// namespace pf::glfw

#endif//PF_GLFW_SRC_PF_GLFW_ENUMS_CONTEXTCREATIONAPI_H
