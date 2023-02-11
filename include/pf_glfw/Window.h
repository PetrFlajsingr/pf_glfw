//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_WINDOW_H
#define PF_GLFW_WINDOW_H

#include <GLFW/glfw3.h>
#include <filesystem>
#include <functional>
#include <optional>
#include <pf_common/enums.h>
#include <pf_glfw/Cursor.h>
#include <pf_glfw/Image.h>
#include <pf_glfw/Monitor.h>
#include <pf_glfw/WindowHints.h>
#include <pf_glfw/concepts.h>
#include <pf_glfw/enums/ButtonState.h>
#include <pf_glfw/enums/ClientAPI.h>
#include <pf_glfw/enums/CursorBehavior.h>
#include <pf_glfw/enums/CursorEntered.h>
#include <pf_glfw/enums/Key.h>
#include <pf_glfw/enums/KeyAction.h>
#include <pf_glfw/enums/ModifierKey.h>
#include <pf_glfw/enums/MouseButton.h>
#include <pf_glfw/fwd.h>
#include <string>
#include <utility>
#include <vector>

namespace pf::glfw {

struct WindowOpenGlConfig {  //-V730
  std::size_t width;
  std::size_t height;
  std::string title;
  std::optional<Monitor> monitor = std::nullopt;
  ClientAPI clientApi = ClientAPI::OpenGL;
  int majorOpenGLVersion;
  int minorOpenGLVersion;
  WindowHints hints{};
};

struct WindowNoApiConfig {  //-V730
  std::size_t width;
  std::size_t height;
  std::string title;
  std::optional<Monitor> monitor = std::nullopt;

  WindowHints hints{};
};

// TODO: return value checks
// TODO: context sharing
class Window {
  friend class GLFW;

 public:
  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;
  Window(Window &&other) noexcept : windowHandle(other.windowHandle) { other.windowHandle = nullptr; }
  Window &operator=(Window &&other) noexcept {
    windowHandle = other.windowHandle;
    other.windowHandle = nullptr;
    return *this;
  }
  ~Window() {
    if (windowHandle != nullptr) { glfwDestroyWindow(windowHandle); }
  }

  [[nodiscard]] bool shouldClose() const { return glfwWindowShouldClose(windowHandle); }
  void requestClose() { glfwSetWindowShouldClose(windowHandle, GLFW_TRUE); }

  [[nodiscard]] ButtonState getLastKeyState(Key key) const {
    const auto keyState = glfwGetKey(windowHandle, static_cast<int>(key));
    return keyState == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  }
  [[nodiscard]] ButtonState getLastMouseButtonState(MouseButton button) const {
    const auto buttonState = glfwGetMouseButton(windowHandle, static_cast<int>(button));
    return buttonState == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  }

  [[nodiscard]] Position<double> getCursorPosition() const {
    Position<double> result{};
    glfwGetCursorPos(windowHandle, &result.x, &result.y);
    return result;
  }
  void setCursorPosition(Position<double> cursorPosition) { glfwSetCursorPos(windowHandle, cursorPosition.x, cursorPosition.y); }

  [[nodiscard]] std::optional<std::string> getClipboardContents() const {
    if (auto clipboard = glfwGetClipboardString(windowHandle); clipboard != nullptr) {
      return std::string{glfwGetClipboardString(windowHandle)};
    }
    return std::nullopt;
  }
  void setClipboardContents(const std::string &contents) { glfwSetClipboardString(windowHandle, contents.c_str()); }

  void setCursor(Cursor &cursor) { glfwSetCursor(windowHandle, cursor.getHandle()); }

  void setTitle(const std::string &title) { glfwSetWindowTitle(windowHandle, title.c_str()); }

  void setIcon(const std::vector<Image> &icons) {
    std::vector<const GLFWimage *> imagePtrs{};
    std::ranges::transform(icons, std::back_inserter(imagePtrs), [](auto &img) { return img.getHandle(); });
    glfwSetWindowIcon(windowHandle, static_cast<int>(imagePtrs.size()), *imagePtrs.data());
  }

