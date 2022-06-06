//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_WINDOW_H
#define PF_GLFW_WINDOW_H

#include <GLFW/glfw3.h>
#include <filesystem>
#include <functional>
#include <magic_enum.hpp>
#include <optional>
#include <pf_common/enums.h>
#include <pf_glfw/Cursor.h>
#include <pf_glfw/Image.h>
#include <pf_glfw/Monitor.h>
#include <pf_glfw/WindowHints.h>
#include <pf_glfw/_export.h>
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

struct PF_GLFW_EXPORT WindowOpenGlConfig { //-V730
  std::size_t width;
  std::size_t height;
  std::string title;
  std::optional<Monitor> monitor = std::nullopt;
  ClientAPI clientApi =
      ClientAPI::OpenGL;
  int majorOpenGLVersion;
  int minorOpenGLVersion;
  WindowHints hints{};
};

struct PF_GLFW_EXPORT WindowNoApiConfig { //-V730
  std::size_t width;
  std::size_t height;
  std::string title;
  std::optional<Monitor> monitor = std::nullopt;

  WindowHints hints{};
};

// TODO: return value checks
// TODO: context sharing
class PF_GLFW_EXPORT Window {
  friend class GLFW;

 public:
  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;
  Window(Window &&other) noexcept;
  Window &operator=(Window &&other) noexcept;
  virtual ~Window();

  [[nodiscard]] bool shouldClose() const;
  void close();

  [[nodiscard]] ButtonState getLastKeyState(Key key) const;
  [[nodiscard]] ButtonState getLastMouseButtonState(MouseButton button) const;

  [[nodiscard]] Position<double> getCursorPosition() const;
  void setCursorPosition(Position<double> cursorPosition);

  [[nodiscard]] std::optional<std::string> getClipboardContents() const;
  void setClipboardContents(const std::string &contents);

  void setCursor(Cursor &cursor);

  void setTitle(const std::string &title);

  void setIcon(const std::vector<Image> &icons);

  [[nodiscard]] Position<int> getPosition() const;
  void setPosition(Position<int> position);

  [[nodiscard]] Size<int> getSize() const;
  void setSize(Size<int> size);

  [[nodiscard]] Box<int> getFrameSize() const;

  [[nodiscard]] Size<int> getFramebufferSize() const;

  [[nodiscard]] Scale getContentScale() const;

  void setSizeLimits(Size<int> minSize, Size<int> maxSize);

  void setAspectRatio(int numer, int denom);

  [[nodiscard]] float getOpacity() const;
  void setOpacity(float opacity);

  void restore();
  void maximize();
  void hide();
  void show();
  void iconify();

  [[nodiscard]] bool isVisible() const;
  [[nodiscard]] bool isMaximized() const;

  void setFocus();

  void requestAttention();

  [[nodiscard]] std::optional<Monitor> getFullscreenMonitor() const;
  void setMonitor(Monitor &monitor, Position<int> windowPosition, Size<int> windowSize, int refreshRate = DontCare);

  [[nodiscard]] bool isDecorated() const;
  [[nodiscard]] bool isResizable() const;
  [[nodiscard]] bool isFloating() const;
  [[nodiscard]] bool isAutoIconify() const;
  [[nodiscard]] bool isFocusOnShow() const;

  void setDecorated(bool decorated);
  void setResizable(bool resizable);
  void setFloating(bool floating);
  void setAutoIconify(bool autoIconify);
  void setFocusOnShow(bool focusOnShow);

  [[nodiscard]] GLFWwindow *getHandle();
  [[nodiscard]] const GLFWwindow *getHandle() const;

  [[nodiscard]] CursorBehavior getCursorBehavior() const;
  [[nodiscard]] bool isStickyKeys() const;
  [[nodiscard]] bool isStickyMouseButtons() const;
  [[nodiscard]] bool isLockModifierKeys() const;
  [[nodiscard]] bool isRawMouseMotionSupported() const;
  [[nodiscard]] bool isRawMouseMotionEnabled() const;

  void setCursorBehavior(CursorBehavior behavior);
  void setStickyKeys(bool sticky);
  void setStickyMouseButtons(bool sticky);
  void setLockModifierKeys(bool lock);
  void setRawMouseMotionEnabled(bool enabled);

  void setCurrent();

  void swapBuffers();

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
  explicit Window(WindowOpenGlConfig config);
  explicit Window(WindowNoApiConfig config);

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
  static void keyGLFWCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

  CharCallback charCallback = [](auto) {};
  static void charGLFWCallback(GLFWwindow *window, unsigned int codepoint);

  MouseButtonCallback mouseButtonCallback = [](auto, auto, auto) {};
  static void mouseButtonGLFWCallback(GLFWwindow *window, int button, int action, int mods);

  CursorPositionCallback cursorPositionCallback = [](auto) {};
  static void cursorPositionGLFWCallback(GLFWwindow *window, double xpos, double ypos);

  CursorEnterCallback cursorEnterCallback = [](auto) {};
  static void cursorEnterGLFWCallback(GLFWwindow *window, int entered);

  ScrollCallback scrollCallback = [](auto, auto) {};
  static void scrollGLFWCallback(GLFWwindow *window, double xoffset, double yoffset);

  DropCallback dropCallback = [](auto) {};
  static void dropGLFWCallback(GLFWwindow *window, int pathCount, const char *paths[]);

  ContentScaleCallback contentScaleCallback = [](auto) {};
  static void contentScaleGLFWCallback(GLFWwindow *window, float xscale, float yscale);

  PositionCallback positionCallback = [](auto) {};
  static void positionGLFWCallback(GLFWwindow *window, int xpos, int ypos);

  SizeCallback sizeCallback = [](auto) {};
  static void sizeGLFWCallback(GLFWwindow *window, int width, int height);

  CloseCallback closeCallback = []() {};
  static void closeGLFWCallback(GLFWwindow *window);

  RefreshCallback refreshCallback = []() {};
  static void refreshGLFWCallback(GLFWwindow *window);

  FocusCallback focusCallback = [](auto) {};
  static void focusGLFWCallback(GLFWwindow *window, int focused);

  IconifyCallback iconifyCallback = [](auto) {};
  static void iconifyGLFWCallback(GLFWwindow *window, int iconified);

  MaximizeCallback maximizeCallback = [](auto) {};
  static void maximizeGLFWCallback(GLFWwindow *window, int maximized);

  FrameBufferSizeCallback framebufferSizeCallback = [](auto) {};
  static void framebufferSizeGLFWCallback(GLFWwindow *window, int width, int height);

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
