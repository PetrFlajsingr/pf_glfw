//
// Created by xflajs00 on 27.10.2021.
//

#include "Window.h"
#include "Exception.h"
#include <span>
#include <stdexcept>

namespace pf::glfw {

Window::Window(WindowOpenGlConfig config) {
  GLFWmonitor *monitor = nullptr;
  if (config.monitor.has_value()) { monitor = config.monitor->getHandle(); }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.majorOpenGLVersion);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.minorOpenGLVersion);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, static_cast<int>(config.clientApi));

  config.hints.apply(true);
  windowHandle = glfwCreateWindow(static_cast<int>(config.width), static_cast<int>(config.height), config.title.c_str(),
                                  monitor, nullptr);
  if (windowHandle == nullptr) { details::getLastErrorAndThrow(); }
  glfwSetWindowUserPointer(windowHandle, this);
}

Window::Window(WindowNoApiConfig config) {
  GLFWmonitor *monitor = nullptr;
  if (config.monitor.has_value()) { monitor = config.monitor->getHandle(); }

  config.hints.apply(false);
  windowHandle = glfwCreateWindow(static_cast<int>(config.width), static_cast<int>(config.height), config.title.c_str(),
                                  monitor, nullptr);
  if (windowHandle == nullptr) { details::getLastErrorAndThrow(); }
  glfwSetWindowUserPointer(windowHandle, this);
}

Window::Window(Window &&other) noexcept : windowHandle(other.windowHandle) { other.windowHandle = nullptr; }

Window &Window::operator=(Window &&other) noexcept {
  windowHandle = other.windowHandle;
  other.windowHandle = nullptr;
  return *this;
}

Window::~Window() {
  if (windowHandle != nullptr) { glfwDestroyWindow(windowHandle); }
}

bool Window::shouldClose() const { return glfwWindowShouldClose(windowHandle); }

void Window::close() { glfwSetWindowShouldClose(windowHandle, GLFW_TRUE); }

ButtonState Window::getLastKeyState(Key key) const {
  const auto keyState = glfwGetKey(windowHandle, static_cast<int>(key));
  return keyState == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
}

ButtonState Window::getLastMouseButtonState(MouseButton button) const {
  const auto buttonState = glfwGetMouseButton(windowHandle, static_cast<int>(button));
  return buttonState == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
}

Position<double> Window::getCursorPosition() const {
  Position<double> result{};
  glfwGetCursorPos(windowHandle, &result.x, &result.y);
  return result;
}

void Window::setCursorPosition(Position<double> cursorPosition) {
  glfwSetCursorPos(windowHandle, cursorPosition.x, cursorPosition.y);
}

std::optional<std::string> Window::getClipboardContents() const {
  if (auto clipboard = glfwGetClipboardString(windowHandle); clipboard != nullptr) {
    return std::string{glfwGetClipboardString(windowHandle)};
  }
  return std::nullopt;
}

void Window::setClipboardContents(const std::string &contents) {
  glfwSetClipboardString(windowHandle, contents.c_str());
}

void Window::setCursor(Cursor &cursor) { glfwSetCursor(windowHandle, cursor.getHandle()); }

void Window::setIcon(const std::vector<Image> &icons) {
  std::vector<const GLFWimage *> imagePtrs{};
  std::ranges::transform(icons, std::back_inserter(imagePtrs), [](auto &img) { return img.getHandle(); });
  glfwSetWindowIcon(windowHandle, static_cast<int>(imagePtrs.size()), *imagePtrs.data());
}

Position<int> Window::getPosition() const {
  Position<int> result{};
  glfwGetWindowPos(windowHandle, &result.x, &result.y);
  return result;
}

void Window::setPosition(Position<int> position) { glfwSetWindowPos(windowHandle, position.x, position.y); }

Size<int> Window::getSize() const {
  Size<int> result{};
  glfwGetWindowSize(windowHandle, &result.width, &result.height);
  return result;
}

void Window::setSize(Size<int> size) { glfwSetWindowSize(windowHandle, size.width, size.height); }

Box<int> Window::getFrameSize() const {
  Box<int> result{};
  glfwGetWindowFrameSize(windowHandle, &result.leftTop.x, &result.leftTop.y, &result.rightBottom.x,
                         &result.rightBottom.y);
  return result;
}

Size<int> Window::getFramebufferSize() const {
  Size<int> result{};
  glfwGetFramebufferSize(windowHandle, &result.width, &result.height);
  return result;
}

Scale Window::getContentScale() const {
  Scale result{};
  glfwGetWindowContentScale(windowHandle, &result.x, &result.y);
  return result;
}

void Window::setSizeLimits(Size<int> minSize, Size<int> maxSize) {
  assert(minSize.width >= 0 && minSize.height >= 0);
  assert(maxSize.width >= minSize.width && maxSize.height >= minSize.height);
  glfwSetWindowSizeLimits(windowHandle, minSize.width, minSize.height, maxSize.width, maxSize.height);
}

