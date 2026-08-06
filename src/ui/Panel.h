#pragma once

namespace evosim {
  
struct AppContext;

class Panel {
public:
  explicit Panel(AppContext &context) : m_context(context) {}
  virtual ~Panel() = default;

  virtual void on_attach() {}
  virtual void on_update(float) {}
  virtual void on_gui_render() {}

protected:
  AppContext &m_context;
};

} // namespace evosim