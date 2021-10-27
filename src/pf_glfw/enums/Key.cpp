//
// Created by xflajs00 on 27.10.2021.
//

#include "Key.h"

namespace pf::glfw {
std::string_view getKeyName(Key key) {
  return glfwGetKeyName(static_cast<int>(key), glfwGetKeyScancode(static_cast<int>(key)));
}
}// namespace pf::glfw