void Window::setAspectRatio(int numer, int denom) { glfwSetWindowAspectRatio(windowHandle, numer, denom); }

float Window::getOpacity() const { return glfwGetWindowOpacity(windowHandle); }

void Window::setOpacity(float opacity) { glfwSetWindowOpacity(windowHandle, opacity); }

void Window::restore() { glfwRestoreWindow(windowHandle); }

void Window::maximize() { glfwMaximizeWindow(windowHandle); }

void Window::hide() { glfwHideWindow(windowHandle); }

void Window::show() { glfwShowWindow(windowHandle); }

void Window::iconify() { glfwIconifyWindow(windowHandle); }

bool Window::isVisible() const { return glfwGetWindowAttrib(windowHandle, GLFW_VISIBLE) == GLFW_TRUE; }

bool Window::isMaximized() const { return glfwGetWindowAttrib(windowHandle, GLFW_MAXIMIZED) == GLFW_TRUE; }

void Window::setFocus() { glfwFocusWindow(windowHandle); }

void Window::requestAttention() { glfwRequestWindowAttention(windowHandle); }

std::optional<Monitor> Window::getFullscreenMonitor() const {
  const auto monitorPtr = glfwGetWindowMonitor(windowHandle);
  if (monitorPtr == nullptr) { return std::nullopt; }
  return Monitor{monitorPtr};
}

void Window::setMonitor(Monitor &monitor, Position<int> windowPosition, Size<int> windowSize, int refreshRate) {
  // TODO: change this, use it to implement fullscreen etc.
  glfwSetWindowMonitor(windowHandle, monitor.getHandle(), windowPosition.x, windowPosition.y, windowSize.width,
                       windowSize.height, refreshRate);
}

bool Window::isDecorated() const { return glfwGetWindowAttrib(windowHandle, GLFW_DECORATED) == GLFW_TRUE; }

bool Window::isResizable() const { return glfwGetWindowAttrib(windowHandle, GLFW_RESIZABLE) == GLFW_TRUE; }

bool Window::isFloating() const { return glfwGetWindowAttrib(windowHandle, GLFW_FLOATING) == GLFW_TRUE; }

bool Window::isAutoIconify() const { return glfwGetWindowAttrib(windowHandle, GLFW_AUTO_ICONIFY) == GLFW_TRUE; }

bool Window::isFocusOnShow() const { return glfwGetWindowAttrib(windowHandle, GLFW_FOCUS_ON_SHOW) == GLFW_TRUE; }

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

GLFWwindow *Window::getHandle() { return windowHandle; }

const GLFWwindow *Window::getHandle() const { return windowHandle; }

CursorBehavior Window::getCursorBehavior() const {
  return static_cast<CursorBehavior>(glfwGetInputMode(windowHandle, GLFW_CURSOR));
}

bool Window::isStickyKeys() const { return glfwGetInputMode(windowHandle, GLFW_STICKY_KEYS) == GLFW_TRUE; }

bool Window::isStickyMouseButtons() const {
  return glfwGetInputMode(windowHandle, GLFW_STICKY_MOUSE_BUTTONS) == GLFW_TRUE;
}

bool Window::isLockModifierKeys() const { return glfwGetInputMode(windowHandle, GLFW_LOCK_KEY_MODS) == GLFW_TRUE; }

bool Window::isRawMouseMotionSupported() const { return glfwRawMouseMotionSupported(); }

bool Window::isRawMouseMotionEnabled() const {
  return glfwGetInputMode(windowHandle, GLFW_RAW_MOUSE_MOTION) == GLFW_TRUE;
}

void Window::setCursorBehavior(CursorBehavior behavior) {
  glfwSetInputMode(windowHandle, GLFW_CURSOR, static_cast<int>(behavior));
}

void Window::setStickyKeys(bool sticky) {
  glfwSetInputMode(windowHandle, GLFW_STICKY_KEYS, sticky ? GLFW_TRUE : GLFW_FALSE);
}

void Window::setStickyMouseButtons(bool sticky) {
  glfwSetInputMode(windowHandle, GLFW_STICKY_MOUSE_BUTTONS, sticky ? GLFW_TRUE : GLFW_FALSE);
}

void Window::setLockModifierKeys(bool lock) {
  glfwSetInputMode(windowHandle, GLFW_LOCK_KEY_MODS, lock ? GLFW_TRUE : GLFW_FALSE);
}

void Window::setRawMouseMotionEnabled(bool enabled) {
  glfwSetInputMode(windowHandle, GLFW_RAW_MOUSE_MOTION, enabled ? GLFW_TRUE : GLFW_FALSE);
}

void Window::setCurrent() { glfwMakeContextCurrent(windowHandle); }  // TODO: is this OpenGL only?

