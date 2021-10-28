//
// Created by xflajs00 on 27.10.2021.
//

#include "Window.h"
#include "Exception.h"
#include <span>
#include <stdexcept>

namespace pf::glfw {

Window::Window(WindowConfig config) {
  GLFWmonitor *monitor = nullptr;
  if (config.monitor.has_value()) {
    monitor = config.monitor->getHandle();
  }
#ifdef PF_GLFW_OPENGL
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.majorOpenGLVersion);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.minorOpenGLVersion);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
  config.hints.apply();
  windowHandle = glfwCreateWindow(config.width, config.height, config.title.c_str(), monitor, nullptr);
  if (windowHandle == nullptr) {
    details::getLastErrorAndThrow();
  }
  glfwSetWindowUserPointer(windowHandle, this);
}

Window::Window(Window &&other) noexcept : windowHandle(other.windowHandle) {
  other.windowHandle = nullptr;
}

Window &Window::operator=(Window &&other) noexcept {
  windowHandle = other.windowHandle;
  other.windowHandle = nullptr;
  return *this;
}

Window::~Window() {
  if (windowHandle != nullptr) {
    glfwDestroyWindow(windowHandle);
  }
}

bool Window::shouldClose() const {
  return glfwWindowShouldClose(windowHandle);
}

void Window::close() {
  glfwSetWindowShouldClose(windowHandle, GLFW_TRUE);
}

ButtonState Window::getLastKeyState(Key key) const {
  const auto keyState = glfwGetKey(windowHandle, static_cast<int>(key));
  return keyState == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
}

ButtonState Window::getLastMouseButtonState(MouseButton button) const {
  const auto buttonState = glfwGetMouseButton(windowHandle, static_cast<int>(button));
  return buttonState == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
}

Position<double> Window::getCursorPosition() const {
  Position<double> result;
  glfwGetCursorPos(windowHandle, &result.x, &result.y);
  return result;
}

void Window::setCursorPosition(Position<double> cursorPosition) {
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

Position<int> Window::getPosition() const {
  Position<int> result;
  glfwGetWindowPos(windowHandle, &result.x, &result.y);
  return result;
}

void Window::setPosition(Position<int> position) {
  glfwSetWindowPos(windowHandle, position.x, position.y);
}

Size<int> Window::getSize() const {
  Size<int> result;
  glfwGetWindowSize(windowHandle, &result.width, &result.height);
  return result;
}

void Window::setSize(Size<int> size) {
  glfwSetWindowSize(windowHandle, size.width, size.height);
}

Box<int> Window::getFrameSize() const {
  Box<int> result;
  glfwGetWindowFrameSize(windowHandle, &result.leftTop.x, &result.leftTop.y, &result.rightBottom.x, &result.rightBottom.y);
  return result;
}

Size<int> Window::getFramebufferSize() const {
  Size<int> result;
  glfwGetFramebufferSize(windowHandle, &result.width, &result.height);
  return result;
}

Scale Window::getContentScale() const {
  Scale result;
  glfwGetWindowContentScale(windowHandle, &result.x, &result.y);
  return result;
}

void Window::setSizeLimits(Size<int> minSize, Size<int> maxSize) {
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

void Window::iconify() {
  glfwIconifyWindow(windowHandle);
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

Monitor Window::getMonitor() const {
  return Monitor{glfwGetWindowMonitor(windowHandle)};
}

void Window::setMonitor(Monitor &monitor, Position<int> windowPosition, Size<int> windowSize, int refreshRate) {
  glfwSetWindowMonitor(windowHandle, monitor.getHandle(), windowPosition.x, windowPosition.y, windowSize.width, windowSize.height, refreshRate);
}

bool Window::isDecorated() const {
  return glfwGetWindowAttrib(windowHandle, GLFW_DECORATED) == GLFW_TRUE;
}

bool Window::isResizable() const {
  return glfwGetWindowAttrib(windowHandle, GLFW_RESIZABLE) == GLFW_TRUE;
}

bool Window::isFloating() const {
  return glfwGetWindowAttrib(windowHandle, GLFW_FLOATING) == GLFW_TRUE;
}

bool Window::isAutoIconify() const {
  return glfwGetWindowAttrib(windowHandle, GLFW_AUTO_ICONIFY) == GLFW_TRUE;
}

bool Window::isFocusOnShow() const {
  return glfwGetWindowAttrib(windowHandle, GLFW_FOCUS_ON_SHOW) == GLFW_TRUE;
}

void Window::setDecorated(bool decorated) {
  glfwSetWindowAttrib(windowHandle, GLFW_DECORATED, decorated ? GLFW_TRUE : GLFW_FALSE);
}

void Window::setResizable(bool resizable) {
  glfwSetWindowAttrib(windowHandle, GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
}

void Window::setFloating(bool floating) {
  glfwSetWindowAttrib(windowHandle, GLFW_FLOATING, floating ? GLFW_TRUE : GLFW_FALSE);
}

void Window::setAutoIconify(bool autoIconify) {
  glfwSetWindowAttrib(windowHandle, GLFW_AUTO_ICONIFY, autoIconify ? GLFW_TRUE : GLFW_FALSE);
}

void Window::setFocusOnShow(bool focusOnShow) {
  glfwSetWindowAttrib(windowHandle, GLFW_FOCUS_ON_SHOW, focusOnShow ? GLFW_TRUE : GLFW_FALSE);
}

GLFWwindow *Window::getHandle() {
  return windowHandle;
}

const GLFWwindow *Window::getHandle() const {
  return windowHandle;
}

ButtonState Window::getMouseButtonState(MouseButton button) const {
  return mouseButtonStates[static_cast<int>(button)];
}

CursorBehavior Window::getCursorBehavior() const {
  return static_cast<CursorBehavior>(glfwGetInputMode(windowHandle, GLFW_CURSOR));
}

bool Window::isStickyKeys() const {
  return glfwGetInputMode(windowHandle, GLFW_STICKY_KEYS) == GLFW_TRUE;
}

bool Window::isStickyMouseButtons() const {
  return glfwGetInputMode(windowHandle, GLFW_STICKY_MOUSE_BUTTONS) == GLFW_TRUE;
}

bool Window::isLockModifierKeys() const {
  return glfwGetInputMode(windowHandle, GLFW_LOCK_KEY_MODS) == GLFW_TRUE;
}

bool Window::isRawMouseMotionSupported() const {
  return glfwRawMouseMotionSupported();
}

bool Window::isRawMouseMotionEnabled() const {
  return glfwGetInputMode(windowHandle, GLFW_RAW_MOUSE_MOTION) == GLFW_TRUE;
}

void Window::setCursorBehavior(CursorBehavior behavior) {
  glfwSetInputMode(windowHandle, GLFW_CURSOR, static_cast<int>(behavior));
  details::getLastErrorAndThrow();
}

void Window::setStickyKeys(bool sticky) {
  glfwSetInputMode(windowHandle, GLFW_STICKY_KEYS, sticky ? GLFW_TRUE : GLFW_FALSE);
  details::getLastErrorAndThrow();
}

void Window::setStickyMouseButtons(bool sticky) {
  glfwSetInputMode(windowHandle, GLFW_STICKY_MOUSE_BUTTONS, sticky ? GLFW_TRUE : GLFW_FALSE);
  details::getLastErrorAndThrow();
}

void Window::setLockModifierKeys(bool lock) {
  glfwSetInputMode(windowHandle, GLFW_LOCK_KEY_MODS, lock ? GLFW_TRUE : GLFW_FALSE);
  details::getLastErrorAndThrow();
}

void Window::setRawMouseMotionEnabled(bool enabled) {
  glfwSetInputMode(windowHandle, GLFW_RAW_MOUSE_MOTION, enabled ? GLFW_TRUE : GLFW_FALSE);
  details::getLastErrorAndThrow();
}

void Window::setCurrent() {
  glfwMakeContextCurrent(windowHandle);
}

void Window::charGLFWCallback(GLFWwindow *window, unsigned int codepoint) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->inputIgnorePredicate()) {
    return;
  }
  self->charCallback(codepoint);
}

void Window::mouseButtonGLFWCallback(GLFWwindow *window, int button, int action, int mods) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->inputIgnorePredicate()) {
    return;
  }
  const auto mbAction = static_cast<MouseButtonAction>(action);
  const auto mouseButton = static_cast<MouseButton>(button);
  const auto modFlags = Flags<ModifierKey>{static_cast<ModifierKey>(mods)};
  if (mbAction == MouseButtonAction::Release && self->mouseButtonStates[button] == ButtonState::Down) {
    self->mouseClickCallback(mouseButton, modFlags);
  }
  self->mouseButtonCallback(mouseButton, mbAction, modFlags);
  self->mouseButtonStates[button] = mbAction == MouseButtonAction::Press ? ButtonState::Down : ButtonState::Up;
}

