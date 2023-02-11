//
// Created by xflajs00 on 27.10.2021.
//

#include "Cursor.h"

namespace pf::glfw {

Cursor::Cursor(const Image &image, int xHotspot, int yHotspot) : cursorHandle(glfwCreateCursor(image.getHandle(), xHotspot, yHotspot)) {}

Cursor::Cursor(CursorShape cursorShape) : cursorHandle(glfwCreateStandardCursor(static_cast<int>(cursorShape))) {}

Cursor::~Cursor() { glfwDestroyCursor(cursorHandle); }

GLFWcursor *Cursor::getHandle() { return cursorHandle; }

}  // namespace pf::glfw