  [[nodiscard]] Position<int> getPosition() const {
    Position<int> result{};
    glfwGetWindowPos(windowHandle, &result.x, &result.y);
    return result;
  }
  void setPosition(Position<int> position) { glfwSetWindowPos(windowHandle, position.x, position.y); }

  [[nodiscard]] Size<int> getSize() const {
    Size<int> result{};
    glfwGetWindowSize(windowHandle, &result.width, &result.height);
    return result;
  }
  void setSize(Size<int> size) { glfwSetWindowSize(windowHandle, size.width, size.height); }

  [[nodiscard]] Box<int> getFrameSize() const {
    Box<int> result{};
    glfwGetWindowFrameSize(windowHandle, &result.leftTop.x, &result.leftTop.y, &result.rightBottom.x, &result.rightBottom.y);
    return result;
  }

  [[nodiscard]] Size<int> getFramebufferSize() const {
    Size<int> result{};
    glfwGetFramebufferSize(windowHandle, &result.width, &result.height);
    return result;
  }

  [[nodiscard]] Scale getContentScale() const {
    Scale result{};
    glfwGetWindowContentScale(windowHandle, &result.x, &result.y);
    return result;
  }

  void setSizeLimits(Size<int> minSize, Size<int> maxSize) {
    assert(minSize.width >= 0 && minSize.height >= 0);
    assert(maxSize.width >= minSize.width && maxSize.height >= minSize.height);
    glfwSetWindowSizeLimits(windowHandle, minSize.width, minSize.height, maxSize.width, maxSize.height);
  }

  void setAspectRatio(int numer, int denom) { glfwSetWindowAspectRatio(windowHandle, numer, denom); }

  [[nodiscard]] float getOpacity() const { return glfwGetWindowOpacity(windowHandle); }
  void setOpacity(float opacity) { glfwSetWindowOpacity(windowHandle, opacity); }

  void restore() { glfwRestoreWindow(windowHandle); }
  void maximize() { glfwMaximizeWindow(windowHandle); }
  void hide() { glfwHideWindow(windowHandle); }
  void show() { glfwShowWindow(windowHandle); }
  void iconify() { glfwIconifyWindow(windowHandle); }

  [[nodiscard]] bool isVisible() const { return glfwGetWindowAttrib(windowHandle, GLFW_VISIBLE) == GLFW_TRUE; }
  [[nodiscard]] bool isMaximized() const { return glfwGetWindowAttrib(windowHandle, GLFW_MAXIMIZED) == GLFW_TRUE; }

  void setFocus() { glfwFocusWindow(windowHandle); }

  void requestAttention() { glfwRequestWindowAttention(windowHandle); }

  [[nodiscard]] std::optional<Monitor> getFullscreenMonitor() const {
    const auto monitorPtr = glfwGetWindowMonitor(windowHandle);
    if (monitorPtr == nullptr) { return std::nullopt; }
    return Monitor{monitorPtr};
  }
  void setMonitor(Monitor &monitor, Position<int> windowPosition, Size<int> windowSize, int refreshRate = DontCare) {
    // TODO: change this, use it to implement fullscreen etc.
    glfwSetWindowMonitor(windowHandle, monitor.getHandle(), windowPosition.x, windowPosition.y, windowSize.width, windowSize.height,
                         refreshRate);
  }

  [[nodiscard]] bool isDecorated() const { return glfwGetWindowAttrib(windowHandle, GLFW_DECORATED) == GLFW_TRUE; }
  [[nodiscard]] bool isResizable() const { return glfwGetWindowAttrib(windowHandle, GLFW_RESIZABLE) == GLFW_TRUE; }
  [[nodiscard]] bool isFloating() const { return glfwGetWindowAttrib(windowHandle, GLFW_FLOATING) == GLFW_TRUE; }
  [[nodiscard]] bool isAutoIconify() const { return glfwGetWindowAttrib(windowHandle, GLFW_AUTO_ICONIFY) == GLFW_TRUE; }
  [[nodiscard]] bool isFocusOnShow() const { return glfwGetWindowAttrib(windowHandle, GLFW_FOCUS_ON_SHOW) == GLFW_TRUE; }

