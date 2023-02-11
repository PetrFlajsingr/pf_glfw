//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_ENUMS_CONNECTION_H
#define PF_GLFW_ENUMS_CONNECTION_H

#include <GLFW/glfw3.h>

namespace pf::glfw {
enum class Connection { Connected = GLFW_CONNECTED, Disconnected = GLFW_DISCONNECTED };
}

#endif  // PF_GLFW_ENUMS_CONNECTION_H
