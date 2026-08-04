#include "Application.h"
#include "imgui.h"
#include "rlImGui.h"
#include <memory>
#include <raylib.h>

#include "../ui/Theme.h"
#include "./layers/EditorLayer.h"
#include "./layers/SimulationLayer.h"

namespace evosim {

constexpr int k_screen_width = 1920;
constexpr int k_screen_height = 1080;
constexpr const char *k_app_name = "EvoSim";

void Application::setup() {
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(144);

  m_window.init(k_screen_width, k_screen_height, k_app_name);

  rlImGuiSetup(true);

  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.Fonts->AddFontFromFileTTF(
      "assets/fonts/Inter/static/Inter_18pt-Regular.ttf", 17.0f);

  // apply custom theme
  apply_evosim_theme();

  // add application layers
  m_layers.push_back(std::make_unique<EditorLayer>(m_context));
  m_layers.push_back(std::make_unique<SimulationLayer>(m_context));
}

void Application::loop() {
  while (!WindowShouldClose()) {

    // update layers
    float dt = GetFrameTime();
    for (auto &layer : m_layers) {
      layer->on_update(dt);
    }

    // rendering layers
    BeginDrawing(); // starts drawing anything
    ClearBackground(
        BLACK); // clears background for hole application but not imgui windows

    for (auto &layer : m_layers) {
      layer->on_render();
    }

    // rendering gui in layers
    rlImGuiBegin(); // starts drawing gui
    ImGui::DockSpaceOverViewport(0, NULL,
                                 ImGuiDockNodeFlags_PassthruCentralNode);
    for (auto &layer : m_layers) {
      layer->on_gui_render();
    }
    rlImGuiEnd(); // ends drawing gui

    EndDrawing(); // ends drawing anything
  }
}

void Application::end() {
  rlImGuiShutdown();
  m_window.close();
}

} // namespace evosim