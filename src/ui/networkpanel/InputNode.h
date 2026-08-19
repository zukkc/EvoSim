#pragma once

#include "Node.h"

namespace evosim {

class InputNode : public Node {
public:
  InputNode(ImVec2 p_position, std::string p_name);
  void accept_inspector(InspectorVisitor &p_visitor) override;
};

} // namespace evosim