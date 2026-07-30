#include <raylib.h>
#include "simulation/World.h"

int main() {
  constexpr int screenWidth = 1920;
  constexpr int screenHeight = 1080;

  InitWindow(screenWidth, screenHeight, "EvoSim");
  SetTargetFPS(144);
  World world;

  while (!WindowShouldClose()) {
    BeginDrawing();
    world.update();
    world.render();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}