  void setDecorated(bool decorated) { glfwSetWindowAttrib(windowHandle, GLFW_DECORATED, decorated ? GLFW_TRUE : GLFW_FALSE); }
  void setResizable(bool resizable) { glfwSetWindowAttrib(windowHandle, GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE); }
  void setFloating(bool floating) { glfwSetWindowAttrib(windowHandle, GLFW_FLOATING, floating ? GLFW_TRUE : GLFW_FALSE); }
  void setAutoIconify(bool autoIconify) { glfwSetWindowAttrib(windowHandle, GLFW_AUTO_ICONIFY, autoIconify ? GLFW_TRUE : GLFW_FALSE); }
  void setFocusOnShow(bool focusOnShow) { glfwSetWindowAttrib(windowHandle, GLFW_FOCUS_ON_SHOW, focusOnShow ? GLFW_TRUE : GLFW_FALSE); }

  [[nodiscard]] GLFWwindow *getHandle() { return windowHandle; }
  [[nodiscard]] const GLFWwindow *getHandle() const { return windowHandle; }

  [[nodiscard]] CursorBehavior getCursorBehavior() const {
    return static_cast<CursorBehavior>(glfwGetInputMode(windowHandle, GLFW_CURSOR));
  }
  [[nodiscard]] bool isStickyKeys() const { return glfwGetInputMode(windowHandle, GLFW_STICKY_KEYS) == GLFW_TRUE; }
  [[nodiscard]] bool isStickyMouseButtons() const { return glfwGetInputMode(windowHandle, GLFW_STICKY_MOUSE_BUTTONS) == GLFW_TRUE; }
  [[nodiscard]] bool isLockModifierKeys() const { return glfwGetInputMode(windowHandle, GLFW_LOCK_KEY_MODS) == GLFW_TRUE; }
  [[nodiscard]] bool isRawMouseMotionSupported() const { return glfwRawMouseMotionSupported(); }
  [[nodiscard]] bool isRawMouseMotionEnabled() const { return glfwGetInputMode(windowHandle, GLFW_RAW_MOUSE_MOTION) == GLFW_TRUE; }

  void setCursorBehavior(CursorBehavior behavior) { glfwSetInputMode(windowHandle, GLFW_CURSOR, static_cast<int>(behavior)); }
  void setStickyKeys(bool sticky) { glfwSetInputMode(windowHandle, GLFW_STICKY_KEYS, sticky ? GLFW_TRUE : GLFW_FALSE); }
  void setStickyMouseButtons(bool sticky) { glfwSetInputMode(windowHandle, GLFW_STICKY_MOUSE_BUTTONS, sticky ? GLFW_TRUE : GLFW_FALSE); }
  void setLockModifierKeys(bool lock) { glfwSetInputMode(windowHandle, GLFW_LOCK_KEY_MODS, lock ? GLFW_TRUE : GLFW_FALSE); }
  void setRawMouseMotionEnabled(bool enabled) { glfwSetInputMode(windowHandle, GLFW_RAW_MOUSE_MOTION, enabled ? GLFW_TRUE : GLFW_FALSE); }

  void setCurrent() { glfwMakeContextCurrent(windowHandle); }

  void swapBuffers() { glfwSwapBuffers(windowHandle); }

  void setKeyCallback(KeyListener auto &&callback, bool callPreviousCallback = false) {
    keyCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetKeyCallback(windowHandle, keyGLFWCallback);
    previousCallbacks.glfWkeyfun = callPreviousCallback ? previousCallback : nullptr;
  }

  void setCharCallback(CharListener auto &&callback, bool callPreviousCallback = false) {
    charCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetCharCallback(windowHandle, charGLFWCallback);
    previousCallbacks.glfWcharfun = callPreviousCallback ? previousCallback : nullptr;
  }

  void setMouseButtonCallback(MouseButtonListener auto &&callback, bool callPreviousCallback = false) {
    mouseButtonCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetMouseButtonCallback(windowHandle, mouseButtonGLFWCallback);
    previousCallbacks.glfWmousebuttonfun = callPreviousCallback ? previousCallback : nullptr;
  }

