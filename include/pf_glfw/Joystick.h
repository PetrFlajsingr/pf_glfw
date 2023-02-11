//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_SRC_PF_GLFW_JOYSTICK_H
#define PF_GLFW_SRC_PF_GLFW_JOYSTICK_H

#include <GLFW/glfw3.h>
#include <algorithm>
#include <functional>
#include <iterator>
#include <pf_common/enums.h>
#include <pf_glfw/concepts.h>
#include <pf_glfw/enums/ButtonState.h>
#include <pf_glfw/enums/Connection.h>
#include <pf_glfw/enums/GamepadAxis.h>
#include <pf_glfw/enums/GamepadButton.h>
#include <pf_glfw/enums/JoystickHatState.h>
#include <pf_glfw/enums/JoystickID.h>
#include <span>
#include <string>
#include <utility>
#include <vector>

namespace pf::glfw {

class GamepadState {
 public:
  explicit GamepadState(GLFWgamepadstate *src) {
    buttons[0] = (src->buttons[0] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up);
    buttons[1] = (src->buttons[1] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up);
    buttons[2] = (src->buttons[2] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up);
    buttons[3] = (src->buttons[3] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up);
    buttons[4] = (src->buttons[4] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up);
    buttons[5] = (src->buttons[5] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up);
    buttons[6] = (src->buttons[6] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up);
    buttons[7] = (src->buttons[7] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up);
    buttons[8] = (src->buttons[8] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up);
    buttons[9] = (src->buttons[9] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up);
    buttons[10] = (src->buttons[10] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up);
    buttons[11] = (src->buttons[11] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up);
    buttons[12] = (src->buttons[12] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up);
    buttons[13] = (src->buttons[13] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up);
    buttons[14] = (src->buttons[14] == GLFW_PRESS ? ButtonState::Down : ButtonState::Up);
    axes[0] = src->axes[0];
    axes[1] = src->axes[1];
    axes[2] = src->axes[2];
    axes[3] = src->axes[3];
    axes[4] = src->axes[4];
    axes[5] = src->axes[5];
  }

  [[nodiscard]] ButtonState getButtonState(GamepadButton button) const { return buttons[static_cast<int>(button)]; }

  [[nodiscard]] float getAxisValue(GamepadAxis axis) const { return axes[static_cast<int>(axis)]; }

 private:
  std::array<ButtonState, 15> buttons{};
  std::array<float, 6> axes{};
};

class Joystick {
 public:
  explicit Joystick(JoystickID id) { glfwSetJoystickUserPointer(static_cast<int>(id), this); }

  [[nodiscard]] bool isPresent() const { return glfwJoystickPresent(static_cast<int>(id)); }

  [[nodiscard]] std::vector<float> getAxes() const {
    int count;
    auto axes = glfwGetJoystickAxes(static_cast<int>(id), &count);
    return {axes, axes + count};
  }

  [[nodiscard]] std::vector<ButtonState> getButtonStates() const {
    int count;
    auto states = glfwGetJoystickButtons(static_cast<int>(id), &count);
    const auto statesSpan = std::span{states, states + count};
    std::vector<ButtonState> result;
    result.reserve(count);
    std::ranges::transform(statesSpan, std::back_inserter(result),
                           [](const auto state) { return state == GLFW_PRESS ? ButtonState::Down : ButtonState::Up; });
    return result;
  }

  [[nodiscard]] std::vector<Flags<JoystickHatState>> getHatStates() const {
    int count;
    auto states = glfwGetJoystickHats(static_cast<int>(id), &count);
    const auto statesSpan = std::span{states, states + count};
    std::vector<Flags<JoystickHatState>> result;
    result.reserve(count);
    std::ranges::transform(statesSpan, std::back_inserter(result), [](const auto state) { return static_cast<JoystickHatState>(state); });
    return result;
  }

  [[nodiscard]] std::string getName() const { return glfwGetJoystickName(static_cast<int>(id)); }

  [[nodiscard]] std::string getGUID() const { return glfwGetJoystickGUID(static_cast<int>(id)); }

  [[nodiscard]] JoystickID getID() const { return id; }

  [[nodiscard]] bool isGamepad() const { return glfwJoystickIsGamepad(static_cast<int>(id)) == GLFW_TRUE; }

  [[nodiscard]] std::string getGamepadName() const { return glfwGetGamepadName(static_cast<int>(id)); }

  [[nodiscard]] GamepadState getGamepadState() const {
    GLFWgamepadstate native;
    glfwGetGamepadState(static_cast<int>(id), &native);
    return GamepadState{&native};
  }

  void updateGamepadMappings(const std::string &gameControllerDbFmt) {
    if (glfwUpdateGamepadMappings(gameControllerDbFmt.c_str()) != GLFW_TRUE) { details::getLastErrorAndThrow(); }
  }

  /*void setGamepadButtonCallback(GamepadButtonListener auto &&callback) {
    gamepadButtonCallback = std::forward<decltype(callback)>(callback);
    // TODO
  }*/

  static void SetConnectionCallback(JoystickConnectionListener auto &&callback) {
    OnConnectionChange = std::forward<decltype(callback)>(callback);
    glfwSetJoystickCallback(joystickGLFWCallback);
  }

 private:
  static inline std::function<void(JoystickID, Connection)> OnConnectionChange = [](auto, auto) {};
  static void joystickGLFWCallback(int id, int event) {
    Joystick::OnConnectionChange(static_cast<JoystickID>(id), static_cast<Connection>(event));
  }

  // std::function<void(GamepadButton, ButtonState)> gamepadButtonCallback = [](auto, auto) {};

  JoystickID id;
};

}  // namespace pf::glfw

#endif  // PF_GLFW_SRC_PF_GLFW_JOYSTICK_H
