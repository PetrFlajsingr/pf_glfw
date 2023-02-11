//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_ENUMS_CURSORBEHAVIOR_H
#define PF_GLFW_ENUMS_CURSORBEHAVIOR_H

#include <GLFW/glfw3.h>
#include <pf_glfw/_export.h>

namespace pf::glfw {
enum class PF_GLFW_EXPORT CursorBehavior { Normal = GLFW_CURSOR_NORMAL, Hidden = GLFW_CURSOR_HIDDEN, Disabled = GLFW_CURSOR_DISABLED };
}

#endif  // PF_GLFW_ENUMS_CURSORBEHAVIOR_H
