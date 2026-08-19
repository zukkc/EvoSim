#pragma once

#include "../Panel.h"
#include "nodegraph/NetworkGraph.h"
#include <imgui.h>
#include <optional>
#include <unordered_map>

namespace evosim {

struct PendingConnection {
  Object::ID from_node;
  PinID from_pin;
};

struct HoveredPin {
  Object::ID node;
  PinID pin;
};

struct NodeViewState {
  ImVec2 position{};
};

class NetworkPanel : public Panel {
public:
  using Panel::Panel;
  void on_attach() override;
  void on_gui_render() override;

private:
  void draw_grid(ImDrawList *p_draw_list);
  void draw_node(ImDrawList *p_draw_list, const Node &p_node,
                 bool p_is_selected);
  void draw_connection(ImDrawList *p_draw_list, const Connection &p_connection);
  void draw_connection_drag(ImDrawList *draw_list);

  void handle_context_menu();
  void handle_camera_input();
  void handle_node_dragging();
  void handle_node_selection();
  void handle_connection_input();

  Node &create_node(NodeType p_type, ImVec2 p_position);
  NodeViewState &get_node_view(const Node &p_node);
  ImVec2 get_node_size(const Node &p_node) const;

  std::optional<PendingConnection> m_pending_connection;
  std::unordered_map<Object::ID, NodeViewState> m_node_views;

  ImVec2 m_pan{0.0f, 0.0f};
  float m_zoom = 1.0f;
  float m_node_width = 200.0f;
  float m_pin_spacing = 20.0f;
  float m_header_height = 25.0f;
  std::optional<Object::ID> m_dragging_node_id;

  Node *get_node_from_grid_position(ImVec2 p_grid_position);
  Node *find_node_by_id(Object::ID p_id);
  ImVec2 grid_to_screen(ImVec2 p_position_on_grid);
  ImVec2 screen_to_grid(ImVec2 p_position_on_screen);
  std::optional<ImVec2> get_input_pin_position(const Node &p_node,
                                               PinID p_pin_id);
  std::optional<ImVec2> get_output_pin_position(const Node &p_node,
                                                PinID p_pin_id);
  bool is_mouse_over_pin(ImVec2 p_pin_position) const;
  std::optional<HoveredPin> find_hovered_input_pin();

  static void draw_centered_text(ImDrawList *draw_list, ImFont *font,
                                 float font_size, ImVec2 node_min,
                                 ImVec2 node_max, const char *text,
                                 ImU32 color);
  static void draw_input_label(ImDrawList *draw_list, ImFont *font,
                               float font_size, ImVec2 pin_pos,
                               const std::string &name, float zoom);
  static void draw_output_label(ImDrawList *draw_list, ImFont *font,
                                float font_size, ImVec2 pin_pos,
                                const std::string &name, float zoom);
  static std::optional<std::size_t> find_pin_index(const std::vector<Pin> &pins,
                                                   PinID id);
};

} // namespace evosim
