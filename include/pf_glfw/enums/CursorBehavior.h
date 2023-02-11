//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_ENUMS_CURSORBEHAVIOR_H
#define PF_GLFW_ENUMS_CURSORBEHAVIOR_H

#include <GLFW/glfw3.h>

namespace pf::glfw {
enum class CursorBehavior { Normal = GLFW_CURSOR_NORMAL, Hidden = GLFW_CURSOR_HIDDEN, Disabled = GLFW_CURSOR_DISABLED };
}

#endif  // PF_GLFW_ENUMS_CURSORBEHAVIOR_H
