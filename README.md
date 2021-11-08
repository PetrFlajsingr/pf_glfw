# pf_glfw

A c++20 GLFW wrapper.

### TODOs:
* more glfw error checks
* vulkan
* glfwGetWindowAttrib

Example usage:

```cpp
auto glfw = pf::glfw::GLFW{}; // init GLFW
auto window = glfw.createWindow({.width = 1200,
                                 .height = 900,
                                 .title = "OpenGL",
                                 .monitor = pf::glfw::Monitor::Primary(),
                                 .majorOpenGLVersion = 4,
                                 .minorOpenGLVersion = 6});

window->setMouseClickCallback([](pf::glfw::MouseButton button, pf::Flags<pf::glfw::ModifierKey> mods) {
  std::cout << "Button pressed";
  if (mods & pf::glfw::ModifierKey::Shift) {
    std::cout << "with shift";
  }
});

std::vector<std::byte> imageData = loadCursorImage();
pf::glfw::Image cursorImage{std::span{imageData.begin(), imageData.end()}};
pf::glfw::Cursor customCursor{cursorImage};
window->setCursor(customCursor);

pf::glfw::Image iconImage = loadIconImage();
window->setIcon{iconImage};

while(!window->shouldClose()) {
  // render your stuff
  window->swapBuffers();
  glfw.pollEvents();
}
```