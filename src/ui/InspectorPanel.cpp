#include "InspectorPanel.h"

#include <imgui.h>
#include <rlImGui.h>

namespace evosim {

void InspectorPanel::on_update(float) {
  m_active = m_context.simulation.get_active_in_inspector();
}

void InspectorPanel::on_gui_render() {
  ImGui::Begin("Inspector");

  if (m_active == nullptr || m_active->is_dead()) {
    ImGui::Text("There is no active Agent");
  } else {
    ImGui::Text("Agent ID: %i", m_active->get_id());
    ImGui::Text("Energy: %f", m_active->get_energy());
    ImGui::Text("Agent ID: x=%f, y=%f", m_active->get_position().x,
                m_active->get_position().y);
    ImGui::Text("Reproduction treshold of energy: %f",
                m_active->get_reproduce_threshold());
    ImGui::Text("Reproduction cooldown remening: %f",
                m_active->get_reproduction_cooldown());
    ImGui::BeginGroup();
    draw_genome_table();
    ImGui::EndGroup();
  }

  ImGui::End();
}

void InspectorPanel::draw_genome_table() {
  const Genome &genome = m_active->get_genome();

  constexpr std::array input_names{
      "Direction to food",
      "Distance to food",
      "Energy",
      "Distance to border",
      "null",
      "bias",
  };

  constexpr std::size_t input_count = input_names.size();
  constexpr std::size_t neuron_count = 2;

  static_assert(Genome{}.size() == input_count * neuron_count,
                "Genome size does not match network layout");

  constexpr ImGuiTableFlags flags = ImGuiTableFlags_Borders |
                                    ImGuiTableFlags_RowBg |
                                    ImGuiTableFlags_SizingStretchProp;

  if (ImGui::BeginTable("Genome", 3, flags)) {
    ImGui::TableSetupColumn("Input", ImGuiTableColumnFlags_WidthStretch, 2.0f);

    ImGui::TableSetupColumn("Direction", ImGuiTableColumnFlags_WidthStretch,
                            1.0f);

    ImGui::TableSetupColumn("Speed", ImGuiTableColumnFlags_WidthStretch, 1.0f);

    ImGui::TableHeadersRow();

    for (std::size_t input = 0; input < input_count; ++input) {
      ImGui::TableNextRow();

      ImGui::TableSetColumnIndex(0);
      ImGui::TextUnformatted(input_names[input]);

      ImGui::TableSetColumnIndex(1);
      ImGui::Text("%.3f", genome[input]);

      ImGui::TableSetColumnIndex(2);
      ImGui::Text("%.3f", genome[input_count + input]);
    }

    ImGui::EndTable();
  }
}

} // namespace evosim