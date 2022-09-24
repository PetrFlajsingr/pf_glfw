# pf_glfw

A c++20 GLFW wrapper.

### TODOs:
* glfwGetWindowAttrib

Example usage:

```cpp
namespace pglfw = pf::glfw;
auto glfw = pglfw::GLFW{}; // init GLFW
auto window = glfw.createWindow({.width = 1200,
                                 .height = 900,
                                 .title = "OpenGL",
                                 .monitor = pglfw::Monitor::Primary(),
                                 .majorOpenGLVersion = 4,
                                 .minorOpenGLVersion = 6});

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
