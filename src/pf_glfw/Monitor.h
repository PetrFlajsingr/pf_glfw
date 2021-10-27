//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_SRC_PF_GLFW_MONITOR_H
#define PF_GLFW_SRC_PF_GLFW_MONITOR_H

#include <GLFW/glfw3.h>
#include <functional>
#include <pf_glfw/concepts.h>
#include <pf_glfw/enums/Connection.h>
#include <string>
#include <vector>
#include <pf_glfw/_export.h>

namespace pf::glfw {

class PF_GLFW_EXPORT Monitor {
 public:
  Monitor(const Monitor &other);
  Monitor &operator=(const Monitor &other);
  static Monitor Primary();
  static std::vector<Monitor> All();

  [[nodiscard]] MonitorPosition getPosition() const;
  [[nodiscard]] MonitorWorkArea getWorkArea() const;
  [[nodiscard]] MonitorSize getPhysicalSize() const;
  [[nodiscard]] MonitorScale getScale() const;
  [[nodiscard]] std::string getName() const;

  void setGamma(float gamma);
  // glfwGetGammaRamp
  // glfwSetGammaRamp
  // glfwGetVideoModes
  // glfwGetVideoMode

  void setMonitorConfigCallback(MonitorConfigListener auto &&callback) {
    monitorConfigCallback = std::forward<decltype(callback)>(callback);
  }

  [[nodiscard]] GLFWmonitor *getHandle();
  [[nodiscard]] const GLFWmonitor *getHandle() const;

 private:
  explicit Monitor(GLFWmonitor *handle);

  static void monitorConfigGLFWCallback(GLFWmonitor *monitor, int event);
  std::function<void(Connection)> monitorConfigCallback;

  GLFWmonitor *monitorHandle;
};

}// namespace pf::glfw

#endif//PF_GLFW_SRC_PF_GLFW_MONITOR_H
