//
// Created by xflajs00 on 05.10.2022.
//

#ifndef PF_GLFW_VIDEOMODE_H
#define PF_GLFW_VIDEOMODE_H

#include <cstdint>

namespace pf::glfw {

struct VideoMode {
  std::uint32_t width;
  std::uint32_t height;
  std::uint32_t redBitDepth;
  std::uint32_t greenBitDepth;
  std::uint32_t blueBitDepth;
  std::uint32_t refreshRate;
};

}

#endif  //PF_GLFW_VIDEOMODE_H
