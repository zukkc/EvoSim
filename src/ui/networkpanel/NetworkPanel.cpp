#include "NetworkPanel.h"
#include "InputNode.h"
#include "core/Context.h"
#include "imgui.h"
#include "raylib.h"
#include "simulation/Simulation.h"
#include <algorithm>
#include <cmath>
#include <memory>
#include <optional>

namespace evosim {

void NetworkPanel::on_attach() {
  m_context.network.add_node(
      std::make_unique<InputNode>(ImVec2(300.F, 200.F), "test"));
}

void NetworkPanel::on_gui_render() {
  ImGui::Begin("Network Editor");

  handle_camera_input();
  handle_node_dragging();
  handle_node_selection();
  handle_connection_input();

  Simulation &sim = m_context.simulation;
  ImDrawList *draw_list = ImGui::GetWindowDrawList();

  ImGui::BeginDisabled(sim.is_running());

  draw_grid(draw_list);

  for (const auto &connection : m_context.network.get_connections()) {
    draw_connection(draw_list, connection);
  }

  draw_connection_drag(draw_list);

  for (const auto &node_ptr : m_context.network.get_nodes()) {
    const Node &node = *node_ptr;
    draw_node(draw_list, node, m_context.selection.is_selected(node));
  }

  ImGui::EndDisabled();

  ImGui::End();
}

void NetworkPanel::draw_grid(ImDrawList *p_draw_list) {
  ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
  ImVec2 canvas_size = ImGui::GetContentRegionAvail();

  float grid_size = 50.0f * m_zoom;

  float offset_x = fmodf(m_pan.x, grid_size);
  float offset_y = fmodf(m_pan.y, grid_size);

  for (float x = offset_x; x < canvas_size.x; x += grid_size) {
    p_draw_list->AddLine({canvas_pos.x + x, canvas_pos.y},
                         {canvas_pos.x + x, canvas_pos.y + canvas_size.y},
                         IM_COL32(60, 60, 60, 255));
  }

  for (float y = offset_y; y < canvas_size.y; y += grid_size) {
    p_draw_list->AddLine({canvas_pos.x, canvas_pos.y + y},
                         {canvas_pos.x + canvas_size.x, canvas_pos.y + y},
                         IM_COL32(60, 60, 60, 255));
  }
}

void NetworkPanel::draw_node(ImDrawList *p_draw_list, const Node &p_node,
                             bool p_is_selected) {
  ImVec2 node_pos = grid_to_screen(p_node.get_position());

  ImVec2 node_max = {node_pos.x + p_node.get_size().x * m_zoom,
                     node_pos.y + p_node.get_size().y * m_zoom};

  float rounding = 6.0f * m_zoom;
  float header_height = p_node.get_header_height() * m_zoom;
  float header_font_size = 18.0f * m_zoom;
  float pin_radius = 5.0f * m_zoom;
  float pin_label_font_size = 14.0f * m_zoom;

  ImVec2 header_max = {node_max.x, node_pos.y + header_height};

  // BODY
  p_draw_list->AddRectFilled(node_pos, node_max, IM_COL32(40, 40, 45, 255),
                             rounding);

  // HEADER
  p_draw_list->AddRectFilled(node_pos, header_max, IM_COL32(10, 68, 74, 255),
                             rounding, ImDrawFlags_RoundCornersTop);

  // SEPARATOR
  p_draw_list->AddLine({node_pos.x, header_max.y}, {node_max.x, header_max.y},
                       IM_COL32(90, 90, 100, 255), 1.0f * m_zoom);

  // BORDER
  p_draw_list->AddRect(node_pos, node_max, IM_COL32(100, 100, 110, 255),
                       rounding);

  if (p_is_selected) {
    p_draw_list->AddRect(node_pos, node_max, IM_COL32(255, 190, 60, 255),
                         rounding, 0, 3.0F * m_zoom);
  }

  // HEADER TEXT
  draw_centered_text(p_draw_list, ImGui::GetFont(), header_font_size, node_pos,
                     header_max, p_node.get_name().c_str(), IM_COL32_WHITE);

  for (const auto &input : p_node.get_inputs()) {
    std::optional<ImVec2> grid_pin_position =
        get_input_pin_position(p_node, input.id);
    if (!grid_pin_position)
      continue;

    ImVec2 screen_pin_position = grid_to_screen(*grid_pin_position);

    p_draw_list->AddCircleFilled(screen_pin_position, pin_radius,
                                 IM_COL32(200, 200, 200, 255));
    draw_input_label(p_draw_list, ImGui::GetFont(), pin_label_font_size,
                     screen_pin_position, input.name, m_zoom);
  }
  for (const auto &output : p_node.get_outputs()) {
    std::optional<ImVec2> grid_pin_position =
        get_output_pin_position(p_node, output.id);
    if (!grid_pin_position)
      continue;

    ImVec2 screen_pin_position = grid_to_screen(*grid_pin_position);
    p_draw_list->AddCircleFilled(screen_pin_position, pin_radius,
                                 IM_COL32(200, 200, 200, 255));
    draw_output_label(p_draw_list, ImGui::GetFont(), pin_label_font_size,
                      screen_pin_position, output.name, m_zoom);
  }
}

void NetworkPanel::draw_connection(ImDrawList *p_draw_list,
                                   const Connection &p_connection) {
  Node *from_node = find_node_by_id(p_connection.from_node);
  Node *to_node = find_node_by_id(p_connection.to_node);

  if (!from_node || !to_node)
    return;

  std::optional<ImVec2> output_pin_position =
      get_output_pin_position(*from_node, p_connection.from_pin);
  std::optional<ImVec2> input_pin_position =
      get_input_pin_position(*to_node, p_connection.to_pin);

  if (!input_pin_position.has_value() || !output_pin_position.has_value())
    return;

  ImVec2 from_screen_position = grid_to_screen(output_pin_position.value());
  ImVec2 to_screen_position = grid_to_screen(input_pin_position.value());

  p_draw_list->AddBezierCubic(
      from_screen_position,
      {from_screen_position.x + (80.0f * m_zoom), from_screen_position.y},
      {to_screen_position.x - (80.0f * m_zoom), to_screen_position.y},
      to_screen_position, IM_COL32(180, 180, 180, 255), 3.0f * m_zoom);
}

void NetworkPanel::draw_connection_drag(ImDrawList *draw_list) {
  if (!m_pending_connection)
    return;

  Node *from_node = find_node_by_id(m_pending_connection->from_node);

  if (!from_node)
    return;

  ImVec2 start = grid_to_screen(
      get_output_pin_position(*from_node, m_pending_connection->from_pin)
          .value());

  ImVec2 end = ImGui::GetIO().MousePos;

  // jeżeli jesteśmy nad inputem,
  // przyklej kabel do niego
  auto hovered = find_hovered_input_pin();

  if (hovered) {
    Node *to_node = find_node_by_id(hovered->node);

    if (to_node) {
      end = grid_to_screen(
          get_input_pin_position(*to_node, hovered->pin).value());
    }
  }

  float distance = std::abs(end.x - start.x);

  float curve = std::max(50.0f * m_zoom, distance * 0.5f);

  draw_list->AddBezierCubic(start, {start.x + curve, start.y},
                            {end.x - curve, end.y}, end,
                            IM_COL32(180, 180, 180, 255), 3.0f * m_zoom);
}

void NetworkPanel::handle_camera_input() {
  // PANNING
  if (ImGui::IsWindowHovered() &&
      ImGui::IsMouseDragging(ImGuiMouseButton_Right)) {
    ImVec2 delta = ImGui::GetIO().MouseDelta;

    m_pan.x += delta.x;
    m_pan.y += delta.y;

    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
  }

  // =======

  // ZOOMING

  if (ImGui::IsWindowHovered()) {

    ImVec2 mouse = ImGui::GetIO().MousePos;
    ImVec2 before = screen_to_grid(mouse);
    float wheel = ImGui::GetIO().MouseWheel;

    if (wheel != 0.0f) {
      m_zoom *= std::pow(1.1f, wheel);
      m_zoom = std::clamp(m_zoom, 0.2f, 3.0f);
    }

    ImVec2 after = screen_to_grid(mouse);

    m_pan.x += (after.x - before.x) * m_zoom;
    m_pan.y += (after.y - before.y) * m_zoom;
  }

  // =======
}
void NetworkPanel::handle_node_dragging() {
  // DRAGGING NODES

  if (ImGui::IsWindowHovered() &&
      ImGui::IsMouseDragging(ImGuiMouseButton_Middle)) {

    if (!m_dragging_node_id.has_value()) {
      ImVec2 mouse_grid = screen_to_grid(ImGui::GetIO().MousePos);
      Node *dragging_node = get_node_from_grid_position(mouse_grid);
      if (dragging_node) {
        m_dragging_node_id = dragging_node->get_id();
      }
    }

    if (m_dragging_node_id.has_value()) {
      Node *dragging_node = find_node_by_id(m_dragging_node_id.value());
      if (dragging_node) {
        dragging_node->get_position().x += ImGui::GetIO().MouseDelta.x / m_zoom;
        dragging_node->get_position().y += ImGui::GetIO().MouseDelta.y / m_zoom;
      }
    }
  } else {
    m_dragging_node_id.reset();
  }

  // ==============
}

void NetworkPanel::handle_node_selection() {
  if (!ImGui::IsWindowHovered() ||
      !ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    return;
  }

  const ImVec2 mouse_grid = screen_to_grid(ImGui::GetIO().MousePos);
  m_context.selection.select(get_node_from_grid_position(mouse_grid));
}

void NetworkPanel::handle_connection_input() {
  if (!m_pending_connection) {
    // szukamy klikniętego outputu

    for (auto &node_ptr : m_context.network.get_nodes()) {
      Node &node = *node_ptr;
      for (auto &output : node.get_outputs()) {

        ImVec2 pin_pos =
            grid_to_screen(get_output_pin_position(node, output.id).value());

        if (is_mouse_over_pin(pin_pos) &&
            ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
          m_pending_connection = PendingConnection{.from_node = node.get_id(),
                                                   .from_pin = output.id};

          return;
        }
      }
    }

    return;
  }

  if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
    auto hovered_input = find_hovered_input_pin();

    if (hovered_input) {
      m_context.network.get_connections().push_back(Connection(
          m_pending_connection->from_node, m_pending_connection->from_pin,
          hovered_input->node, hovered_input->pin));
    }

    m_pending_connection.reset();
  }
}