void Window::cursorPositionGLFWCallback(GLFWwindow *window, double xpos, double ypos) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->inputIgnorePredicate()) {
    return;
  }
  self->cursorPositionCallback({xpos, ypos});
}

void Window::cursorEnterGLFWCallback(GLFWwindow *window, int entered) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->inputIgnorePredicate()) {
    return;
  }
  self->cursorEnterCallback(static_cast<CursorEntered>(entered));
}

void Window::scrollGLFWCallback(GLFWwindow *window, double xoffset, double yoffset) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->inputIgnorePredicate()) {
    return;
  }
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

void Window::contentScaleGLFWCallback(GLFWwindow *window, float xscale, float yscale) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->contentScaleCallback({xscale, yscale});
}

void Window::positionGLFWCallback(GLFWwindow *window, int xpos, int ypos) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->positionCallback({xpos, ypos});
}

void Window::sizeGLFWCallback(GLFWwindow *window, int xpos, int ypos) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->sizeCallback({xpos, ypos});
}

void Window::closeGLFWCallback(GLFWwindow *window) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->closeCallback();
}

void Window::refreshGLFWCallback(GLFWwindow *window) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->refreshCallback();
}

void Window::focusGLFWCallback(GLFWwindow *window, int focused) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->focusCallback(focused == GLFW_TRUE);
}

void Window::iconifyGLFWCallback(GLFWwindow *window, int iconified) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->iconifyCallback(iconified == GLFW_TRUE);
}

void Window::maximizeGLFWCallback(GLFWwindow *window, int maximized) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->maximizeCallback(maximized == GLFW_TRUE);
}

void Window::framebufferSizeGLFWCallback(GLFWwindow *window, int width, int height) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->framebufferSizeCallback({width, height});
}

void Window::setTitle(const std::string &title) {
  glfwSetWindowTitle(windowHandle, title.c_str());
}

void Window::swapBuffers() {
  glfwSwapBuffers(windowHandle);
}

}// namespace pf::glfw