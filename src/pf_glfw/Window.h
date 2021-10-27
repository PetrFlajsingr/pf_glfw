//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_SRC_PF_GLFW_WINDOW_H
#define PF_GLFW_SRC_PF_GLFW_WINDOW_H

#include <GLFW/glfw3.h>
#include <filesystem>
#include <functional>
#include <pf_common/enums.h>
#include <pf_glfw/enums/CursorEntered.h>
#include <pf_glfw/enums/Key.h>
#include <pf_glfw/enums/KeyAction.h>
#include <pf_glfw/enums/ModifierKey.h>
#include <pf_glfw/enums/MouseButton.h>
#include <pf_glfw/enums/MouseButtonAction.h>
#include <string>

// TODO: monitor, cursor
// input stuff:
// glfwGetInputMode - Window
// glfwSetInputMode - Window
// glfwRawMouseMotionSupported - Window
// glfwCreateCursor
// glfwCreateStandardCursor
// glfwDestroyCursor
// glfwSetCursor - Window
// joystick stuff
// gamepad stuff
// glfwGetTime
// glfwSetTime
// glfwGetTimerValue
// glfwGetTimerFrequency

namespace pf::glfw {


struct WindowConfig {
  std::size_t width;
  std::size_t height;
  std::string title;
  // TODO: monitor
};
// TODO: move this out
struct CursorPosition {
  double x;
  double y;
};
template<typename F>
concept KeyListener = std::is_invocable_r_v<void, F, Key, KeyAction, Flags<ModifierKey>>;
template<typename F>
concept CharListener = std::is_invocable_r_v<void, F, std::u32string::value_type>;
template<typename F>
concept MouseButtonListener = std::is_invocable_r_v<void, F, MouseButton, MouseButtonAction, Flags<ModifierKey>>;
template<typename F>
concept CursorPositionListener = std::is_invocable_r_v<void, F, CursorPosition>;
template<typename F>
concept CursorEnterListener = std::is_invocable_r_v<void, F, CursorEntered>;
template<typename F>
concept ScrollListener = std::is_invocable_r_v<void, F, double, double>;
template<typename F>
concept DropListener = std::is_invocable_r_v<void, F, std::vector<std::filesystem::path>>;

// TODO: opengl/vulkan descendant
// TODO: click, double click
class Window {
 public:
  explicit Window(const WindowConfig &config);
  virtual ~Window();

  [[nodiscard]] bool shouldClose() const;
  void close();

  [[nodiscard]] KeyAction getLastKeyState(Key key) const;
  [[nodiscard]] MouseButtonAction getLastMouseButtonState(MouseButton button) const;

  [[nodiscard]] CursorPosition getCursorPosition() const;
  void setCursorPosition(CursorPosition cursorPosition);

  [[nodiscard]] std::string getClipboardContents() const;
  void setClipboardContents(const std::string &contents);

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

 private:
  std::function<void(Key, KeyAction, Flags<ModifierKey>)> keyCallback;
  static void keyGLFWCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

  std::function<void(std::u32string::value_type)> charCallback;
  static void charGLFWCallback(GLFWwindow *window, unsigned int codepoint);

  std::function<void(MouseButton, MouseButtonAction, Flags<ModifierKey>)> mouseButtonCallback;
  static void mouseButtonGLFWCallback(GLFWwindow *window, int button, int action, int mods);

  std::function<void(CursorPosition)> cursorPositionCallback;
  static void cursorPositionGLFWCallback(GLFWwindow *window, double xpos, double ypos);

  std::function<void(CursorEntered)> cursorEnterCallback;
  static void cursorEnterGLFWCallback(GLFWwindow *window, int entered);

  std::function<void(double, double)> scrollCallback;
  static void scrollGLFWCallback(GLFWwindow *window, double xoffset, double yoffset);

  std::function<void(std::vector<std::filesystem::path>)> dropCallback;
  static void dropGLFWCallback(GLFWwindow *window, int pathCount, const char* paths[]);

  GLFWwindow *windowHandle;
};

}// namespace pf::glfw

#endif//PF_GLFW_SRC_PF_GLFW_WINDOW_H
