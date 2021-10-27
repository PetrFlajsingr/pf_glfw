//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_SRC_PF_GLFW_CURSOR_H
#define PF_GLFW_SRC_PF_GLFW_CURSOR_H

#include "Image.h"
#include <GLFW/glfw3.h>

#include <pf_glfw/enums/CursorShape.h>

namespace pf::glfw {

class Cursor {
 public:
  Cursor(const Image &image, int xHotspot, int yHotspot);

  explicit Cursor(CursorShape cursorShape);

  virtual ~Cursor();

  [[nodiscard]] GLFWcursor *getHandle();
 private:
  GLFWcursor *cursorHandle;
};

}

#endif//PF_GLFW_SRC_PF_GLFW_CURSOR_H
