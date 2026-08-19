#pragma once
#include "WorldObject.h"
#include "raylib.h"

namespace evosim {

struct Transform2D {
  Vector2 position{};
  float rotation = 0.0F;
  float radius = 10.0F;
};

class Object2D : public WorldObject {
public:
  explicit Object2D(Vector2 p_position, float p_radius)
      : m_transform{p_position, 0.0F, p_radius} {}

  void render_selection_overlay() const override {
    constexpr float overlay_offset = 2.0F;
    constexpr float overlay_thickness = 2.0F;

    DrawRing(m_transform.position, m_transform.radius + overlay_offset,
             m_transform.radius + overlay_offset + overlay_thickness, 0.0F,
             360.0F, 48, YELLOW);
  }

  Transform2D &get_transform() { return m_transform; }
  const Transform2D &get_transform() const { return m_transform; }

protected:
  Transform2D m_transform;
};

} // namespace evosim
