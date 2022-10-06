//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_MONITOR_H
#define PF_GLFW_MONITOR_H

#include <GLFW/glfw3.h>
#include <functional>
#include <pf_glfw/GammaRamp.h>
#include <pf_glfw/VideoMode.h>
#include <pf_glfw/_export.h>
#include <pf_glfw/concepts.h>
#include <pf_glfw/enums/Connection.h>
#include <string>
#include <utility>
#include <vector>

namespace pf::glfw {

class PF_GLFW_EXPORT Monitor {
  friend class Window;

 public:
  Monitor(const Monitor &other);
  Monitor &operator=(const Monitor &other);
  static Monitor Primary();
  static std::vector<Monitor> All();

  [[nodiscard]] Position<int> getPosition() const;
  [[nodiscard]] Area<int> getWorkArea() const;
  [[nodiscard]] Size<int> getPhysicalSize() const;
  [[nodiscard]] Scale getScale() const;
  [[nodiscard]] std::string getName() const;

  [[nodiscard]] VideoMode getCurrentVideoMode() const;
  [[nodiscard]] std::vector<VideoMode> getAvailableVideoModes() const;

  [[nodiscard]] GammaRamp getGammaRamp() const;
  [[nodiscard]] void setGammaRamp(const GammaRamp &gammaRamp) const;

  void setGamma(float gamma);

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

}  // namespace pf::glfw

#endif  // PF_GLFW_MONITOR_H
