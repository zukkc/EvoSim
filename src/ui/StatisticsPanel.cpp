#include "StatisticsPanel.h"
#include "../core/Context.h"
#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

namespace evosim {

void StatisticsPanel::on_gui_render() {
  ImGui::Begin("Statistics");

  ImGui::Text("FPS: %i", GetFPS());
  ImGui::Text("Agents: %zu", m_context.simulation.get_agent_count());

  ImGui::End();
}

} // namespace evosim