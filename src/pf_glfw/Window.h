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
#include <pf_glfw/enums/MouseButtonAction.h>
#include <pf_glfw/fwd.h>
#include <string>

namespace pf::glfw {

struct PF_GLFW_EXPORT WindowConfig {
  std::size_t width;
  std::size_t height;
  std::string title;
  std::optional<Monitor> monitor = std::nullopt;
  ClientAPI clientApi =
#ifdef PF_GLFW_OPENGL
      ClientAPI::OpenGL;
#else
      ClientAPI::None;
#endif
#ifdef PF_GLFW_OPENGL
  int majorOpenGLVersion;
  int minorOpenGLVersion;
#endif
  WindowHints hints{};
};

// TODO: double click
// TODO: return value checks
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

  [[nodiscard]] std::string getClipboardContents() const;
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

  void setFocus();

  void requestAttention();

  [[nodiscard]] Monitor getMonitor() const;
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

  [[nodiscard]] ButtonState getMouseButtonState(MouseButton button) const;

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

#ifdef PF_GLFW_OPENGL
  void swapBuffers();
#endif

  void setKeyCallback(KeyListener auto &&callback) {
    keyCallback = std::forward<decltype(callback)>(callback);
    glfwSetKeyCallback(windowHandle, keyGLFWCallback);
  }

  void setCharCallback(CharListener auto &&callback) {
    charCallback = std::forward<decltype(callback)>(callback);
    glfwSetCharCallback(windowHandle, charGLFWCallback);
  }

  void setMouseButtonCallback(MouseButtonListener auto &&callback) {
    mouseButtonCallback = std::forward<decltype(callback)>(callback);
    glfwSetMouseButtonCallback(windowHandle, mouseButtonGLFWCallback);
  }

  void setMouseClickCallback(MouseClickListener auto &&callback) {
    mouseClickCallback = std::forward<decltype(callback)>(callback);
    glfwSetMouseButtonCallback(windowHandle, mouseButtonGLFWCallback);
  }

  void setCursorPositionCallback(CursorPositionListener auto &&callback) {
    cursorPositionCallback = std::forward<decltype(callback)>(callback);
    glfwSetCursorPosCallback(windowHandle, cursorPositionGLFWCallback);
  }

  void setCursorEnterCallback(CursorEnterListener auto &&callback) {
    cursorEnterCallback = std::forward<decltype(callback)>(callback);
    glfwSetCursorEnterCallback(windowHandle, cursorEnterGLFWCallback);
  }

  void setScrollCallback(ScrollListener auto &&callback) {
    scrollCallback = std::forward<decltype(callback)>(callback);
    glfwSetScrollCallback(windowHandle, scrollGLFWCallback);
  }

  void setDropCallback(DropListener auto &&callback) {
    dropCallback = std::forward<decltype(callback)>(callback);
    glfwSetDropCallback(windowHandle, dropGLFWCallback);
  }

  void setContentScaleCallback(ContentScaleListener auto &&callback) {
    contentScaleCallback = std::forward<decltype(callback)>(callback);
    glfwSetWindowContentScaleCallback(windowHandle, contentScaleGLFWCallback);
  }

  void setPositionListener(WindowPositionListener auto &&callback) {
    positionCallback = std::forward<decltype(callback)>(callback);
    glfwSetWindowPosCallback(windowHandle, positionGLFWCallback);
  }

  void setSizeListenerListener(WindowSizeListener auto &&callback) {
    sizeCallback = std::forward<decltype(callback)>(callback);
    glfwSetWindowSizeCallback(windowHandle, sizeGLFWCallback);
  }

  void setCloseListenerListener(WindowCloseListener auto &&callback) {
    closeCallback = std::forward<decltype(callback)>(callback);
    glfwSetWindowCloseCallback(windowHandle, closeGLFWCallback);
  }

  void setRefreshListenerListener(WindowRefreshListener auto &&callback) {
    refreshCallback = std::forward<decltype(callback)>(callback);
    glfwSetWindowRefreshCallback(windowHandle, refreshGLFWCallback);
  }