Node *NetworkPanel::get_node_from_grid_position(ImVec2 p_grid_position) {
  Vector2 position = Vector2{
      .x = p_grid_position.x,
      .y = p_grid_position.y,
  };

  for (auto &node_ptr : m_context.network.get_nodes()) {
    Rectangle rect = {node_ptr->get_position().x, node_ptr->get_position().y,
                      node_ptr->get_size().x, node_ptr->get_size().y};

    if (CheckCollisionPointRec(position, rect)) {
      return node_ptr.get();
    }
  }

  return nullptr;
}

Node *NetworkPanel::find_node_by_id(Object::ID p_id) {
  return m_context.network.get_node_by_id(p_id);
}

std::optional<HoveredPin> NetworkPanel::find_hovered_input_pin() {
  for (auto &node_ptr : m_context.network.get_nodes()) {
    Node &node = *node_ptr;
    for (auto &input : node.get_inputs()) {
      ImVec2 position =
          grid_to_screen(get_input_pin_position(node, input.id).value());

      if (is_mouse_over_pin(position)) {
        return HoveredPin{.node = node.get_id(), .pin = input.id};
      }
    }
  }

  return std::nullopt;
}

std::optional<ImVec2> NetworkPanel::get_input_pin_position(const Node &p_node,
                                                           PinID p_pin_id) {
  auto index = find_pin_index(p_node.get_inputs(), p_pin_id);

  if (!index)
    return std::nullopt;

  return ImVec2{p_node.get_position().x,
                p_node.get_position().y + p_node.get_header_height() +
                    p_node.get_spacing() * static_cast<float>(*index + 1)};
}

