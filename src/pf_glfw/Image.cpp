//
// Created by xflajs00 on 27.10.2021.
//

#include "Image.h"
#include <GLFW/glfw3.h>

namespace pf::glfw {

Image::Image(std::size_t width, std::size_t height, std::span<const std::byte> pixels) : imagePixels(pixels.begin(), pixels.end()) {
  imageHandle.width = width;
  imageHandle.height = height;
  imageHandle.pixels = reinterpret_cast<unsigned char *>(imagePixels.data());
}

Image::Image(const Image & other) : imageHandle(other.imageHandle), imagePixels(other.imagePixels) {
  imageHandle.pixels = reinterpret_cast<unsigned char *>(imagePixels.data());
}

Image& Image::operator=(const Image & other) {
  imageHandle= other.imageHandle;
  imagePixels = other.imagePixels;
  imageHandle.pixels = reinterpret_cast<unsigned char *>(imagePixels.data());
  return *this;
}

Image::Image(Image && other) noexcept : imageHandle(other.imageHandle), imagePixels(std::move(other.imagePixels)) {
  imageHandle.pixels = reinterpret_cast<unsigned char *>(imagePixels.data());
}

Image& Image::operator=(Image && other) noexcept {
  imageHandle= other.imageHandle;
  imagePixels = std::move(other.imagePixels);
  imageHandle.pixels = reinterpret_cast<unsigned char *>(imagePixels.data());
  return *this;
}

std::size_t Image::getWidth() const {
  return imageHandle.width;
}

std::size_t Image::getHeight() const {
  return imageHandle.height;
}

std::span<const std::byte> Image::getPixels() const {
  return std::span{imagePixels.begin(), imagePixels.end()};
}

GLFWimage *Image::getHandle() {
  return &imageHandle;
}

const GLFWimage *Image::getHandle() const {
  return &imageHandle;
}
}// namespace pf::glfw