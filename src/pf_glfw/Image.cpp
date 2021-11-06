//
// Created by xflajs00 on 27.10.2021.
//

#include "Image.h"
#include <GLFW/glfw3.h>

namespace pf::glfw {

Image::Image(std::size_t width, std::size_t height, std::span<const std::byte> pixels) : imageHandle(std::make_shared<GLFWimage>()),
                                                                                   imagePixels(pixels.begin(), pixels.end()) {
  imageHandle->width = width;
  imageHandle->height = height;
  imageHandle->pixels = reinterpret_cast<unsigned char *>(imagePixels.data());
}

std::size_t Image::getWidth() const {
  return imageHandle->width;
}

std::size_t Image::getHeight() const {
  return imageHandle->height;
}

std::span<const std::byte> Image::getPixels() const {
  return std::span{imagePixels.begin(), imagePixels.end()};
}

GLFWimage *Image::getHandle() {
  return imageHandle.get();
}

const GLFWimage *Image::getHandle() const {
  return imageHandle.get();
}
}// namespace pf::glfw