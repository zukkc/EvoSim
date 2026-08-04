#pragma once
#include <memory>
#include <raylib.h>
#include <vector>

#include "./layers/Layer.h"
#include "Window.h"
#include "app/Context.h"

namespace evosim {

class Application {
public:
  void setup();
  void loop();
  void end();

private:
  AppContext m_context;
  Window m_window;
  std::vector<std::unique_ptr<Layer>> m_layers;
};

} // namespace evosim