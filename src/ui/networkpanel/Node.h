#pragma once

#include "core/Object.h"
#include <cstdint>
#include <imgui.h>
#include <string>
#include <vector>

namespace evosim {

using PinID = uint32_t;
using ConnectionID = uint32_t;

struct Pin {
  PinID id;
  std::string name;

  Pin(PinID p_id, std::string p_name) : id(p_id), name(p_name) {}
};

class Node : public Object {
protected:
  Node(ImVec2 p_position, std::string p_name);

public:
  void add_input_pin(std::string p_name);
  void remove_input_pin(PinID p_pin_id);
  void add_output_pin(std::string p_name);
  void remove_output_pin(PinID p_pin_id);
  const std::vector<Pin> &get_inputs() const;
  const std::vector<Pin> &get_outputs() const;
  ImVec2 &get_position();
  ImVec2 get_position() const;
  ImVec2 get_size() const;
  float get_spacing() const;
  float get_header_height() const;
  const std::string &get_name() const;

private:
  PinID m_next_pin_id = 0;
  ImVec2 m_position;
  ImVec2 m_size;
  float m_spacing = 20.0f;
  float m_header = 25.0f;

  std::vector<Pin> m_inputs;
  std::vector<Pin> m_outputs;

  std::string m_name;

  void resize_node();
};

struct Connection {
  ConnectionID id;
  inline static ConnectionID s_next_id = 0;

  Object::ID from_node;
  PinID from_pin;

  Object::ID to_node;
  PinID to_pin;

  Connection(Object::ID p_from_node, PinID p_from_pin, Object::ID p_to_node,
             PinID p_to_pin)
      : id(s_next_id++), from_node(p_from_node), from_pin(p_from_pin),
        to_node(p_to_node), to_pin(p_to_pin) {}
};

} // namespace evosim