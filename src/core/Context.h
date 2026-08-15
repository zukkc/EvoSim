#pragma once

#include "./simulation/Simulation.h"


struct ImFont;

namespace evosim {

struct UIContext {
  ImFont *font_regular = nullptr;
  ImFont *font_bold = nullptr;
};

struct ViewportContext {
  RenderTexture2D render_texture{};

  int width = 1;
  int height = 1;

  int requested_width = 1;
  int requested_height = 1;

  Camera2D camera{};
};

struct AppContext {
  UIContext ui;
  Simulation simulation;
  ViewportContext viewport;
};

} // namespace evosim
