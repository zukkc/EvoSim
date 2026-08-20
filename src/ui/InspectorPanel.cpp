#include "InspectorPanel.h"
#include "../core/Context.h"
#include "nodegraph/Node.h"
#include <imgui.h>
#include <rlImGui.h>

namespace evosim {

void InspectorPanel::on_gui_render() {
  ImGui::Begin("Inspector");

  Object *object = m_context.get_selected_object();

  if (!object) {
    ImGui::Text("Inspektor nieaktywny");
  } else if (auto *node = dynamic_cast<Node *>(object)) {
    draw_node_inspector(*node);
  } else {
    m_context.simulation->draw_inspector(*object);
  }

  ImGui::End();
}

void InspectorPanel::draw_node_inspector(Node &p_node) {
  ImGui::Text("ID: %lu", p_node.get_id());
  ImGui::Text("Nazwa: %s", p_node.get_name().c_str());
  ImGui::Text("Inputs: %zu", p_node.get_inputs().size());
  ImGui::Text("Outputs: %zu", p_node.get_outputs().size());
}
} // namespace evosim
