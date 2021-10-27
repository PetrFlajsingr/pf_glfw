//
// Created by xflajs00 on 27.10.2021.
//

#include "Window.h"
#include <stdexcept>
#include <span>
namespace pf::glfw {

Window::Window(const WindowConfig& config) {
  windowHandle = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);
  if (windowHandle == nullptr) {
    throw std::runtime_error("Could not initialize GLFW window");
  }
  glfwSetWindowUserPointer(windowHandle, this);
}

Window::~Window() {
  glfwDestroyWindow(windowHandle);
}

bool Window::shouldClose() const {
  return glfwWindowShouldClose(windowHandle);
}

void Window::close() {
  glfwSetWindowShouldClose(windowHandle, GLFW_TRUE);
}

KeyAction Window::getLastKeyState(Key key) const {
  return static_cast<KeyAction>(glfwGetKey(windowHandle, static_cast<int>(key)));
}

MouseButtonAction Window::getLastMouseButtonState(MouseButton button) const {
  return static_cast<MouseButtonAction>(glfwGetMouseButton(windowHandle, static_cast<int>(button)));
}

CursorPosition Window::getCursorPosition() const {
  CursorPosition result;
  glfwGetCursorPos(windowHandle, &result.x, &result.y);
  return result;
}

void Window::setCursorPosition(CursorPosition cursorPosition) {
  glfwSetCursorPos(windowHandle, cursorPosition.x, cursorPosition.y);
}

void Window::keyGLFWCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  auto self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  self->keyCallback(static_cast<Key>(key), static_cast<KeyAction>(action), Flags<ModifierKey>{static_cast<ModifierKey>(mods)});
}

std::string Window::getClipboardContents() const {
  return std::string{ glfwGetClipboardString(windowHandle)};
}
void Window::setClipboardContents(const std::string &contents) {
  glfwSetClipboardString(windowHandle, contents.c_str());
}

void Window::charGLFWCallback(GLFWwindow *window, unsigned int codepoint) {
  auto self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  self->charCallback(codepoint);
}

void Window::mouseButtonGLFWCallback(GLFWwindow *window, int button, int action, int mods) {
  auto self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  self->mouseButtonCallback(static_cast<MouseButton>(button), static_cast<MouseButtonAction>(action), Flags<ModifierKey>{static_cast<ModifierKey>(mods)});
}

void Window::cursorPositionGLFWCallback(GLFWwindow *window, double xpos, double ypos) {
  auto self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  self->cursorPositionCallback({xpos, ypos});
}

void Window::cursorEnterGLFWCallback(GLFWwindow *window, int entered) {
  auto self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  self->cursorEnterCallback(static_cast<CursorEntered>(entered));
}

void Window::scrollGLFWCallback(GLFWwindow *window, double xoffset, double yoffset) {
  auto self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  self->scrollCallback(xoffset, yoffset);
}

void Window::dropGLFWCallback(GLFWwindow *window, int pathCount, const char *paths[]) {
  auto self = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  std::vector<std::filesystem::path> fsPaths;
  fsPaths.reserve(pathCount);
  std::ranges::transform(std::span{paths, static_cast<std::size_t>(pathCount)}, std::back_inserter(fsPaths), [] (const auto path) {
    return std::filesystem::path{path};
  });
  self->dropCallback(fsPaths);
}
}