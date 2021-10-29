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
#include <pf_glfw/_export.h>
#include <pf_glfw/concepts.h>
#include <pf_glfw/enums/ButtonState.h>
#include <pf_glfw/enums/Connection.h>
#include <pf_glfw/enums/GamepadAxis.h>
#include <pf_glfw/enums/JoystickHatState.h>
#include <pf_glfw/enums/JoystickID.h>
#include <span>
#include <vector>

namespace pf::glfw {

class GamepadState {
 public:
  explicit GamepadState(GLFWgamepadstate *src);

  [[nodiscard]] ButtonState getButtonState(MouseButton button) const;

  [[nodiscard]] float getAxisValue(GamepadAxis axis) const;

 private:
  std::array<ButtonState, 15> buttons{};
  std::array<float, 6> axes{};
};

class PF_GLFW_EXPORT Joystick {
 public:
  explicit Joystick(JoystickID id);

  [[nodiscard]] bool isPresent() const;

  [[nodiscard]] std::vector<float> getAxes() const;

  [[nodiscard]] std::vector<ButtonState> getButtonStates() const;

  [[nodiscard]] std::vector<Flags<JoystickHatState>> getHatStates() const;

  [[nodiscard]] std::string getName() const;

  [[nodiscard]] std::string getGUID() const;

  [[nodiscard]] bool isGamepad() const;

  [[nodiscard]] std::string getGamepadName() const;

  [[nodiscard]] GamepadState getGamepadState() const;

  void updateGamepadMappings(const std::string &gameControllerDbFmt);

  static void SetConnectionCallback(JoystickConnectionListener auto &&callback) {
    OnConnectionChange = std::forward<decltype(callback)>(callback);
  }

 private:
  static inline std::function<void(JoystickID, Connection)> OnConnectionChange = [](auto, auto) {};
  static void joystickGLFWCallback(int id, int event);
  JoystickID id;
};

}// namespace pf::glfw

#endif//PF_GLFW_SRC_PF_GLFW_JOYSTICK_H
