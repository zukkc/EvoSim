#include "ViewportPanel.h"

#include <imgui.h>
#include <rlImGui.h>

void ViewportPanel::on_gui_render() {

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0.0f, 0.0f});

  ImGui::Begin("Viewport", nullptr,
               ImGuiWindowFlags_NoScrollbar |
                   ImGuiWindowFlags_NoScrollWithMouse);

  const ImVec2 available_size = ImGui::GetContentRegionAvail();

  auto &viewport = m_context.viewport;

  viewport.requested_width = std::max(1, static_cast<int>(available_size.x));

  viewport.requested_height = std::max(1, static_cast<int>(available_size.y));

  if (viewport.render_texture.texture.id != 0) {
    const Rectangle source{
        0.0f, 0.0f, static_cast<float>(viewport.render_texture.texture.width),
        -static_cast<float>(viewport.render_texture.texture.height)};

    rlImGuiImageRect(&viewport.render_texture.texture, viewport.width,
                     viewport.height, source);
  }

  ImGui::End();
  ImGui::PopStyleVar();
}