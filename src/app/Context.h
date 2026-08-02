#pragma once

#include "./simulation/Simulation.h"

struct ViewportContext {
  RenderTexture2D render_texture{};

  int width = 1;
  int height = 1;

  int requested_width = 1;
  int requested_height = 1;

  Camera2D camera{};
};

struct AppContext {
  Simulation simulation;
  ViewportContext viewport;
};
