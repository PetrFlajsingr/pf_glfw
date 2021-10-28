//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_ENUMS_MODIFIERKEY_H
#define PF_GLFW_ENUMS_MODIFIERKEY_H

#include <GLFW/glfw3.h>
#include <pf_glfw/_export.h>

namespace pf::glfw {
enum class PF_GLFW_EXPORT ModifierKey {
  Shift = GLFW_MOD_SHIFT,
  Control = GLFW_MOD_CONTROL,
  Alt = GLFW_MOD_ALT,
  Super = GLFW_MOD_SUPER,
  CapsLock = GLFW_MOD_CAPS_LOCK,
  NumLock = GLFW_MOD_NUM_LOCK,
};
}

#endif//PF_GLFW_ENUMS_MODIFIERKEY_H
