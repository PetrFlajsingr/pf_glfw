//
// Created by xflajs00 on 28.10.2021.
//

#include "GLFW.h"
#include <pf_glfw/Window.h>

namespace pf::glfw {

GLFW::GLFW() {  //-V730
  if (glfwInit() != GLFW_TRUE) { details::getLastErrorAndThrow(); }
}

GLFW::~GLFW() { glfwTerminate(); }

Version GLFW::GetVersion() {
  Version result{};
  glfwGetVersion(&result.major, &result.minor, &result.revision);
  return result;
}

const std::shared_ptr<Window> &GLFW::createWindow(const pf::glfw::WindowOpenGlConfig &config) {
  auto window = std::shared_ptr<Window>(new Window{config});  //-V824
  return windows.emplace_back(window);
}

const std::shared_ptr<Window> &GLFW::createWindow(const pf::glfw::WindowNoApiConfig &config) {
  auto window = std::shared_ptr<Window>(new Window{config});  //-V824
  return windows.emplace_back(window);
}

void GLFW::removeWindow(const std::shared_ptr<Window> &window) { std::erase(windows, window); }

void GLFW::setCurrentWindow(const std::shared_ptr<Window> &window) { glfwMakeContextCurrent(window->getHandle()); }

bool GLFW::isExtensionSupported(const std::string &extension) const {
  return glfwExtensionSupported(extension.c_str()) == GLFW_TRUE;
}

std::vector<std::string> GLFW::getRequiredVulkanExtensions() const {
  std::uint32_t count;
  const auto extensions = glfwGetRequiredInstanceExtensions(&count);
  const auto extSpan = std::span{extensions, count};
  return std::vector<std::string>{extSpan.begin(), extSpan.end()};
}

void GLFW::pollEvents() { glfwPollEvents(); }

void GLFW::waitEvents() { glfwWaitEvents(); }

void GLFW::waitEvents(std::chrono::milliseconds timeout) {
  glfwWaitEventsTimeout(static_cast<double>(timeout.count()) / 1000.0);
}

double GLFW::getTime() const { return glfwGetTime(); }

void GLFW::setTime(double time) { glfwSetTime(time); }

std::uint64_t GLFW::getTimerValue() const { return glfwGetTimerValue(); }

std::uint64_t GLFW::getTimerFrequency() const { return glfwGetTimerFrequency(); }

decltype(&glfwGetProcAddress) GLFW::getLoaderFnc() const { return glfwGetProcAddress; }

void GLFW::setSwapInterval(std::size_t interval) { glfwSwapInterval(static_cast<int>(interval)); }

}  // namespace pf::glfw
