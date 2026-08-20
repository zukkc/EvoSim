#pragma once

#include <cstdint>

namespace evosim {

class Object {
public:
  using ID = std::uint64_t;

  Object();
  virtual ~Object() = default;

  ID get_id() const { return m_id; }

private:
  ID m_id;
  inline static ID s_next_id = 1;
};

} // namespace evosim