  void setFocusListenerListener(WindowFocusListener auto &&callback) {
    focusCallback = std::forward<decltype(callback)>(callback);
    glfwSetWindowFocusCallback(windowHandle, focusGLFWCallback);
  }

  void setIconifyListenerListener(WindowIconifyListener auto &&callback) {
    iconifyCallback = std::forward<decltype(callback)>(callback);
    glfwSetWindowIconifyCallback(windowHandle, iconifyGLFWCallback);
  }

  void setMaximizeListenerListener(WindowMaximizeListener auto &&callback) {
    maximizeCallback = std::forward<decltype(callback)>(callback);
    glfwSetWindowMaximizeCallback(windowHandle, maximizeGLFWCallback);
  }

  void setFramebufferSizeListenerListener(WindowFramebufferSizeListener auto &&callback) {
    framebufferSizeCallback = std::forward<decltype(callback)>(callback);
    glfwSetFramebufferSizeCallback(windowHandle, framebufferSizeGLFWCallback);
  }

  void setInputIgnorePredicate(std::predicate auto &&predicate) {
    inputIgnorePredicate = std::forward<decltype(predicate)>(predicate);
  }

 private:
  explicit Window(WindowConfig config);

  std::function<void(Key, KeyAction, Flags<ModifierKey>)> keyCallback = [](auto, auto, auto) {};
  static void keyGLFWCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

  std::function<void(std::u32string::value_type)> charCallback = [](auto) {};
  static void charGLFWCallback(GLFWwindow *window, unsigned int codepoint);

  std::function<void(MouseButton, MouseButtonAction, Flags<ModifierKey>)> mouseButtonCallback = [](auto, auto, auto) {};
  static void mouseButtonGLFWCallback(GLFWwindow *window, int button, int action, int mods);

  std::function<void(MouseButton, Flags<ModifierKey>)> mouseClickCallback = [](auto, auto) {};

  std::function<void(Position<double>)> cursorPositionCallback = [](auto) {};
  static void cursorPositionGLFWCallback(GLFWwindow *window, double xpos, double ypos);

  std::function<void(CursorEntered)> cursorEnterCallback = [](auto) {};
  static void cursorEnterGLFWCallback(GLFWwindow *window, int entered);

  std::function<void(double, double)> scrollCallback = [](auto, auto) {};
  static void scrollGLFWCallback(GLFWwindow *window, double xoffset, double yoffset);

  std::function<void(std::vector<std::filesystem::path>)> dropCallback = [](auto) {};
  static void dropGLFWCallback(GLFWwindow *window, int pathCount, const char *paths[]);

  std::function<void(Scale)> contentScaleCallback = [](auto) {};
  static void contentScaleGLFWCallback(GLFWwindow *window, float xscale, float yscale);

  std::function<void(Position<int>)> positionCallback = [](auto) {};
  static void positionGLFWCallback(GLFWwindow *window, int xpos, int ypos);

  std::function<void(Size<int>)> sizeCallback = [](auto) {};
  static void sizeGLFWCallback(GLFWwindow *window, int xpos, int ypos);

  std::function<void()> closeCallback = []() {};
  static void closeGLFWCallback(GLFWwindow *window);

  std::function<void()> refreshCallback = []() {};
  static void refreshGLFWCallback(GLFWwindow *window);

  std::function<void(bool)> focusCallback = [](auto) {};
  static void focusGLFWCallback(GLFWwindow *window, int focused);

  std::function<void(bool)> iconifyCallback = [](auto) {};
  static void iconifyGLFWCallback(GLFWwindow *window, int iconified);

  std::function<void(bool)> maximizeCallback = [](auto) {};
  static void maximizeGLFWCallback(GLFWwindow *window, int maximized);

  std::function<void(Size<int>)> framebufferSizeCallback = [](auto) {};
  static void framebufferSizeGLFWCallback(GLFWwindow *window, int width, int height);

  std::function<bool()> inputIgnorePredicate = [] { return false; };

  std::array<ButtonState, magic_enum::enum_count<MouseButton>()> mouseButtonStates{ButtonState::Up};

  GLFWwindow *windowHandle;
};

}// namespace pf::glfw

#endif//PF_GLFW_WINDOW_H
