#pragma once
#include <cstdint>

namespace evosim {

class InspectorVisitor;

class Object {
public:
  Object();
  virtual ~Object() = default;
  virtual void accept_inspector(InspectorVisitor &p_inspector) = 0;

  using ID = std::uint64_t;
  ID get_id() const { return m_id; }

private:
  ID m_id;
  inline static ID s_next_id = 1;
};

} // namespace evosim
