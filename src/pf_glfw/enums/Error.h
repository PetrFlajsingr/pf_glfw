//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_ENUMS_ERROR_H
#define PF_GLFW_ENUMS_ERROR_H

#include <GLFW/glfw3.h>
#include <pf_glfw/_export.h>

namespace pf::glfw {

enum class PF_GLFW_EXPORT Error {
  NoError = GLFW_NO_ERROR,
  NotInitialized = GLFW_NOT_INITIALIZED,
  NoCurrentContext = GLFW_NO_CURRENT_CONTEXT,
  InvalidEnum = GLFW_INVALID_ENUM,
  InvalidValue = GLFW_INVALID_VALUE,
  OutOfMemory = GLFW_OUT_OF_MEMORY,
  ApiUnavailable = GLFW_API_UNAVAILABLE,
  VersionUnavailable = GLFW_VERSION_UNAVAILABLE,
  PlatformError = GLFW_PLATFORM_ERROR,
  FormatUnavailable = GLFW_FORMAT_UNAVAILABLE,
  NoWindowContext = GLFW_NO_WINDOW_CONTEXT
};

}  // namespace pf::glfw

#endif  // PF_GLFW_ENUMS_ERROR_H
