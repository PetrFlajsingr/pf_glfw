//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_MONITOR_H
#define PF_GLFW_MONITOR_H

#include <GLFW/glfw3.h>
#include <functional>
#include <pf_glfw/GammaRamp.h>
#include <pf_glfw/VideoMode.h>
#include <pf_glfw/concepts.h>
#include <pf_glfw/enums/Connection.h>
#include <string>
#include <utility>
#include <vector>

namespace pf::glfw {

class Monitor {
  friend class Window;

 public:
  Monitor(const Monitor &other) : monitorHandle(other.monitorHandle) {}
  Monitor &operator=(const Monitor &other) {
    monitorHandle = other.monitorHandle;
    return *this;
  }
  static Monitor Primary() { return Monitor{glfwGetPrimaryMonitor()}; }
  static std::vector<Monitor> All() {
    std::vector<Monitor> monitors;
    int count;
    const auto monitorsRaw = glfwGetMonitors(&count);
    monitors.reserve(count);
    const auto monitorsSpan = std::span{monitorsRaw, static_cast<std::size_t>(count)};
    std::ranges::transform(monitorsSpan, std::back_inserter(monitors), [](const auto monitorPtr) { return Monitor{monitorPtr}; });
    return monitors;
  }

  [[nodiscard]] Position<int> getPosition() const {
    Position<int> result{};
    glfwGetMonitorPos(monitorHandle, &result.x, &result.y);
    return result;
  }
  [[nodiscard]] Area<int> getWorkArea() const {
    Area<int> result{};
    glfwGetMonitorWorkarea(monitorHandle, &result.position.x, &result.position.y, &result.width, &result.height);
    return result;
  }
  [[nodiscard]] Size<int> getPhysicalSize() const {
    Size<int> result{};
    glfwGetMonitorPhysicalSize(monitorHandle, &result.width, &result.height);
    return result;
  }
  [[nodiscard]] Scale getScale() const {
    Scale result{};
    glfwGetMonitorContentScale(monitorHandle, &result.x, &result.y);
    return result;
  }
  [[nodiscard]] std::string getName() const { return glfwGetMonitorName(monitorHandle); }

  [[nodiscard]] VideoMode getCurrentVideoMode() const {
    const auto glfwVidMode = glfwGetVideoMode(monitorHandle);
    return {static_cast<std::uint32_t>(glfwVidMode->width),    static_cast<std::uint32_t>(glfwVidMode->height),
            static_cast<std::uint32_t>(glfwVidMode->redBits),  static_cast<std::uint32_t>(glfwVidMode->greenBits),
            static_cast<std::uint32_t>(glfwVidMode->blueBits), static_cast<std::uint32_t>(glfwVidMode->refreshRate)};
  }
  [[nodiscard]] std::vector<VideoMode> getAvailableVideoModes() const {
    int count{};
    const auto glfwVidModes = glfwGetVideoModes(monitorHandle, &count);
    const auto vidModesSpan = std::span{glfwVidModes, static_cast<std::size_t>(count)};
    std::vector<VideoMode> result{};
    result.reserve(vidModesSpan.size());
    std::ranges::transform(vidModesSpan, std::back_inserter(result), [](const auto &vidMode) {
      return VideoMode{static_cast<std::uint32_t>(vidMode.width),    static_cast<std::uint32_t>(vidMode.height),
                       static_cast<std::uint32_t>(vidMode.redBits),  static_cast<std::uint32_t>(vidMode.greenBits),
                       static_cast<std::uint32_t>(vidMode.blueBits), static_cast<std::uint32_t>(vidMode.refreshRate)};
    });
    return result;
  }

  [[nodiscard]] GammaRamp getGammaRamp() const {
    const auto glfwGammaRamp = glfwGetGammaRamp(monitorHandle);
    const auto redSpan = std::span{glfwGammaRamp->red, glfwGammaRamp->red + glfwGammaRamp->size};
    const auto greenSpan = std::span{glfwGammaRamp->green, glfwGammaRamp->green + glfwGammaRamp->size};
    const auto blueSpan = std::span{glfwGammaRamp->blue, glfwGammaRamp->blue + glfwGammaRamp->size};
    return GammaRamp{{redSpan.begin(), redSpan.end()}, {greenSpan.begin(), greenSpan.end()}, {blueSpan.begin(), blueSpan.end()}};
  }
  void setGammaRamp(const GammaRamp &gammaRamp) const {
    GLFWgammaramp glfWgammaramp;
    glfWgammaramp.size = static_cast<std::uint32_t>(gammaRamp.red.size());
    // these const casts are safe, since glfw is only reading the values
    glfWgammaramp.red = const_cast<std::uint16_t *>(gammaRamp.red.data());
    glfWgammaramp.green = const_cast<std::uint16_t *>(gammaRamp.green.data());
    glfWgammaramp.blue = const_cast<std::uint16_t *>(gammaRamp.blue.data());
    glfwSetGammaRamp(monitorHandle, &glfWgammaramp);
  }

  void setGamma(float gamma) { glfwSetGamma(monitorHandle, gamma); }

  void setMonitorConfigCallback(MonitorConfigListener auto &&callback) {
    monitorConfigCallback = std::forward<decltype(callback)>(callback);
  }

  [[nodiscard]] GLFWmonitor *getHandle() { return monitorHandle; }
  [[nodiscard]] const GLFWmonitor *getHandle() const { return monitorHandle; }

 private:
  explicit Monitor(GLFWmonitor *handle) : monitorHandle(handle) { glfwSetMonitorUserPointer(monitorHandle, this); }

  static void monitorConfigGLFWCallback(GLFWmonitor *monitor, int event) {
    auto self = reinterpret_cast<Monitor *>(glfwGetMonitorUserPointer(monitor));
    self->monitorConfigCallback(static_cast<Connection>(event));
  }
  std::function<void(Connection)> monitorConfigCallback;

  GLFWmonitor *monitorHandle;
};

}  // namespace pf::glfw

#endif  // PF_GLFW_MONITOR_H
