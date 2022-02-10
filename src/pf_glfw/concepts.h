//
// Created by xflajs00 on 27.10.2021.
//

#ifndef PF_GLFW_CONCEPTS_H
#define PF_GLFW_CONCEPTS_H

#include <filesystem>
#include <vector>
#include <pf_common/enums.h>
#include <pf_glfw/enums/ButtonState.h>
#include <pf_glfw/enums/Connection.h>
#include <pf_glfw/enums/CursorEntered.h>
#include <pf_glfw/enums/GamepadButton.h>
#include <pf_glfw/enums/JoystickID.h>
#include <pf_glfw/enums/Key.h>
#include <pf_glfw/enums/KeyAction.h>
#include <pf_glfw/enums/ModifierKey.h>
#include <pf_glfw/enums/MouseButton.h>
#include <pf_glfw/structs.h>

namespace pf::glfw {

template<typename F>
concept KeyListener = std::is_invocable_r_v<void, F, Key, KeyAction, Flags<ModifierKey>>;
template<typename F>
concept CharListener = std::is_invocable_r_v<void, F, std::u32string::value_type>;
template<typename F>
concept MouseButtonListener = std::is_invocable_r_v<void, F, MouseButton, ButtonState, Flags<ModifierKey>>;
template<typename F>
concept MouseClickListener = std::is_invocable_r_v<void, F, MouseButton, Flags<ModifierKey>>;
template<typename F>
concept CursorPositionListener = std::is_invocable_r_v<void, F, Position<double>>;
template<typename F>
concept CursorEnterListener = std::is_invocable_r_v<void, F, CursorEntered>;
template<typename F>
concept ScrollListener = std::is_invocable_r_v<void, F, double, double>;
template<typename F>
concept DropListener = std::is_invocable_r_v<void, F, std::vector<std::filesystem::path>>;
template<typename F>
concept ContentScaleListener = std::is_invocable_r_v<void, F, Scale>;
template<typename F>
concept WindowPositionListener = std::is_invocable_r_v<void, F, Position<int>>;
template<typename F>
concept WindowSizeListener = std::is_invocable_r_v<void, F, Size<int>>;
template<typename F>
concept WindowCloseListener = std::is_invocable_r_v<void, F>;
template<typename F>
concept WindowRefreshListener = std::is_invocable_r_v<void, F>;
template<typename F>
concept WindowFocusListener = std::is_invocable_r_v<void, F, bool>;
template<typename F>
concept WindowIconifyListener = std::is_invocable_r_v<void, F, bool>;
template<typename F>
concept WindowMaximizeListener = std::is_invocable_r_v<void, F, bool>;
template<typename F>
concept WindowFramebufferSizeListener = std::is_invocable_r_v<void, F, Size<int>>;
template<typename F>
concept GamepadButtonListener = std::is_invocable_r_v<void, F, GamepadButton, ButtonState>;

template<typename F>
concept MonitorConfigListener = std::is_invocable_r_v<void, F, Connection>;
template<typename F>
concept JoystickConnectionListener = std::is_invocable_r_v<void, F, JoystickID, Connection>;
}  // namespace pf::glfw

#endif  // PF_GLFW_CONCEPTS_H
