#include "ViewportPanel.h"
#include "raylib.h"
#include "simulation/Agent.h"

#include <algorithm>
#include <imgui.h>
#include <rlImGui.h>

namespace evosim {

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
  const ImVec2 image_min = ImGui::GetItemRectMin();
  const ImVec2 image_size = ImGui::GetItemRectSize();

  if (!p_is_viewport_hovered || image_size.x <= 0.0f || image_size.y <= 0.0f) {
    return;
  }

  ViewportContext &viewport = m_context.viewport;
  Camera2D &camera = viewport.camera;

  constexpr ImGuiMouseButton pan_button = ImGuiMouseButton_Right;
  constexpr ImGuiMouseButton click_button = ImGuiMouseButton_Left;
  const ImVec2 mouse = ImGui::GetIO().MousePos;
  const float wheel = ImGui::GetIO().MouseWheel;

  const float local_x = mouse.x - image_min.x;
  const float local_y = mouse.y - image_min.y;

  const Vector2 texture_mouse_position{
      local_x * static_cast<float>(viewport.render_texture.texture.width) /
          image_size.x,

      local_y * static_cast<float>(viewport.render_texture.texture.height) /
          image_size.y};

  Vector2 mouse_world_position =
      GetScreenToWorld2D(texture_mouse_position, camera);

  // ZOOMING
  if (wheel != 0.0f) {
    constexpr float zoom_speed = 0.15f;

    camera.zoom *= std::exp(wheel * zoom_speed);
    camera.zoom = std::clamp(camera.zoom, 0.1f, 20.0f);

    const Vector2 mouse_position_in_world_after_zoom =
        GetScreenToWorld2D(texture_mouse_position, camera);

    camera.target.x +=
        mouse_world_position.x - mouse_position_in_world_after_zoom.x;
    camera.target.y +=
        mouse_world_position.y - mouse_position_in_world_after_zoom.y;

    // updating mouse position in world after zoom
    mouse_world_position = mouse_position_in_world_after_zoom;
  }
  // =======

  // PANNING
  if (p_is_viewport_hovered && ImGui::IsMouseClicked(pan_button)) {
    m_is_panning = true;
  }

  if (!ImGui::IsMouseDown(pan_button)) {
    m_is_panning = false;
  }

  if (m_is_panning) {
    const ImVec2 mouse_delta = ImGui::GetIO().MouseDelta;
    camera.target.x -= mouse_delta.x / camera.zoom;
    camera.target.y -= mouse_delta.y / camera.zoom;

    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
  }
  // =======

  // CLICKING
  if (p_is_viewport_hovered && ImGui::IsMouseClicked(click_button)) {
    Simulation &simulation = m_context.simulation;
    Object *found = simulation.find_object_at(mouse_world_position);
    simulation.set_active_object(found);
    m_context.editor.active_object = found;
  }
  // =======
}

} // namespace evosim