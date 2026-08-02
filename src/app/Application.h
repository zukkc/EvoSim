#pragma once
#include <memory>
#include <vector>
#include <raylib.h>

#include "Window.h"
#include "./layers/Layer.h"
#include "app/Context.h"

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