#include "EditorLayer.h"
#include <imgui.h>
#include <memory>
#include <rlImGui.h>

#include "../ui/ViewportPanel.h"
#include "../ui/InspectorPanel.h"
#include "../ui/StatisticsPanel.h"

EditorLayer::EditorLayer(AppContext &context) : m_context(context) {
  m_panels.push_back(std::make_unique<ViewportPanel>(context));
  m_panels.push_back(std::make_unique<InspectorPanel>(context));
  m_panels.push_back(std::make_unique<StatisticsPanel>(context));
}

void EditorLayer::on_gui_render() {
  for (auto &panel : m_panels) {
    panel->on_gui_render();
  }
}