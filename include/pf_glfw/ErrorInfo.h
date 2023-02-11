//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_EXCEPTION_H
#define PF_GLFW_EXCEPTION_H

#include <exception>
#include <optional>
#include <pf_glfw/enums/Error.h>
#include <string>
#include <utility>

namespace pf::glfw {

struct ErrorInfo {
  Error error;
  std::string description;
};

namespace details {

inline std::optional<ErrorInfo> getLastError() {
  const char *desc;
  const auto code = static_cast<Error>(glfwGetError(&desc));
  if (code == Error::NoError) { return std::nullopt; }
  if (desc != nullptr) { return ErrorInfo{code, desc}; }
  return ErrorInfo{code, ""};
}

}  // namespace details
}  // namespace pf::glfw

#endif  // PF_GLFW_EXCEPTION_H
