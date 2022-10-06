//
// Created by xflajs00 on 27.10.2021.
//

#include "Monitor.h"
#include <algorithm>
#include <iterator>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/transform.hpp>
#include <span>

namespace pf::glfw {

Monitor::Monitor(const Monitor &other) : monitorHandle(other.monitorHandle) {}

Monitor &Monitor::operator=(const Monitor &other) {
  monitorHandle = other.monitorHandle;
  return *this;
}

Monitor::Monitor(GLFWmonitor *handle) : monitorHandle(handle) { glfwSetMonitorUserPointer(monitorHandle, this); }

Monitor Monitor::Primary() { return Monitor{glfwGetPrimaryMonitor()}; }

std::vector<Monitor> Monitor::All() {
  std::vector<Monitor> monitors;
  int count;
  const auto monitorsRaw = glfwGetMonitors(&count);
  monitors.reserve(count);
  const auto monitorsSpan = std::span{monitorsRaw, static_cast<std::size_t>(count)};
  std::ranges::transform(monitorsSpan, std::back_inserter(monitors),
                         [](const auto monitorPtr) { return Monitor{monitorPtr}; });
  return monitors;
}

Position<int> Monitor::getPosition() const {
  Position<int> result{};
  glfwGetMonitorPos(monitorHandle, &result.x, &result.y);
  return result;
}

Area<int> Monitor::getWorkArea() const {
  Area<int> result{};
  glfwGetMonitorWorkarea(monitorHandle, &result.position.x, &result.position.y, &result.width, &result.height);
  return result;
}

Size<int> Monitor::getPhysicalSize() const {
  Size<int> result{};
  glfwGetMonitorPhysicalSize(monitorHandle, &result.width, &result.height);
  return result;
}

Scale Monitor::getScale() const {
  Scale result{};
  glfwGetMonitorContentScale(monitorHandle, &result.x, &result.y);
  return result;
}

std::string Monitor::getName() const { return glfwGetMonitorName(monitorHandle); }

VideoMode Monitor::getCurrentVideoMode() const {
  const auto glfwVidMode = glfwGetVideoMode(monitorHandle);
  return {static_cast<std::uint32_t>(glfwVidMode->width),    static_cast<std::uint32_t>(glfwVidMode->height),
          static_cast<std::uint32_t>(glfwVidMode->redBits),  static_cast<std::uint32_t>(glfwVidMode->greenBits),
          static_cast<std::uint32_t>(glfwVidMode->blueBits), static_cast<std::uint32_t>(glfwVidMode->refreshRate)};
}

std::vector<VideoMode> Monitor::getAvailableVideoModes() const {
  int count{};
  const auto glfwVidModes = glfwGetVideoModes(monitorHandle, &count);
  return std::span{glfwVidModes, static_cast<std::size_t>(count)} | ranges::views::transform([](const auto &vidMode) {
           return VideoMode{
               static_cast<std::uint32_t>(vidMode.width),    static_cast<std::uint32_t>(vidMode.height),
               static_cast<std::uint32_t>(vidMode.redBits),  static_cast<std::uint32_t>(vidMode.greenBits),
               static_cast<std::uint32_t>(vidMode.blueBits), static_cast<std::uint32_t>(vidMode.refreshRate)};
         })
      | ranges::to_vector;
}

GammaRamp Monitor::getGammaRamp() const {
  const auto glfwGammaRamp = glfwGetGammaRamp(monitorHandle);
  const auto redSpan = std::span{glfwGammaRamp->red, glfwGammaRamp->red + glfwGammaRamp->size};
  const auto greenSpan = std::span{glfwGammaRamp->green, glfwGammaRamp->green + glfwGammaRamp->size};
  const auto blueSpan = std::span{glfwGammaRamp->blue, glfwGammaRamp->blue + glfwGammaRamp->size};
  return GammaRamp{{redSpan.begin(), redSpan.end()},
                   {greenSpan.begin(), greenSpan.end()},
                   {blueSpan.begin(), blueSpan.end()}};
}

void Monitor::setGammaRamp(const GammaRamp &gammaRamp) const {
  GLFWgammaramp glfWgammaramp;
  glfWgammaramp.size = static_cast<std::uint32_t>(gammaRamp.red.size());
  // these const casts are safe, since glfw is only reading the values
  glfWgammaramp.red = const_cast<std::uint16_t *>(gammaRamp.red.data());
  glfWgammaramp.green = const_cast<std::uint16_t *>(gammaRamp.green.data());
  glfWgammaramp.blue = const_cast<std::uint16_t *>(gammaRamp.blue.data());
  glfwSetGammaRamp(monitorHandle, &glfWgammaramp);
}

void Monitor::setGamma(float gamma) { glfwSetGamma(monitorHandle, gamma); }

GLFWmonitor *Monitor::getHandle() { return monitorHandle; }

const GLFWmonitor *Monitor::getHandle() const { return monitorHandle; }
void Monitor::monitorConfigGLFWCallback(GLFWmonitor *monitor, int event) {
  auto self = reinterpret_cast<Monitor *>(glfwGetMonitorUserPointer(monitor));
  self->monitorConfigCallback(static_cast<Connection>(event));
}

}  // namespace pf::glfw
