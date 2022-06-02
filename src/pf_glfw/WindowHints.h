//
// Created by xflajs00 on 28.10.2021.
//

#ifndef PF_GLFW_WINDOWHINTS_H
#define PF_GLFW_WINDOWHINTS_H

#include <pf_glfw/constants.h>
#include <pf_glfw/enums/ContextCreationAPI.h>
#include <pf_glfw/enums/ContextReleaseBehavior.h>
#include <pf_glfw/enums/ContextRobustness.h>
#include <pf_glfw/enums/OpenGLProfile.h>
#include <string>

namespace pf::glfw {

class WindowHints {
  friend class Window;

 public:
  bool resizable = true;
  bool visible = true;
  bool decorated = true;
  bool focused = true;
  bool autoIconify = true;
  bool floating = false;
  bool maximized = false;
  bool centerCursor = true;
  bool transparentFramebuffer = false;
  bool focusOnShow = true;
  bool scaleToMonitor = false;

  int redBits = 8;
  int greenBits = 8;
  int blueBits = 8;
  int alphaBits = 8;
  int depthBits = 24;
  int stencilBits = 8;
  int accumRedBits = 0;
  int accumGreenBits = 0;
  int accumBlueBits = 0;
  int accumAlphaBits = 0;

  int auxBuffers = 0;
  int samples = 0;
  int refreshRate = DontCare;
  bool stereo = false;
  bool srgbCapable = false;
  bool doubleBuffer = true;

  ContextCreationAPI contextCreationApi = ContextCreationAPI::Native;
  ContextRobustness contextRobustness = ContextRobustness::No;
  ContextReleaseBehavior contextReleaseBehavior = ContextReleaseBehavior::Any;
  bool forwardCompat = false;
  bool debugContext = false;
  OpenGLProfile openglProfile = OpenGLProfile::Any;

  bool cocoaRetinaFramebuffer = true;
  std::string cocoaFrameName{};
  bool cocoaGraphicsSwitching = false;

  std::string x11ClassName{};
  std::string x11InstanceName{};

 private:
  void apply(bool isOpenGl) const;
};

}  // namespace pf::glfw
#endif  // PF_GLFW_WINDOWHINTS_H