std::optional<ImVec2> NetworkPanel::get_output_pin_position(const Node &p_node,
                                                            PinID p_pin_id) {
  auto index = find_pin_index(p_node.get_outputs(), p_pin_id);

  if (!index)
    return std::nullopt;

  return ImVec2{p_node.get_position().x + p_node.get_size().x,
                p_node.get_position().y + p_node.get_header_height() +
                    p_node.get_spacing() * static_cast<float>(*index + 1)};
}

ImVec2 NetworkPanel::grid_to_screen(ImVec2 p_position_on_grid) {
  ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
  return {canvas_pos.x + m_pan.x + p_position_on_grid.x * m_zoom,
          canvas_pos.y + m_pan.y + p_position_on_grid.y * m_zoom};
}

ImVec2 NetworkPanel::screen_to_grid(ImVec2 p_position_on_screen) {
  ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
  return {(p_position_on_screen.x - canvas_pos.x - m_pan.x) / m_zoom,
          (p_position_on_screen.y - canvas_pos.y - m_pan.y) / m_zoom};
}

void NetworkPanel::draw_centered_text(ImDrawList *draw_list, ImFont *font,
                                      float font_size, ImVec2 node_min,
                                      ImVec2 node_max, const char *text,
                                      ImU32 color) {
  ImVec2 text_size = font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, text);

  ImVec2 node_center = {(node_min.x + node_max.x) * 0.5f,
                        (node_min.y + node_max.y) * 0.5f};

  ImVec2 text_pos = {node_center.x - text_size.x * 0.5f,
                     node_center.y - text_size.y * 0.5f};

  draw_list->AddText(font, font_size, text_pos, color, text);
}

