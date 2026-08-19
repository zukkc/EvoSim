#include "Node.h"

namespace evosim {

Node::Node(ImVec2 p_position, std::string p_name)
    : m_position(p_position), m_name(p_name) {
}

void Node::add_input_pin(std::string p_name) {
  m_inputs.emplace_back(Pin(m_next_pin_id++, p_name));
  resize_node();
}
void Node::remove_input_pin(PinID p_pin_id) {
  std::erase_if(m_inputs,
                [p_pin_id](const Pin &pin) { return pin.id == p_pin_id; });
  resize_node();
}
void Node::add_output_pin(std::string p_name) {
  m_outputs.emplace_back(Pin(m_next_pin_id++, p_name));
  resize_node();
}
void Node::remove_output_pin(PinID p_pin_id) {
  std::erase_if(m_outputs,
                [p_pin_id](const Pin &pin) { return pin.id == p_pin_id; });
  resize_node();
}
const std::vector<Pin> &Node::get_inputs() const { return m_inputs; }
const std::vector<Pin> &Node::get_outputs() const { return m_outputs; }
ImVec2 &Node::get_position() { return m_position; }
ImVec2 Node::get_position() const { return m_position; }
ImVec2 Node::get_size() const { return m_size; }
float Node::get_spacing() const { return m_spacing; }
float Node::get_header_height() const { return m_header; }
const std::string &Node::get_name() const { return m_name; }

void Node::resize_node() {
  float inputs_size = static_cast<float>(m_inputs.size()) * m_spacing;
  float outputs_size = static_cast<float>(m_outputs.size()) * m_spacing;
  float max_size = inputs_size >= outputs_size ? inputs_size : outputs_size;
  m_size = ImVec2(200.0f, max_size + m_header + m_spacing);
}

} // namespace evosim