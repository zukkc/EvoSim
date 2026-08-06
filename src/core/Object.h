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
  
  bool is_active() const;
  void set_is_active(bool p_active);

private:
  ID m_id;
  inline static ID s_next_id = 1;
  
  bool m_is_active = false;
};

} // namespace evosim