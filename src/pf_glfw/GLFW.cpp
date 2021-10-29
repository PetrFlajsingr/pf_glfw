//
// Created by xflajs00 on 28.10.2021.
//

#include "GLFW.h"
#include <pf_glfw/Window.h>

namespace pf::glfw {

GLFW::GLFW() {
  if (glfwInit() != GLFW_TRUE) {
    details::getLastErrorAndThrow();
  }
}

GLFW::~GLFW() {
  glfwTerminate();
}

Version GLFW::GetVersion() {
  Version result;
  glfwGetVersion(&result.major, &result.minor, &result.revision);
  return result;
}

const std::shared_ptr<Window> &GLFW::createWindow(const pf::glfw::WindowConfig &config) {
  auto window = std::shared_ptr<Window>(new Window{config});
  return windows.emplace_back(window);
}

void GLFW::removeWindow(const std::shared_ptr<Window> &window) {
  std::erase(windows, window);
}

void GLFW::setCurrentWindow(const std::shared_ptr<Window> &window) {
  glfwMakeContextCurrent(window->getHandle());
}
#ifdef PF_GLFW_OPENGL
bool GLFW::isExtensionSupported(const std::string &extension) const {
  return glfwExtensionSupported(extension.c_str()) == GLFW_TRUE;
}
#endif
#ifdef PF_GLFW_VULKAN
std::vector<std::string> GLFW::getRequiredExtensions() const {
  std::uint32_t count;
  const auto extensions = glfwGetRequiredInstanceExtensions(&count);
  const auto extSpan = std::span{extensions, count};
  return std::vector<std::string>{extSpan.begin(), extSpan.end()};
}
#endif

void GLFW::pollEvents() {
  glfwPollEvents();
}

void GLFW::waitEvents() {
  glfwWaitEvents();
}

void GLFW::waitEvents(std::chrono::milliseconds timeout) {
  glfwWaitEventsTimeout(timeout.count() / 1000.0);
}

double GLFW::getTime() const {
  return glfwGetTime();
}

void GLFW::setTime(double time) {
  glfwSetTime(time);
}

std::uint64_t GLFW::getTimerValue() const {
  return glfwGetTimerValue();
}

std::uint64_t GLFW::getTimerFrequency() const {
  return glfwGetTimerFrequency();
}

#ifdef PF_GLFW_OPENGL
decltype(&glfwGetProcAddress) GLFW::getLoaderFnc() const {
  return glfwGetProcAddress;
}
#endif
}// namespace pf::glfw