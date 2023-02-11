//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_IMAGE_H
#define PF_GLFW_IMAGE_H

#include <GLFW/glfw3.h>
#include <memory>
#include <span>
#include <vector>

namespace pf::glfw {

// gotta be RGBA
class Image {
 public:
  Image(std::size_t width, std::size_t height, std::span<const std::byte> pixels) : imagePixels(pixels.begin(), pixels.end()) {
    imageHandle.width = static_cast<int>(width);
    imageHandle.height = static_cast<int>(height);
    imageHandle.pixels = reinterpret_cast<unsigned char *>(imagePixels.data());
  }
  Image(const Image &other) : imagePixels{other.imagePixels}, imageHandle{other.imageHandle} {
    imageHandle.pixels = reinterpret_cast<unsigned char *>(imagePixels.data());
  }
  Image &operator=(const Image &other) {
    imageHandle = other.imageHandle;
    imagePixels = other.imagePixels;
    imageHandle.pixels = reinterpret_cast<unsigned char *>(imagePixels.data());
    return *this;
  }
  Image(Image &&other) noexcept : imagePixels(std::move(other.imagePixels)), imageHandle(other.imageHandle) {
    imageHandle.pixels = reinterpret_cast<unsigned char *>(imagePixels.data());
  }
  Image &operator=(Image &&other) noexcept {
    imageHandle = other.imageHandle;
    imagePixels = std::move(other.imagePixels);
    imageHandle.pixels = reinterpret_cast<unsigned char *>(imagePixels.data());
    return *this;
  }

  [[nodiscard]] std::size_t getWidth() const { return imageHandle.width; }
  [[nodiscard]] std::size_t getHeight() const { return imageHandle.height; }
  [[nodiscard]] std::span<std::byte> getPixels() { return std::span{imagePixels.begin(), imagePixels.end()}; }
  [[nodiscard]] std::span<const std::byte> getPixels() const { return std::span{imagePixels.begin(), imagePixels.end()}; }

  [[nodiscard]] GLFWimage *getHandle() { return &imageHandle; }
  [[nodiscard]] const GLFWimage *getHandle() const { return &imageHandle; }

 private:
  std::vector<std::byte> imagePixels;
  GLFWimage imageHandle{};
};

}  // namespace pf::glfw

#endif  // PF_GLFW_IMAGE_H
