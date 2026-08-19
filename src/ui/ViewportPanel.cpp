#include "ViewportPanel.h"
#include "../core/Context.h"
#include "extras/IconsFontAwesome6.h"
#include "imgui.h"
#include "raylib.h"
#include "simulation/Simulation.h"

#include <algorithm>
#include <cmath>
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

    const ImVec2 image_min = ImGui::GetItemRectMin();
    const ImVec2 image_max = ImGui::GetItemRectMax();
    const ImVec2 image_size = ImGui::GetItemRectSize();

    const bool viewport_hovered = ImGui::IsItemHovered();
    const bool controls_hovered = draw_viewport_controls(image_min, image_max);

    if (viewport_hovered && !controls_hovered) {
      handle_input(true, image_min, image_size);
    };
  }

  ImGui::End();
  ImGui::PopStyleVar();
}

void ViewportPanel::handle_input(bool p_is_viewport_hovered,
                                 const ImVec2 &p_image_min,
                                 const ImVec2 &p_image_size) {

  if (!p_is_viewport_hovered || p_image_size.x <= 0.0f ||
      p_image_size.y <= 0.0f) {
    return;
  }

  ViewportContext &viewport = m_context.viewport;
  Camera2D &camera = viewport.camera;

  constexpr ImGuiMouseButton pan_button = ImGuiMouseButton_Right;
  constexpr ImGuiMouseButton click_button = ImGuiMouseButton_Left;
  const ImVec2 mouse = ImGui::GetIO().MousePos;
  const float wheel = ImGui::GetIO().MouseWheel;

  const float local_x = mouse.x - p_image_min.x;
  const float local_y = mouse.y - p_image_min.y;

  const Vector2 texture_mouse_position{
      local_x * static_cast<float>(viewport.render_texture.texture.width) /
          p_image_size.x,

      local_y * static_cast<float>(viewport.render_texture.texture.height) /
          p_image_size.y};

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
    m_context.selection.select(found);
  }
  // =======
}

bool ViewportPanel::draw_viewport_controls(const ImVec2 &image_min,
                                           const ImVec2 &image_max) {
  Simulation &sim = m_context.simulation;
  const float button_size = 32.0f;
  const float spacing = 4.0f;
  const float large_spacing = 20.0f;
  const float padding = 6.0f;

  constexpr int button_count = 6;
  constexpr int normal_spacing_count = button_count - 2;

  const float controls_width = button_count * button_size +
                               normal_spacing_count * spacing + large_spacing +
                               padding * 2.0f;
  ;

  const float controls_height = button_size + padding * 2.0f;

  const float image_center_x = (image_min.x + image_max.x) * 0.5f;

  const ImVec2 controls_position{image_center_x - controls_width * 0.5f,
                                 image_min.y + 10.0f};

  ImGui::SetCursorScreenPos(controls_position);

  ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 6.0f);

  ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);

  ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0.08f, 0.08f, 0.08f, 0.85f});

  ImGui::BeginChild("ViewportControls", ImVec2{controls_width, controls_height},
                    true, ImGuiWindowFlags_NoScrollbar);

  ImGui::SetCursorPos({padding, padding});

  ImGui::BeginDisabled(sim.is_running());
  if (ImGui::Button(ICON_FA_PLAY, {button_size, button_size})) {
    sim.set_simulation_speed(Simulation::Speed::NORMAL);
    sim.start_simulation();
  }
  ImGui::EndDisabled();

  ImGui::SameLine(0.0f, spacing);

  ImGui::BeginDisabled(!sim.is_running());
  if (ImGui::Button(ICON_FA_PAUSE, {button_size, button_size})) {
    sim.end_simulation();
  }
  ImGui::EndDisabled();

  ImGui::SameLine(0.0f, spacing);

  ImGui::BeginDisabled();
  if (ImGui::Button(ICON_FA_STOP, {button_size, button_size})) {
    sim.end_simulation();
  }
  ImGui::EndDisabled();

  ImGui::SameLine(0.0f, large_spacing);

  if (ImGui::Button(ICON_FA_ANGLES_LEFT, {button_size, button_size})) {
    sim.set_simulation_speed(Simulation::Speed::SLOWER);
  }

  ImGui::SameLine(0.0f, spacing);

  if (ImGui::Button(ICON_FA_ANGLE_RIGHT, {button_size, button_size})) {
    sim.set_simulation_speed(Simulation::Speed::NORMAL);
  }

  ImGui::SameLine(0.0f, spacing);

  if (ImGui::Button(ICON_FA_ANGLES_RIGHT, {button_size, button_size})) {
    sim.set_simulation_speed(Simulation::Speed::FASTER);
  }

  const bool hovered =
      ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);

  ImGui::EndChild();

  ImGui::PopStyleColor();
  ImGui::PopStyleVar(2);

  return hovered;
}

} // namespace evosim
