#include "Food.h"
#include <raylib.h>

#include "core/InspectorVisitor.h"

namespace evosim {

Food::Food(Vector2 p_position) : Object2D(p_position, 3.0F) {}

void Food::accept_inspector(InspectorVisitor &p_visitor) {
  p_visitor.inspect(*this);
}

void Food::render() const {
  DrawCircle((int)m_transform.position.x, (int)m_transform.position.y,
             m_transform.radius, BLUE);
}

float Food::consume() {
  float energy = m_energy;
  m_energy = 0.f;
  return energy;
}
void Food::set_energy(float p_energy) { m_energy = p_energy; }
bool Food::is_consumed() const { return m_energy <= 0; }

} // namespace evosim
