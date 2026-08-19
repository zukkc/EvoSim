#pragma once

#include "Pin.h"
#include "core/Object.h"

#include <cstdint>

namespace evosim {

using ConnectionID = std::uint32_t;

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
