//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_SRC_PF_GLFW_WINDOW_H
#define PF_GLFW_SRC_PF_GLFW_WINDOW_H

#include "Cursor.h"
#include "Monitor.h"
#include <GLFW/glfw3.h>
#include <filesystem>
#include <functional>
#include <optional>
#include <pf_common/enums.h>
#include <pf_glfw/Image.h>
#include <pf_glfw/Monitor.h>
#include <pf_glfw/_export.h>
#include <pf_glfw/concepts.h>
#include <pf_glfw/enums/CursorEntered.h>
#include <pf_glfw/enums/Key.h>
#include <pf_glfw/enums/KeyAction.h>
#include <pf_glfw/enums/ModifierKey.h>
#include <pf_glfw/enums/MouseButton.h>
#include <pf_glfw/enums/MouseButtonAction.h>
#include <pf_glfw/enums/ButtonState.h>
#include <magic_enum.hpp>
#include <pf_glfw/fwd.h>
#include <string>

// TODO;
// input stuff:
// joystick stuff
// gamepad stuff
// glfwGetTime
// glfwSetTime
// glfwGetTimerValue
// glfwGetTimerFrequency

namespace pf::glfw {

// TODO: hints and opengl init stuff
struct PF_GLFW_EXPORT WindowConfig {
  std::size_t width;
  std::size_t height;
  std::string title;
  std::optional<Monitor> monitor = std::nullopt;
};

// TODO: click, double click
// TODO: builder with hints?
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

  [[nodiscard]] KeyAction getLastKeyState(Key key) const;
  [[nodiscard]] MouseButtonAction getLastMouseButtonState(MouseButton button) const;

  [[nodiscard]] CursorPosition getCursorPosition() const;
  void setCursorPosition(CursorPosition cursorPosition);

  [[nodiscard]] std::string getClipboardContents() const;
  void setClipboardContents(const std::string &contents);

  void setCursor(Cursor &cursor);

  void setTitle(const std::string &title);

  void setIcon(const std::vector<Image> &icons);

  [[nodiscard]] WindowPosition getPosition() const;
  void setPosition(WindowPosition position);

  [[nodiscard]] WindowSize getSize() const;
  void setSize(WindowSize size);

  void setSizeLimits(WindowSize minSize, WindowSize maxSize);

  void setAspectRatio(int numer, int denom);

  // glfwGetFramebufferSize
  // glfwGetWindowFrameSize
  // glfwGetWindowCOntentScale
  [[nodiscard]] float getOpacity() const;
  void setOpacity(float opacity);

  // glfwIconifyWindow
  void restore();
  void maximize();
  void hide();
  void show();
  [[nodiscard]] bool isVisible() const;

  void setFocus();

  void requestAttention();

  [[nodiscard]] Monitor getMonitor() const;

  // glfwSetWindowMonitor
  // glfwGetSetWindowAttrib
  // glfwPollEvents/waitEvents + timeout

  [[nodiscard]] GLFWwindow *getHandle();
  [[nodiscard]] const GLFWwindow *getHandle() const;

  [[nodiscard]] ButtonState getMouseButtonState(MouseButton button) const;

  // glfwGetInputMode - Window
  // glfwSetInputMode - Window
  // glfwRawMouseMotionSupported - Window

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

 private:
  explicit Window(WindowConfig config);

  std::function<void(Key, KeyAction, Flags<ModifierKey>)> keyCallback;
  static void keyGLFWCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

  std::function<void(std::u32string::value_type)> charCallback;
  static void charGLFWCallback(GLFWwindow *window, unsigned int codepoint);

  std::function<void(MouseButton, MouseButtonAction, Flags<ModifierKey>)> mouseButtonCallback;
  static void mouseButtonGLFWCallback(GLFWwindow *window, int button, int action, int mods);

  std::function<void(MouseButton, Flags<ModifierKey>)> mouseClickCallback = [](auto, auto){};

  std::function<void(CursorPosition)> cursorPositionCallback;
  static void cursorPositionGLFWCallback(GLFWwindow *window, double xpos, double ypos);

  std::function<void(CursorEntered)> cursorEnterCallback;
  static void cursorEnterGLFWCallback(GLFWwindow *window, int entered);

  std::function<void(double, double)> scrollCallback;
  static void scrollGLFWCallback(GLFWwindow *window, double xoffset, double yoffset);

  std::function<void(std::vector<std::filesystem::path>)> dropCallback;
  static void dropGLFWCallback(GLFWwindow *window, int pathCount, const char *paths[]);


  std::array<ButtonState, magic_enum::enum_count<MouseButton>()> mouseButtonStates{ButtonState::Up};

  GLFWwindow *windowHandle;
};

}// namespace pf::glfw

#endif//PF_GLFW_SRC_PF_GLFW_WINDOW_H
