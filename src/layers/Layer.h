#pragma once

namespace evosim {

class Layer {
public:
  virtual ~Layer() = default;

  virtual void on_attach() {}
  virtual void on_update(float) {}
  virtual void on_render() {}
  virtual void on_gui_render() {}
};

} // namespace evosim