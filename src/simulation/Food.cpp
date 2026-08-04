#include "Food.h"
#include <raylib.h>

namespace evosim {

Food::Food(int p_id, Vector2 p_position) : m_id(p_id), m_position(p_position) {}

void Food::render() {
  DrawCircle((int)m_position.x, (int)m_position.y, 3.0F, BLUE);
}

float Food::consume() {
  float energy = m_energy;
  m_energy = 0.f;
  return energy;
}
void Food::set_position(Vector2 p_position) { m_position = p_position; }
void Food::set_energy(float p_energy) { m_energy = p_energy; }

int Food::get_id() const { return m_id; }
Vector2 Food::get_position() const { return m_position; }
bool Food::is_consumed() const { return m_energy <= 0; }

} // namespace evosim