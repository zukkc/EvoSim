#pragma once
#include <raylib.h>

#include "Object2D.h"

namespace evosim {

class Food : public Object2D {
public:
  Food(Vector2 p_position);
  void accept_inspector(InspectorVisitor &p_visitor) override;
  void render();

  float consume();
  void set_energy(float p_energy);

  bool is_consumed() const;

private:
  float m_energy = 0.50F;
};

} // namespace evosim