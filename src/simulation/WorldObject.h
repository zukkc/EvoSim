#pragma once

#include "core/Object.h"

namespace evosim {

// Object that belongs to the rendered simulation world. Editor-only objects,
// such as graph nodes, deliberately do not implement this interface.
class WorldObject : public Object {
public:
  virtual void render() const = 0;
  virtual void render_selection_overlay() const = 0;
};

} // namespace evosim
