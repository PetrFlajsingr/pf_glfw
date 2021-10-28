//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_SRC_PF_GLFW_GLFW_H
#define PF_GLFW_SRC_PF_GLFW_GLFW_H

#include "Exception.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include <optional>
#include <pf_glfw/_export.h>

namespace pf::glfw {

class PF_GLFW_EXPORT GLFW {
 public:
  GLFW();
  virtual ~GLFW();

  [[nodiscard]] static Version GetVersion();

  [[nodiscard]] const std::shared_ptr<Window> &createWindow(const WindowConfig &config);
  void removeWindow(const std::shared_ptr<Window> &window);

  void setCurrentWindow(const std::shared_ptr<Window> &window);

  void pollEvents();

  void waitEvents();

  void waitEvents(std::chrono::milliseconds timeout);

#ifdef PF_GLFW_OPENGL
  [[nodiscard]] bool isExtensionSupported(const std::string &extension) const;
#endif

#ifdef PF_GLFW_VULKAN
  [[nodiscard]] std::vector<std::string> getRequiredExtensions() const;
#endif

  //glfwSwapInterval
  // glfwGetProcAddress

 private:
  std::vector<std::shared_ptr<Window>> windows;
};

}// namespace pf::glfw

#endif//PF_GLFW_SRC_PF_GLFW_GLFW_H
