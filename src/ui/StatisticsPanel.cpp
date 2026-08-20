#include "StatisticsPanel.h"
#include "../core/Context.h"
#include <imgui.h>
#include <raylib.h>
#include <rlImGui.h>

namespace evosim {

void StatisticsPanel::on_gui_render() {
  ImGui::Begin("Statistics");

  ImGui::Text("FPS: %i", GetFPS());
  ImGui::Text("Simulation Speed: %.3fx", m_context.playback.time_scale);

  if (m_context.simulation) {
    m_context.simulation->draw_statistics();
  }

  ImGui::End();
}

} // namespace evosim
