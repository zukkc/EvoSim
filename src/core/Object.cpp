#include "Object.h"

namespace evosim {

Object::Object() : m_id(s_next_id++) {}

bool Object::is_active() const { return m_is_active; }
void Object::set_is_active(bool p_active) { m_is_active = p_active; }

} // namespace evosim