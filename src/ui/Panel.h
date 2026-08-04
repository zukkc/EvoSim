#pragma once

#include "../app/Context.h"

namespace evosim {

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