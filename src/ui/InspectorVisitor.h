#pragma once

namespace evosim {

class Agent;
class Food;

class InspectorVisitor {

public:
  virtual ~InspectorVisitor() = default;

  virtual void inspect(Agent &agent) = 0;
  virtual void inspect(Food &food) = 0;
};

} // namespace evosim