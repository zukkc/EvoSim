#include "InspectorPanel.h"

#include <imgui.h>
#include <rlImGui.h>

void InspectorPanel::on_gui_render() {
  ImGui::Begin("Inspector");

  ImGui::Text("Agent 123: ");

  ImGui::End();
}