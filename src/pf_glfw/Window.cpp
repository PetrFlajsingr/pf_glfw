//
// Created by xflajs00 on 27.10.2021.
//

#include "Window.h"
#include <span>
#include <stdexcept>

namespace pf::glfw {

Window::Window(WindowConfig config) {
  GLFWmonitor *monitor = nullptr;
  if (config.monitor.has_value()) {
    monitor = config.monitor->getHandle();
  }
  windowHandle = glfwCreateWindow(config.width, config.height, config.title.c_str(), monitor, nullptr);
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
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->keyCallback(static_cast<Key>(key), static_cast<KeyAction>(action), Flags<ModifierKey>{static_cast<ModifierKey>(mods)});
}

std::string Window::getClipboardContents() const {
  return std::string{glfwGetClipboardString(windowHandle)};
}
void Window::setClipboardContents(const std::string &contents) {
  glfwSetClipboardString(windowHandle, contents.c_str());
}

void Window::setCursor(Cursor &cursor) {
  glfwSetCursor(windowHandle, cursor.getHandle());
}

void Window::setIcon(const std::vector<Image> &icons) {
  std::vector<const GLFWimage *> imagePtrs;
  std::ranges::transform(icons, std::back_inserter(imagePtrs), [](auto &img) {
    return img.getHandle();
  });
  glfwSetWindowIcon(windowHandle, imagePtrs.size(), *imagePtrs.data());
}

WindowPosition Window::getPosition() const {
  WindowPosition result;
  glfwGetWindowPos(windowHandle, &result.x, &result.y);
  return result;
}

void Window::setPosition(WindowPosition position) {
  glfwSetWindowPos(windowHandle, position.x, position.y);
}

WindowSize Window::getSize() const {
  WindowSize result;
  glfwGetWindowSize(windowHandle, &result.width, &result.height);
  return result;
}

void Window::setSize(WindowSize size) {
  glfwSetWindowSize(windowHandle, size.width, size.height);
}

void Window::setSizeLimits(WindowSize minSize, WindowSize maxSize) {
  glfwSetWindowSizeLimits(windowHandle, minSize.width, minSize.height, maxSize.width, maxSize.height);
}

void Window::setAspectRatio(int numer, int denom) {
  glfwSetWindowAspectRatio(windowHandle, numer, denom);
}

float Window::getOpacity() const {
  return glfwGetWindowOpacity(windowHandle);
}

void Window::setOpacity(float opacity) {
  glfwSetWindowOpacity(windowHandle, opacity);
}

void Window::restore() {
  glfwRestoreWindow(windowHandle);
}

void Window::maximize() {
  glfwMaximizeWindow(windowHandle);
}

void Window::hide() {
  glfwHideWindow(windowHandle);
}

void Window::show() {
  glfwShowWindow(windowHandle);
}

bool Window::isVisible() const {
  return glfwGetWindowAttrib(windowHandle, GLFW_VISIBLE) == GLFW_TRUE;
}

void Window::setFocus() {
  glfwFocusWindow(windowHandle);
}

void Window::requestAttention() {
  glfwRequestWindowAttention(windowHandle);
}

GLFWwindow *Window::getHandle() {
  return windowHandle;
}

const GLFWwindow *Window::getHandle() const {
  return windowHandle;
}

void Window::charGLFWCallback(GLFWwindow *window, unsigned int codepoint) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->charCallback(codepoint);
}

void Window::mouseButtonGLFWCallback(GLFWwindow *window, int button, int action, int mods) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->mouseButtonCallback(static_cast<MouseButton>(button), static_cast<MouseButtonAction>(action), Flags<ModifierKey>{static_cast<ModifierKey>(mods)});
}

void Window::cursorPositionGLFWCallback(GLFWwindow *window, double xpos, double ypos) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->cursorPositionCallback({xpos, ypos});
}

void Window::cursorEnterGLFWCallback(GLFWwindow *window, int entered) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->cursorEnterCallback(static_cast<CursorEntered>(entered));
}

void Window::scrollGLFWCallback(GLFWwindow *window, double xoffset, double yoffset) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->scrollCallback(xoffset, yoffset);
}

void Window::dropGLFWCallback(GLFWwindow *window, int pathCount, const char *paths[]) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  std::vector<std::filesystem::path> fsPaths;
  fsPaths.reserve(pathCount);
  std::ranges::transform(std::span{paths, static_cast<std::size_t>(pathCount)}, std::back_inserter(fsPaths), [](const auto path) {
    return std::filesystem::path{path};
  });
  self->dropCallback(fsPaths);
}
void Window::setTitle(const std::string &title) {
  glfwSetWindowTitle(windowHandle, title.c_str());
}

}// namespace pf::glfw