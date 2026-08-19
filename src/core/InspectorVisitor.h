#pragma once

namespace evosim {

class Agent;
class Food;
class Node;

class InspectorVisitor {
public:
  virtual ~InspectorVisitor() = default;

  virtual void inspect(Agent &p_agent) = 0;
  virtual void inspect(Food &p_food) = 0;
  virtual void inspect(Node &p_node) = 0;
};

} // namespace evosim
