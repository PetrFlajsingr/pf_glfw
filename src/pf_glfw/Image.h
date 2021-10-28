//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_SRC_PF_GLFW_IMAGE_H
#define PF_GLFW_SRC_PF_GLFW_IMAGE_H

#include <GLFW/glfw3.h>
#include <memory>
#include <pf_glfw/_export.h>
#include <span>
#include <vector>

namespace pf::glfw {

// gotta be RGBA
class PF_GLFW_EXPORT Image {
 public:
  Image(std::size_t width, std::size_t height, std::span<std::byte> pixels);

  [[nodiscard]] std::size_t getWidth() const;
  [[nodiscard]] std::size_t getHeight() const;
  [[nodiscard]] std::span<const std::byte> getPixels() const;

  [[nodiscard]] GLFWimage *getHandle();
  [[nodiscard]] const GLFWimage *getHandle() const;

 private:
  std::vector<std::byte> imagePixels;
  std::shared_ptr<GLFWimage> imageHandle;
};

}// namespace pf::glfw

#endif//PF_GLFW_SRC_PF_GLFW_IMAGE_H
