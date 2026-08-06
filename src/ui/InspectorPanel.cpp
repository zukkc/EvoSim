#include "InspectorPanel.h"

#include <imgui.h>
#include <rlImGui.h>

namespace evosim {

void InspectorPanel::on_gui_render() {
  ImGui::Begin("Inspector");

  Object *&object = m_context.editor.active_object;

  if (!m_context.simulation.contains_object(object)) {
    object = nullptr;
    ImGui::Text("Inspektor nieaktywny");
  } else {
    object->accept_inspector(*this);
  }

  ImGui::End();
}

void InspectorPanel::inspect(Agent &p_agent) {

  if (p_agent.is_dead()) {
    ImGui::Text("Agent died");
  } else {
    ImGui::Text("Agent ID: %lu", p_agent.get_id());
    ImGui::Text("Energy: %f", p_agent.get_energy());
    ImGui::Text("Agent ID: x=%f, y=%f", p_agent.get_transform().position.x,
                p_agent.get_transform().position.y);
    ImGui::Text("Reproduction treshold of energy: %f",
                p_agent.get_reproduce_threshold());
    ImGui::Text("Reproduction cooldown remening: %f",
                p_agent.get_reproduction_cooldown());
    ImGui::BeginGroup();
    draw_genome_table(p_agent);
    ImGui::EndGroup();
  }
}

void InspectorPanel::inspect(Food &p_food) {

  if (p_food.is_consumed()) {
    ImGui::Text("Food eaten");
  } else {
    ImGui::Text("Food ID: %lu", p_food.get_id());
  }
}

void InspectorPanel::draw_genome_table(Agent &p_agent) {
  const Genome &genome = p_agent.get_genome();

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
