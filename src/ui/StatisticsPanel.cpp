#include "StatisticsPanel.h"
#include "../core/Context.h"
#include "simulation/Simulation.h"
#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

namespace evosim {

void StatisticsPanel::on_gui_render() {
  Simulation &sim = m_context.simulation;
  
  ImGui::Begin("Statistics");

  ImGui::Text("FPS: %i", GetFPS());
  ImGui::Text("Agents: %zu", sim.get_agent_count());
  ImGui::Text("Simulation Speed: %f", sim.get_simulation_speed());

  ImGui::End();
}

} // namespace evosim