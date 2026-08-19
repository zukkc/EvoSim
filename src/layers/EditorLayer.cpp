#include "EditorLayer.h"
#include <imgui.h>
#include <memory>
#include <rlImGui.h>

#include "../ui/InspectorPanel.h"
#include "../ui/StatisticsPanel.h"
#include "../ui/ViewportPanel.h"
#include "ui/networkpanel/NetworkPanel.h"

namespace evosim {

EditorLayer::EditorLayer(AppContext &context) : m_context(context) {
  add_panel(std::make_unique<ViewportPanel>(context));
  add_panel(std::make_unique<NetworkPanel>(context));
  add_panel(std::make_unique<InspectorPanel>(context));
  add_panel(std::make_unique<StatisticsPanel>(context));
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

void EditorLayer::add_panel(std::unique_ptr<Panel> p_panel) {
  m_panels.push_back(std::move(p_panel));
  m_panels.back()->on_attach();
}

} // namespace evosim
