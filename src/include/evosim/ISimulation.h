#pragma once

#include <evosim/Object.h>

#include <raylib.h>

namespace evosim {

class ISimulation {
public:
  virtual ~ISimulation() = default;

  virtual void on_attach() {}
  virtual void on_detach() {}

  virtual void update(float p_delta_time) = 0;
  virtual void render() const = 0;
  virtual void render_selection_overlay(const Object &p_object) const = 0;

  virtual Object *find_object_at(Vector2 p_world_position) = 0;
  virtual Object *find_object_by_id(Object::ID p_id) = 0;

  virtual void draw_inspector(Object &p_object) = 0;
  virtual void draw_statistics() {}
};

} // namespace evosim
