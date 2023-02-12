//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_CURSOR_H
#define PF_GLFW_CURSOR_H

#include "Image.h"
#include <GLFW/glfw3.h>
#include <pf_glfw/enums/CursorShape.h>

namespace pf::glfw {

class Cursor {
 public:
  Cursor(const Image &image, int xHotspot, int yHotspot) : cursorHandle(glfwCreateCursor(image.getHandle(), xHotspot, yHotspot)) {}

  explicit Cursor(CursorShape cursorShape) : cursorHandle(glfwCreateStandardCursor(static_cast<int>(cursorShape))) {}
  Cursor(const Cursor &) = delete;
  Cursor &operator=(const Cursor &) = delete;
  ~Cursor() { glfwDestroyCursor(cursorHandle); }

  [[nodiscard]] GLFWcursor *getHandle() { return cursorHandle; }

 private:
  GLFWcursor *cursorHandle;
};

}  // namespace pf::glfw

#endif  // PF_GLFW_CURSOR_H