#pragma once
#include <raylib.h>

namespace evosim {

class Food {
public:
  Food(int p_id, Vector2 p_position);
  void render();

  float consume();
  void set_position(Vector2 p_position);
  void set_energy(float p_energy);

  int get_id() const;
  Vector2 get_position() const;
  bool is_consumed() const;

private:
  int m_id;
  Vector2 m_position;
  float m_energy = 0.50F;
};

} // namespace evosim