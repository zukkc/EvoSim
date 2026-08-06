#pragma once
#include <memory>
#include <raylib.h>
#include <vector>

#include "Window.h"
#include "Context.h"

namespace evosim {
  
class Layer;

class Application {
public:
  Application();
  ~Application();

  void setup();
  void loop();
  void end();

private:
  AppContext m_context;
  Window m_window;
  std::vector<std::unique_ptr<Layer>> m_layers;
};

} // namespace evosim
