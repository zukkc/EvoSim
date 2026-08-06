#include "NeuralPanel.h"
#include "../core/Context.h"
#include "../simulation/neural/Genome.h"
#include "simulation/Simulation.h"
#include <imgui.h>
#include <rlImGui.h>

namespace evosim {

void NeuralPanel::on_gui_render() {
  ImGui::Begin("Inspector");

  Simulation &sim = m_context.simulation;
  Object *object = sim.get_active_object();

  if (!sim.contains_object(object)) {
    object = nullptr;
    ImGui::Text("Edytor nieaktywny");
  } else {

  }

  ImGui::End();
}

} // namespace evosim