void Window::keyGLFWCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWkeyfun != nullptr) {
    self->previousCallbacks.glfWkeyfun(window, key, scancode, action, mods);
  }
  self->keyCallback(static_cast<Key>(key), static_cast<KeyAction>(action),
                    Flags<ModifierKey>{static_cast<ModifierKey>(mods)});
}

void Window::charGLFWCallback(GLFWwindow *window, unsigned int codepoint) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWcharfun != nullptr) { self->previousCallbacks.glfWcharfun(window, codepoint); }
  self->charCallback(codepoint);
}

void Window::mouseButtonGLFWCallback(GLFWwindow *window, int button, int action, int mods) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWmousebuttonfun != nullptr) {
    self->previousCallbacks.glfWmousebuttonfun(window, button, action, mods);
  }
  const auto state = static_cast<ButtonState>(action);
  const auto mouseButton = static_cast<MouseButton>(button);
  const auto modFlags = Flags<ModifierKey>{static_cast<ModifierKey>(mods)};
  self->mouseButtonCallback(mouseButton, state, modFlags);
}

void Window::cursorPositionGLFWCallback(GLFWwindow *window, double xpos, double ypos) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWcursorposfun != nullptr) {
    self->previousCallbacks.glfWcursorposfun(window, xpos, ypos);
  }
  self->cursorPositionCallback({xpos, ypos});
}

void Window::cursorEnterGLFWCallback(GLFWwindow *window, int entered) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWcursorenterfun != nullptr) {
    self->previousCallbacks.glfWcursorenterfun(window, entered);
  }
  self->cursorEnterCallback(static_cast<CursorEntered>(entered));
}

void Window::scrollGLFWCallback(GLFWwindow *window, double xoffset, double yoffset) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWscrollfun != nullptr) {
    self->previousCallbacks.glfWscrollfun(window, xoffset, yoffset);
  }
  self->scrollCallback(xoffset, yoffset);
}

void Window::dropGLFWCallback(GLFWwindow *window, int pathCount, const char *paths[]) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWdropfun != nullptr) { self->previousCallbacks.glfWdropfun(window, pathCount, paths); }
  std::vector<std::filesystem::path> fsPaths;
  fsPaths.reserve(pathCount);
  std::ranges::transform(std::span{paths, static_cast<std::size_t>(pathCount)}, std::back_inserter(fsPaths),
                         [](const auto path) { return std::filesystem::path{path}; });
  self->dropCallback(fsPaths);
}

void Window::contentScaleGLFWCallback(GLFWwindow *window, float xscale, float yscale) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWwindowcontentscalefun != nullptr) {
    self->previousCallbacks.glfWwindowcontentscalefun(window, xscale, yscale);
  }
  self->contentScaleCallback({xscale, yscale});
}

void Window::positionGLFWCallback(GLFWwindow *window, int xpos, int ypos) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWwindowposfun != nullptr) {
    self->previousCallbacks.glfWwindowposfun(window, xpos, ypos);
  }
  self->positionCallback({xpos, ypos});
}

void Window::sizeGLFWCallback(GLFWwindow *window, int width, int height) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWwindowsizefun != nullptr) {
    self->previousCallbacks.glfWwindowsizefun(window, width, height);
  }
  self->sizeCallback({width, height});
}

void Window::closeGLFWCallback(GLFWwindow *window) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWwindowclosefun != nullptr) { self->previousCallbacks.glfWwindowclosefun(window); }
  self->closeCallback();
}

void Window::refreshGLFWCallback(GLFWwindow *window) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWwindowrefreshfun != nullptr) { self->previousCallbacks.glfWwindowrefreshfun(window); }
  self->refreshCallback();
}

void Window::focusGLFWCallback(GLFWwindow *window, int focused) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWwindowfocusfun != nullptr) {
    self->previousCallbacks.glfWwindowfocusfun(window, focused);
  }
  self->focusCallback(focused == GLFW_TRUE);
}

void Window::iconifyGLFWCallback(GLFWwindow *window, int iconified) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWwindowiconifyfun != nullptr) {
    self->previousCallbacks.glfWwindowiconifyfun(window, iconified);
  }
  self->iconifyCallback(iconified == GLFW_TRUE);
}

void Window::maximizeGLFWCallback(GLFWwindow *window, int maximized) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWwindowmaximizefun != nullptr) {
    self->previousCallbacks.glfWwindowmaximizefun(window, maximized);
  }
  self->maximizeCallback(maximized == GLFW_TRUE);
}

void Window::framebufferSizeGLFWCallback(GLFWwindow *window, int width, int height) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (self->previousCallbacks.glfWframebuffersizefun != nullptr) {
    self->previousCallbacks.glfWframebuffersizefun(window, width, height);
  }
  self->framebufferSizeCallback({width, height});
}

void Window::setTitle(const std::string &title) { glfwSetWindowTitle(windowHandle, title.c_str()); }

void Window::swapBuffers() { glfwSwapBuffers(windowHandle); }

}  // namespace pf::glfw
