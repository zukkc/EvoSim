#include "Food.h"
#include <raylib.h>

Food::Food(Vector2 p_position) : m_position(p_position) {}

void Food::render() {
  DrawCircle((int)m_position.x, (int)m_position.y, 3.0F, BLUE);
}

Vector2 Food::get_position() { return m_position; }

float Food::consume() {
  float energy = m_energy;
  m_energy = 0.f;
  return energy;
}

bool Food::is_consumed() { return m_energy <= 0; }

void Food::set_position(Vector2 p_position) { m_position = p_position; }

void Food::set_energy(float p_energy) { m_energy = p_energy; }