void NetworkPanel::draw_input_label(ImDrawList *draw_list, ImFont *font,
                                    float font_size, ImVec2 pin_pos,
                                    const std::string &name, float zoom) {
  ImVec2 size = font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, name.c_str());

  float padding = 10.0f * zoom;

  ImVec2 pos = {pin_pos.x + padding, pin_pos.y - size.y * 0.5f};

  draw_list->AddText(font, font_size, pos, IM_COL32_WHITE, name.c_str());
}

void NetworkPanel::draw_output_label(ImDrawList *draw_list, ImFont *font,
                                     float font_size, ImVec2 pin_pos,
                                     const std::string &name, float zoom) {
  ImVec2 size = font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, name.c_str());

  float padding = 10.0f * zoom;

  ImVec2 pos = {pin_pos.x - padding - size.x, pin_pos.y - size.y * 0.5f};

  draw_list->AddText(font, font_size, pos, IM_COL32_WHITE, name.c_str());
}

std::optional<std::size_t>
NetworkPanel::find_pin_index(const std::vector<Pin> &pins, PinID id) {
  auto it = std::find_if(pins.begin(), pins.end(),
                         [id](const Pin &pin) { return pin.id == id; });

  if (it == pins.end())
    return std::nullopt;

  return static_cast<std::size_t>(std::distance(pins.begin(), it));
}

bool NetworkPanel::is_mouse_over_pin(ImVec2 p_pin_position) const {
  ImVec2 mouse = ImGui::GetIO().MousePos;

  float dx = mouse.x - p_pin_position.x;
  float dy = mouse.y - p_pin_position.y;

  float radius = std::max(8.0f * m_zoom, 6.0f);

  return dx * dx + dy * dy <= radius * radius;
}

} // namespace evosim