  void setCursorPositionCallback(CursorPositionListener auto &&callback, bool callPreviousCallback = false) {
    cursorPositionCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetCursorPosCallback(windowHandle, cursorPositionGLFWCallback);
    previousCallbacks.glfWcursorposfun = callPreviousCallback ? previousCallback : nullptr;
  }

  void setCursorEnterCallback(CursorEnterListener auto &&callback, bool callPreviousCallback = false) {
    cursorEnterCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetCursorEnterCallback(windowHandle, cursorEnterGLFWCallback);
    previousCallbacks.glfWcursorenterfun = callPreviousCallback ? previousCallback : nullptr;
  }

  void setScrollCallback(ScrollListener auto &&callback, bool callPreviousCallback = false) {
    scrollCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetScrollCallback(windowHandle, scrollGLFWCallback);
    previousCallbacks.glfWscrollfun = callPreviousCallback ? previousCallback : nullptr;
  }

  void setDropCallback(DropListener auto &&callback, bool callPreviousCallback = false) {
    dropCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetDropCallback(windowHandle, dropGLFWCallback);
    previousCallbacks.glfWdropfun = callPreviousCallback ? previousCallback : nullptr;
  }

  void setContentScaleCallback(ContentScaleListener auto &&callback, bool callPreviousCallback = false) {
    contentScaleCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetWindowContentScaleCallback(windowHandle, contentScaleGLFWCallback);
    previousCallbacks.glfWwindowcontentscalefun = callPreviousCallback ? previousCallback : nullptr;
  }

  void setPositionListener(WindowPositionListener auto &&callback, bool callPreviousCallback = false) {
    positionCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetWindowPosCallback(windowHandle, positionGLFWCallback);
    previousCallbacks.glfWwindowposfun = callPreviousCallback ? previousCallback : nullptr;
  }

  void setSizeListener(WindowSizeListener auto &&callback, bool callPreviousCallback = false) {
    sizeCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetWindowSizeCallback(windowHandle, sizeGLFWCallback);
    previousCallbacks.glfWwindowsizefun = callPreviousCallback ? previousCallback : nullptr;
  }

  void setCloseListener(WindowCloseListener auto &&callback, bool callPreviousCallback = false) {
    closeCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetWindowCloseCallback(windowHandle, closeGLFWCallback);
    previousCallbacks.glfWwindowclosefun = callPreviousCallback ? previousCallback : nullptr;
  }

  void setRefreshListener(WindowRefreshListener auto &&callback, bool callPreviousCallback = false) {
    refreshCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetWindowRefreshCallback(windowHandle, refreshGLFWCallback);
    previousCallbacks.glfWwindowrefreshfun = callPreviousCallback ? previousCallback : nullptr;
  }

  void setFocusListener(WindowFocusListener auto &&callback, bool callPreviousCallback = false) {
    focusCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetWindowFocusCallback(windowHandle, focusGLFWCallback);
    previousCallbacks.glfWwindowfocusfun = callPreviousCallback ? previousCallback : nullptr;
  }

  void setIconifyListener(WindowIconifyListener auto &&callback, bool callPreviousCallback = false) {
    iconifyCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetWindowIconifyCallback(windowHandle, iconifyGLFWCallback);
    previousCallbacks.glfWwindowiconifyfun = callPreviousCallback ? previousCallback : nullptr;
  }

  void setMaximizeListener(WindowMaximizeListener auto &&callback, bool callPreviousCallback = false) {
    maximizeCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetWindowMaximizeCallback(windowHandle, maximizeGLFWCallback);
    previousCallbacks.glfWwindowmaximizefun = callPreviousCallback ? previousCallback : nullptr;
  }

  void setFramebufferSizeListener(WindowFramebufferSizeListener auto &&callback, bool callPreviousCallback = false) {
    framebufferSizeCallback = std::forward<decltype(callback)>(callback);
    const auto previousCallback = glfwSetFramebufferSizeCallback(windowHandle, framebufferSizeGLFWCallback);
    previousCallbacks.glfWframebuffersizefun = callPreviousCallback ? previousCallback : nullptr;
  }

