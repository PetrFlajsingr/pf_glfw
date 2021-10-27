//
// Created by xflajs00 on 27.10.2021.
//

#include "Monitor.h"
#include <algorithm>
#include <iterator>
#include <span>

namespace pf::glfw {

Monitor::Monitor(const Monitor &other) : monitorHandle(other.monitorHandle) {}

Monitor &Monitor::operator=(const Monitor &other) {
  monitorHandle = other.monitorHandle;
  return *this;
}

Monitor::Monitor(GLFWmonitor *handle) : monitorHandle(handle) {
  glfwSetMonitorUserPointer(monitorHandle, this);
}

Monitor Monitor::Primary() {
  return Monitor{glfwGetPrimaryMonitor()};
}

std::vector<Monitor> Monitor::All() {
  std::vector<Monitor> monitors;
  int count;
  const auto monitorsRaw = glfwGetMonitors(&count);
  monitors.reserve(count);
  const auto monitorsSpan = std::span{monitorsRaw, static_cast<std::size_t>(count)};
  std::ranges::transform(monitorsSpan, std::back_inserter(monitors), [](const auto monitorPtr) {
    return Monitor{monitorPtr};
  });
  return monitors;
}

MonitorPosition Monitor::getPosition() const {
  MonitorPosition result;
  glfwGetMonitorPos(monitorHandle, &result.x, &result.y);
  return result;
}

MonitorWorkArea Monitor::getWorkArea() const {
  MonitorWorkArea result;
  glfwGetMonitorWorkarea(monitorHandle, &result.position.x, &result.position.y, &result.width, &result.height);
  return result;
}

MonitorSize Monitor::getPhysicalSize() const {
  MonitorSize result;
  glfwGetMonitorPhysicalSize(monitorHandle, &result.width, &result.height);
  return result;
}

MonitorScale Monitor::getScale() const {
  MonitorScale result;
  glfwGetMonitorContentScale(monitorHandle, &result.x, &result.y);
  return result;
}

std::string Monitor::getName() const {
  return glfwGetMonitorName(monitorHandle);
}

void Monitor::setGamma(float gamma) {
  glfwSetGamma(monitorHandle, gamma);
}

GLFWmonitor *Monitor::getHandle() {
  return monitorHandle;
}

const GLFWmonitor *Monitor::getHandle() const {
  return monitorHandle;
}

void Monitor::monitorConfigGLFWCallback(GLFWmonitor *monitor, int event) {
  auto self = reinterpret_cast<Monitor *>(glfwGetMonitorUserPointer(monitor));
  self->monitorConfigCallback(static_cast<Connection>(event));
}

}// namespace pf::glfw