#pragma once
#include <raylib.h>

class Food {
public:
  Food(Vector2 p_position);
  void render();
  Vector2 get_position();
  float consume();
  bool is_consumed();
  void set_position(Vector2 p_position);
  void set_energy(float p_energy);

private:
  Vector2 m_position;
  float m_energy = 0.50F;
};