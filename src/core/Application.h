#pragma once
#include <memory>
#include <raylib.h>
#include <vector>

#include "Context.h"
#include "Window.h"

namespace evosim {

class ISimulation;
class Layer;

class Application {
public:
  Application(std::unique_ptr<ISimulation> p_sim);
  ~Application();

  int run();

private:
  AppContext m_context;
  Window m_window;
  std::vector<std::unique_ptr<Layer>> m_layers;

  void setup();
  void loop();
  void end();
};

} // namespace evosim
