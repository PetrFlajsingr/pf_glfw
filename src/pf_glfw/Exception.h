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

class PF_GLFW_EXPORT Exception : public std::exception {
 public:
  template<typename... Args>
  explicit Exception(Error error, std::string message) : eType(error), msg(std::move(message)) {
  }
  [[nodiscard]] inline const char *what() const noexcept override {
    return msg.c_str();
  }
  [[nodiscard]] inline Error type() const {
    return eType;
  }

 private:
  Error eType;
  std::string msg;
};

namespace details {
inline std::optional<Exception> getLastError() {
  const char *desc;
  const auto code = static_cast<Error>(glfwGetError(&desc));
  if (code == Error::NoError) {
    return std::nullopt;
  }
  if (desc != nullptr) {
    return Exception{code, desc};
  }
  return Exception{code, ""};
}

inline void getLastErrorAndThrow() {
  const auto error = getLastError();
  if (error.has_value()) {
    throw error.value();
  }
}
}// namespace details

}// namespace pf::glfw

#endif//PF_GLFW_EXCEPTION_H
