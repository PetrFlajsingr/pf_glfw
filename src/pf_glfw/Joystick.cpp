//
// Created by xflajs00 on 28.10.2021.
//

#include "Joystick.h"
#include "Exception.h"

namespace pf::glfw {

GamepadState::GamepadState(GLFWgamepadstate *src) {
  buttons[0] = src->buttons[0] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  buttons[1] = src->buttons[1] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  buttons[2] = src->buttons[2] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  buttons[3] = src->buttons[3] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  buttons[4] = src->buttons[4] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  buttons[5] = src->buttons[5] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  buttons[6] = src->buttons[6] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  buttons[7] = src->buttons[7] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  buttons[8] = src->buttons[8] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  buttons[9] = src->buttons[9] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  buttons[10] = src->buttons[10] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  buttons[11] = src->buttons[11] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  buttons[12] = src->buttons[12] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  buttons[13] = src->buttons[13] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  buttons[14] = src->buttons[14] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  axes[0] = src->axes[0];
  axes[1] = src->axes[1];
  axes[2] = src->axes[2];
  axes[3] = src->axes[3];
  axes[4] = src->axes[4];
  axes[5] = src->axes[5];
}

ButtonState GamepadState::getButtonState(MouseButton button) const {
  return buttons[static_cast<int>(button)];
}

float GamepadState::getAxisValue(GamepadAxis axis) const {
  return axes[static_cast<int>(axis)];
}

Joystick::Joystick(JoystickID id) : id(id) {
  glfwSetJoystickUserPointer(static_cast<int>(id), this);
}

bool Joystick::isPresent() const {
  return glfwJoystickPresent(static_cast<int>(id));
}

std::vector<float> Joystick::getAxes() const {
  int count;
  auto axes = glfwGetJoystickAxes(static_cast<int>(id), &count);
  return {axes, axes + count};
}

std::vector<ButtonState> Joystick::getButtonStates() const {
  int count;
  auto states = glfwGetJoystickButtons(static_cast<int>(id), &count);
  const auto statesSpan = std::span{states, states + count};
  std::vector<ButtonState> result;
  result.reserve(count);
  std::ranges::transform(statesSpan, std::back_inserter(result), [](const auto state) {
    return state == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
  });
  return result;
}

std::vector<Flags<JoystickHatState>> Joystick::getHatStates() const {
  int count;
  auto states = glfwGetJoystickHats(static_cast<int>(id), &count);
  const auto statesSpan = std::span{states, states + count};
  std::vector<Flags<JoystickHatState>> result;
  result.reserve(count);
  std::ranges::transform(statesSpan, std::back_inserter(result), [](const auto state) {
    return static_cast<JoystickHatState>(state);
  });
  return result;
}

std::string Joystick::getName() const {
  return glfwGetJoystickName(static_cast<int>(id));
}

std::string Joystick::getGUID() const {
  return glfwGetJoystickGUID(static_cast<int>(id));
}

bool Joystick::isGamepad() const {
  return glfwJoystickIsGamepad(static_cast<int>(id)) == GLFW_TRUE;
}

std::string Joystick::getGamepadName() const {
  return glfwGetGamepadName(static_cast<int>(id));
}

GamepadState Joystick::getGamepadState() const {
  GLFWgamepadstate native;
  glfwGetGamepadState(static_cast<int>(id), &native);
  return GamepadState{&native};
}

void Joystick::updateGamepadMappings(const std::string &gameControllerDbFmt) {
  if (glfwUpdateGamepadMappings(gameControllerDbFmt.c_str()) != GLFW_TRUE) {
    details::getLastErrorAndThrow();
  }
}

void Joystick::joystickGLFWCallback(int id, int event) {
  Joystick::OnConnectionChange(static_cast<JoystickID>(id), static_cast<Connection>(event));
}
}// namespace pf::glfw