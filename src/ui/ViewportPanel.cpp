#include "ViewportPanel.h"

#include <algorithm>
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

    handle_input(ImGui::IsItemHovered());
  }

  ImGui::End();
  ImGui::PopStyleVar();
}

void ViewportPanel::handle_input(bool p_is_viewport_hovered) {
  constexpr ImGuiMouseButton pan_button = ImGuiMouseButton_Left;

  Camera2D &camera = m_context.viewport.camera;

  if (p_is_viewport_hovered) {
    const float wheel = ImGui::GetIO().MouseWheel;

    if (wheel != 0.0f) {
      constexpr float zoom_step = 0.15f;

      camera.zoom *= 1.0f + wheel * zoom_step;
      camera.zoom = std::clamp(camera.zoom, 0.1f, 20.0f);
    }
  }

  if (p_is_viewport_hovered && ImGui::IsMouseClicked(pan_button)) {
    m_is_panning = true;
  }

  if (!ImGui::IsMouseDown(pan_button)) {
    m_is_panning = false;
  }

  if (m_is_panning) {
    const ImVec2 delta = ImGui::GetIO().MouseDelta;

    camera.target.x -= delta.x / camera.zoom;
    camera.target.y -= delta.y / camera.zoom;

    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
  }
}