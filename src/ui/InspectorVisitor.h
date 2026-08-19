#pragma once

namespace evosim {

class Agent;
class Food;
class InputNode;

class InspectorVisitor {

public:
  virtual ~InspectorVisitor() = default;

  virtual void inspect(Agent &agent) = 0;
  virtual void inspect(Food &food) = 0;
  virtual void inspect(InputNode &node) = 0;
};

} // namespace evosim