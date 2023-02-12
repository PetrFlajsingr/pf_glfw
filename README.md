# pf_glfw

A c++20 GLFW wrapper.

Example usage:

```cpp
namespace pglfw = pf::glfw;
// init GLFW
auto glfwCreateResult = pglfw::GLFW::Create();
if (!glfwCreateResult.has_value()) {
  const auto error = glfwCreateResult.error();
  print("Error '{}', reason: '{}'", error.error, error.description);
  std::abort();
}
auto glfw = std::move(*glfwCreateResult);

auto windowCreateResult = glfw.createWindow({.width = 1200,
                                             .height = 900,
                                             .title = "OpenGL",
                                             .monitor = pglfw::Monitor::Primary(),
                                             .majorOpenGLVersion = 4,
                                             .minorOpenGLVersion = 6});
if (!windowCreateResult.has_value()) {
  const auto error = windowCreateResult.error();
  print("Error '{}', reason: '{}'", error.error, error.description);
  std::abort();
}
auto window = std::move(*windowCreateResult);

// new callback can cache the old one and call it when the event is triggered
constexpr bool callPreviousMouseButtonCallback = true;
window->setMouseButtonCallback([](pglfw::MouseButton button, 
                                  pglfw::ButtonState state, 
                                  pf::Flags<pglfw::ModifierKey> mods) {
  switch (state) {
    case pglfw::ButtonState::Down: std::cout << "Button down"; break;
    case pglfw::ButtonState::Up: std::cout << "Button up"; break;
  }
  if (mods & pglfw::ModifierKey::Shift) {
    std::cout << " with shift";
  }
}, callPreviousMouseButtonCallback);

std::vector<std::byte> imageData = loadCursorImage();
pglfw::Image cursorImage{std::span{imageData.begin(), imageData.end()}};
pglfw::Cursor customCursor{cursorImage};
window->setCursor(customCursor);

pglfw::Image iconImage = loadIconImage();
window->setIcon{iconImage};

while(!window->shouldClose()) {
  // render your stuff
  window->swapBuffers();
  glfw.pollEvents();
}
```
