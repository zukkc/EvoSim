#pragma once

#include <evosim/Object.h>

namespace evosim {

class WorldObject : public Object {
public:
  virtual void render() const = 0;
  virtual void render_selection_overlay() const = 0;
};

} // namespace evosim