 private:
  explicit Window(GLFWwindow *handle) : windowHandle{handle} {}

  using KeyCallback = std::function<void(Key, KeyAction, Flags<ModifierKey>)>;
  using CharCallback = std::function<void(std::u32string::value_type)>;
  using MouseButtonCallback = std::function<void(MouseButton, ButtonState, Flags<ModifierKey>)>;
  using CursorPositionCallback = std::function<void(Position<double>)>;
  using CursorEnterCallback = std::function<void(CursorEntered)>;
  using ScrollCallback = std::function<void(double, double)>;
  using DropCallback = std::function<void(std::vector<std::filesystem::path>)>;
  using ContentScaleCallback = std::function<void(Scale)>;
  using PositionCallback = std::function<void(Position<int>)>;
  using SizeCallback = std::function<void(Size<int>)>;
  using CloseCallback = std::function<void()>;
  using RefreshCallback = std::function<void()>;
  using FocusCallback = std::function<void(bool)>;
  using IconifyCallback = std::function<void(bool)>;
  using MaximizeCallback = std::function<void(bool)>;
  using FrameBufferSizeCallback = std::function<void(Size<int>)>;

  KeyCallback keyCallback = [](auto, auto, auto) {};
  static void keyGLFWCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWkeyfun != nullptr) { self->previousCallbacks.glfWkeyfun(window, key, scancode, action, mods); }
    self->keyCallback(static_cast<Key>(key), static_cast<KeyAction>(action), Flags<ModifierKey>{static_cast<ModifierKey>(mods)});
  }

  CharCallback charCallback = [](auto) {};
  static void charGLFWCallback(GLFWwindow *window, unsigned int codepoint) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWcharfun != nullptr) { self->previousCallbacks.glfWcharfun(window, codepoint); }
    self->charCallback(codepoint);
  }

  MouseButtonCallback mouseButtonCallback = [](auto, auto, auto) {};
  static void mouseButtonGLFWCallback(GLFWwindow *window, int button, int action, int mods) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWmousebuttonfun != nullptr) { self->previousCallbacks.glfWmousebuttonfun(window, button, action, mods); }
    const auto state = static_cast<ButtonState>(action);
    const auto mouseButton = static_cast<MouseButton>(button);
    const auto modFlags = Flags<ModifierKey>{static_cast<ModifierKey>(mods)};
    self->mouseButtonCallback(mouseButton, state, modFlags);
  }

  CursorPositionCallback cursorPositionCallback = [](auto) {};
  static void cursorPositionGLFWCallback(GLFWwindow *window, double xpos, double ypos) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWcursorposfun != nullptr) { self->previousCallbacks.glfWcursorposfun(window, xpos, ypos); }
    self->cursorPositionCallback({xpos, ypos});
  }

  CursorEnterCallback cursorEnterCallback = [](auto) {};
  static void cursorEnterGLFWCallback(GLFWwindow *window, int entered) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWcursorenterfun != nullptr) { self->previousCallbacks.glfWcursorenterfun(window, entered); }
    self->cursorEnterCallback(static_cast<CursorEntered>(entered));
  }

  ScrollCallback scrollCallback = [](auto, auto) {};
  static void scrollGLFWCallback(GLFWwindow *window, double xoffset, double yoffset) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWscrollfun != nullptr) { self->previousCallbacks.glfWscrollfun(window, xoffset, yoffset); }
    self->scrollCallback(xoffset, yoffset);
  }

  DropCallback dropCallback = [](auto) {};
  static void dropGLFWCallback(GLFWwindow *window, int pathCount, const char *paths[]) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWdropfun != nullptr) { self->previousCallbacks.glfWdropfun(window, pathCount, paths); }
    std::vector<std::filesystem::path> fsPaths;
    fsPaths.reserve(pathCount);
    std::ranges::transform(std::span{paths, static_cast<std::size_t>(pathCount)}, std::back_inserter(fsPaths),
                           [](const auto path) { return std::filesystem::path{path}; });
    self->dropCallback(fsPaths);
  }

  ContentScaleCallback contentScaleCallback = [](auto) {};
  static void contentScaleGLFWCallback(GLFWwindow *window, float xscale, float yscale) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWwindowcontentscalefun != nullptr) {
      self->previousCallbacks.glfWwindowcontentscalefun(window, xscale, yscale);
    }
    self->contentScaleCallback({xscale, yscale});
  }

  PositionCallback positionCallback = [](auto) {};
  static void positionGLFWCallback(GLFWwindow *window, int xpos, int ypos) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWwindowposfun != nullptr) { self->previousCallbacks.glfWwindowposfun(window, xpos, ypos); }
    self->positionCallback({xpos, ypos});
  }

  SizeCallback sizeCallback = [](auto) {};
  static void sizeGLFWCallback(GLFWwindow *window, int width, int height) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWwindowsizefun != nullptr) { self->previousCallbacks.glfWwindowsizefun(window, width, height); }
    self->sizeCallback({width, height});
  }

  CloseCallback closeCallback = []() {};
  static void closeGLFWCallback(GLFWwindow *window) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWwindowclosefun != nullptr) { self->previousCallbacks.glfWwindowclosefun(window); }
    self->closeCallback();
  }

  RefreshCallback refreshCallback = []() {};
  static void refreshGLFWCallback(GLFWwindow *window) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWwindowrefreshfun != nullptr) { self->previousCallbacks.glfWwindowrefreshfun(window); }
    self->refreshCallback();
  }

  FocusCallback focusCallback = [](auto) {};
  static void focusGLFWCallback(GLFWwindow *window, int focused) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWwindowfocusfun != nullptr) { self->previousCallbacks.glfWwindowfocusfun(window, focused); }
    self->focusCallback(focused == GLFW_TRUE);
  }

  IconifyCallback iconifyCallback = [](auto) {};
  static void iconifyGLFWCallback(GLFWwindow *window, int iconified) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWwindowiconifyfun != nullptr) { self->previousCallbacks.glfWwindowiconifyfun(window, iconified); }
    self->iconifyCallback(iconified == GLFW_TRUE);
  }

  MaximizeCallback maximizeCallback = [](auto) {};
  static void maximizeGLFWCallback(GLFWwindow *window, int maximized) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWwindowmaximizefun != nullptr) { self->previousCallbacks.glfWwindowmaximizefun(window, maximized); }
    self->maximizeCallback(maximized == GLFW_TRUE);
  }

  FrameBufferSizeCallback framebufferSizeCallback = [](auto) {};
  static void framebufferSizeGLFWCallback(GLFWwindow *window, int width, int height) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self->previousCallbacks.glfWframebuffersizefun != nullptr) {
      self->previousCallbacks.glfWframebuffersizefun(window, width, height);
    }
    self->framebufferSizeCallback({width, height});
  }

  GLFWwindow *windowHandle;

  struct {
    GLFWkeyfun glfWkeyfun = nullptr;
    GLFWcharfun glfWcharfun = nullptr;
    GLFWmousebuttonfun glfWmousebuttonfun = nullptr;
    GLFWcursorposfun glfWcursorposfun = nullptr;
    GLFWcursorenterfun glfWcursorenterfun = nullptr;
    GLFWscrollfun glfWscrollfun = nullptr;
    GLFWdropfun glfWdropfun = nullptr;
    GLFWwindowcontentscalefun glfWwindowcontentscalefun = nullptr;
    GLFWwindowposfun glfWwindowposfun = nullptr;
    GLFWwindowsizefun glfWwindowsizefun = nullptr;
    GLFWwindowclosefun glfWwindowclosefun = nullptr;
    GLFWwindowrefreshfun glfWwindowrefreshfun = nullptr;
    GLFWwindowfocusfun glfWwindowfocusfun = nullptr;
    GLFWwindowiconifyfun glfWwindowiconifyfun = nullptr;
    GLFWwindowmaximizefun glfWwindowmaximizefun = nullptr;
    GLFWframebuffersizefun glfWframebuffersizefun = nullptr;
  } previousCallbacks;
};

}  // namespace pf::glfw

#endif  // PF_GLFW_WINDOW_H
