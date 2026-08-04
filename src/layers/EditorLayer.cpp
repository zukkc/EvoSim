#include "EditorLayer.h"
#include <imgui.h>
#include <memory>
#include <rlImGui.h>

#include "../ui/InspectorPanel.h"
#include "../ui/StatisticsPanel.h"
#include "../ui/ViewportPanel.h"

namespace evosim {

EditorLayer::EditorLayer(AppContext &context) : m_context(context) {
  m_panels.push_back(std::make_unique<ViewportPanel>(context));
  m_panels.push_back(std::make_unique<InspectorPanel>(context));
  m_panels.push_back(std::make_unique<StatisticsPanel>(context));
}

void EditorLayer::on_update(float p_dt) {
  for (auto &panel : m_panels) {
    panel->on_update(p_dt);
  }
}

void EditorLayer::on_gui_render() {
  for (auto &panel : m_panels) {
    panel->on_gui_render();
  }
}

} // namespace evosim