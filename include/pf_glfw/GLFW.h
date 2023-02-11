//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_GLFW_H
#define PF_GLFW_GLFW_H

#include "ErrorInfo.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include <memory>
#include <optional>
#include <string>
#include <tl/expected.hpp>
#include <vector>

namespace pf::glfw {

class GLFW {
 public:
  [[nodiscard]] static tl::expected<GLFW, ErrorInfo> Create() {
    if (glfwInit() != GLFW_TRUE) {
      const auto error = details::getLastError();
      return tl::make_unexpected(error.value_or(ErrorInfo{Error::Unknown, ""}));
    }
    return GLFW{};
  }
  ~GLFW() { glfwTerminate(); }

  [[nodiscard]] static Version GetVersion() {
    Version result{};
    glfwGetVersion(&result.major, &result.minor, &result.revision);
    return result;
  }

  [[nodiscard]] tl::expected<std::shared_ptr<Window>, ErrorInfo> createWindow(const WindowOpenGlConfig &config) {
    GLFWmonitor *monitor = nullptr;
    if (config.monitor.has_value()) {
      // the pointed to struct is never const
      monitor = const_cast<GLFWmonitor *>(config.monitor->getHandle());
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.majorOpenGLVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.minorOpenGLVersion);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, static_cast<int>(config.clientApi));

    config.hints.apply(true);
    const auto windowHandle =
        glfwCreateWindow(static_cast<int>(config.width), static_cast<int>(config.height), config.title.c_str(), monitor, nullptr);
    if (windowHandle == nullptr) {
      if (const auto error = details::getLastError(); error.has_value()) { return tl::make_unexpected(*error); }
    }
    return createAndRegisterWindowImpl(windowHandle);
  }
  [[nodiscard]] tl::expected<std::shared_ptr<Window>, ErrorInfo> createWindow(const WindowNoApiConfig &config) {
    GLFWmonitor *monitor = nullptr;
    if (config.monitor.has_value()) {
      // the pointed to struct is never const
      monitor = const_cast<GLFWmonitor *>(config.monitor->getHandle());
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    config.hints.apply(false);
    const auto windowHandle =
        glfwCreateWindow(static_cast<int>(config.width), static_cast<int>(config.height), config.title.c_str(), monitor, nullptr);
    if (windowHandle == nullptr) {
      if (const auto error = details::getLastError(); error.has_value()) { return tl::make_unexpected(*error); }
    }
    return createAndRegisterWindowImpl(windowHandle);
  }
  void removeWindow(const std::shared_ptr<Window> &window) { std::erase(windows, window); }

  void setCurrentWindow(const std::shared_ptr<Window> &window) { glfwMakeContextCurrent(window->getHandle()); }

  void pollEvents() { glfwPollEvents(); }
  void waitEvents() { glfwWaitEvents(); }
  void waitEvents(std::chrono::milliseconds timeout) { glfwWaitEventsTimeout(static_cast<double>(timeout.count()) / 1000.0); }

  [[nodiscard]] double getTime() const { return glfwGetTime(); }
  void setTime(double time) { glfwSetTime(time); }

  [[nodiscard]] std::uint64_t getTimerValue() const { return glfwGetTimerValue(); }
  [[nodiscard]] std::uint64_t getTimerFrequency() const { return glfwGetTimerFrequency(); }

  void setSwapInterval(std::size_t interval) { glfwSwapInterval(static_cast<int>(interval)); }

  [[nodiscard]] decltype(&glfwGetProcAddress) getLoaderFnc() const { return glfwGetProcAddress; }

  [[nodiscard]] bool isExtensionSupported(const std::string &extension) const {
    return glfwExtensionSupported(extension.c_str()) == GLFW_TRUE;
  }

  [[nodiscard]] std::vector<std::string> getRequiredVulkanExtensions() const {
    std::uint32_t count;
    const auto extensions = glfwGetRequiredInstanceExtensions(&count);
    const auto extSpan = std::span{extensions, count};
    return std::vector<std::string>{extSpan.begin(), extSpan.end()};
  }

 private:
  GLFW() = default;

  [[nodiscard]] std::shared_ptr<Window> createAndRegisterWindowImpl(GLFWwindow *handle) {
    auto result = windows.emplace_back(new Window{handle});
    // user pointer for callbacks
    glfwSetWindowUserPointer(handle, result.get());
    return result;
  }

  std::vector<std::shared_ptr<Window>> windows;
};

}  // namespace pf::glfw

#endif  // PF_GLFW_GLFW_H
