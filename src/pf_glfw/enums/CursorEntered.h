//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_SRC_PF_GLFW_ENUMS_CURSORENTERED_H
#define PF_GLFW_SRC_PF_GLFW_ENUMS_CURSORENTERED_H

#include <GLFW/glfw3.h>
#include <pf_glfw/_export.h>

namespace pf::glfw {
enum class PF_GLFW_EXPORT CursorEntered {
  Yes = GLFW_TRUE,
  No = GLFW_FALSE
};
}

#endif//PF_GLFW_SRC_PF_GLFW_ENUMS_CURSORENTERED_H
