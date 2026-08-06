#pragma once
#include "../core/Object.h"
#include "raylib.h"

namespace evosim {

struct Transform2D {
  Vector2 position{};
  float rotation = 0.0F;
  float radius = 10.0F;
};

class Object2D : public Object {
public:
  explicit Object2D(Vector2 p_position, float p_radius) : m_transform{p_position, 0.0F, p_radius} {};
  Transform2D &get_transform() { return m_transform; }
  const Transform2D &get_transform() const { return m_transform; }

protected:
  Transform2D m_transform;
};

} // namespace evosim