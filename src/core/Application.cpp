#include "Application.h"
#include <evosim/Application.h>

#include "imgui.h"
#include "rlImGui.h"
#include <memory>
#include <raylib.h>
#include <stdexcept>
#include <string>
#include <utility>

#include "../ui/Theme.h"
#include "layers/EditorLayer.h"
#include "layers/Layer.h"
#include "layers/SimulationLayer.h"

namespace evosim {

constexpr int k_screen_width = 1920;
constexpr int k_screen_height = 1080;
constexpr const char *k_app_name = "EvoSim";

Application::Application(std::unique_ptr<ISimulation> p_sim)
    : m_context(std::move(p_sim)) {
  if (!m_context.simulation) {
    throw std::invalid_argument("EvoSim requires a simulation instance");
  }
}
Application::~Application() = default;

int Application::run() {
  setup();
  loop();
  end();
  return 0;
}

int run(std::unique_ptr<ISimulation> p_simulation) {
  Application application(std::move(p_simulation));
  return application.run();
}

void Application::setup() {
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(144);

  m_window.init(k_screen_width, k_screen_height, k_app_name);

  rlImGuiBeginInitImGui();

  ImGui::StyleColorsDark();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  const std::string font_directory =
      std::string(EVOSIM_ASSET_DIR) + "/fonts/Inter/static/";
  const std::string bold_font_path = font_directory + "Inter_18pt-Bold.ttf";
  const std::string regular_font_path =
      font_directory + "Inter_18pt-Regular.ttf";

  if (FileExists(bold_font_path.c_str())) {
    m_context.ui.font_bold =
        io.Fonts->AddFontFromFileTTF(bold_font_path.c_str(), 17.0F);
  }

  // main font must be addad in the end in order to rlimgui marged
  // FontAwsomeIcons to it
  if (FileExists(regular_font_path.c_str())) {
    m_context.ui.font_regular =
        io.Fonts->AddFontFromFileTTF(regular_font_path.c_str(), 17.0F);
  } else {
    m_context.ui.font_regular = io.Fonts->AddFontDefault();
  }

  if (!m_context.ui.font_bold) {
    m_context.ui.font_bold = m_context.ui.font_regular;
  }
  io.FontDefault = m_context.ui.font_regular;

  rlImGuiEndInitImGui();

  // apply custom theme
  apply_evosim_theme();

  m_context.simulation->on_attach();

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
  m_layers.clear();
  m_context.simulation->on_detach();
  m_context.simulation.reset();
  rlImGuiShutdown();
  m_window.close();
}

} // namespace evosim
