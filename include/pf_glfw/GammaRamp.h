//
// Created by xflajs00 on 05.10.2022.
//

#ifndef PF_GLFW_GAMMARAMP_H
#define PF_GLFW_GAMMARAMP_H

#include <cstdint>
#include <vector>

namespace pf::glfw {

template<typename T>
class FixedSizeVector {
 public:
  explicit FixedSizeVector(std::size_t size) : vec(size) {}
  template<std::input_iterator It, std::sentinel_for<It> Sent>
  FixedSizeVector(It &&begin, Sent &&end) : vec(begin, end) {}
  explicit FixedSizeVector(std::initializer_list<T> initializerList) : vec(initializerList) {}

  [[nodiscard]] T &operator[](std::size_t index) { return vec[index]; }
  [[nodiscard]] const T &operator[](std::size_t index) const { return vec[index]; }
  [[nodiscard]] T *data() { return vec.data(); }
  [[nodiscard]] const T *data() const { return vec.data(); }
  [[nodiscard]] std::size_t size() const { return vec.size(); }
  [[nodiscard]] auto begin() { return vec.begin(); }
  [[nodiscard]] auto end() { return vec.end(); }
  [[nodiscard]] auto begin() const { return vec.begin(); }
  [[nodiscard]] auto end() const { return vec.end(); }

 private:
  std::vector<T> vec;
};

struct GammaRamp {
  friend class Monitor;
  inline GammaRamp(FixedSizeVector<std::uint16_t> red, FixedSizeVector<std::uint16_t> green, FixedSizeVector<std::uint16_t> blue)
      : red(std::move(red)), green(std::move(green)), blue(std::move(blue)) {}

 public:
  FixedSizeVector<std::uint16_t> red;
  FixedSizeVector<std::uint16_t> green;
  FixedSizeVector<std::uint16_t> blue;
};

}  // namespace pf::glfw

#endif  //PF_GLFW_GAMMARAMP_H
