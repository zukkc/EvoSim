#pragma once

#include <cstdint>
#include <string>
#include <utility>

namespace evosim {

using PinID = std::uint32_t;

struct Pin {
  PinID id;
  std::string name;

  Pin(PinID p_id, std::string p_name) : id(p_id), name(std::move(p_name)) {}
};

} // namespace evosim
