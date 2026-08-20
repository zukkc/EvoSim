#include "Node.h"

#include <algorithm>
#include <utility>

namespace evosim {

Node::Node(std::string p_name) : m_name(std::move(p_name)) {}

void Node::add_input_pin(std::string p_name) {
  m_inputs.emplace_back(m_next_pin_id++, std::move(p_name));
}

void Node::remove_input_pin(PinID p_pin_id) {
  std::erase_if(m_inputs,
                [p_pin_id](const Pin &pin) { return pin.id == p_pin_id; });
}

void Node::add_output_pin(std::string p_name) {
  m_outputs.emplace_back(m_next_pin_id++, std::move(p_name));
}

void Node::remove_output_pin(PinID p_pin_id) {
  std::erase_if(m_outputs,
                [p_pin_id](const Pin &pin) { return pin.id == p_pin_id; });
}

const std::vector<Pin> &Node::get_inputs() const { return m_inputs; }

const std::vector<Pin> &Node::get_outputs() const { return m_outputs; }

const std::string &Node::get_name() const { return m_name; }

} // namespace evosim
