#include "InputNode.h"

#include "../InspectorVisitor.h"

namespace evosim {

InputNode::InputNode(ImVec2 p_position, std::string p_name)
    : Node(p_position, p_name) {
        add_output_pin("");
    }

void InputNode::accept_inspector(InspectorVisitor& p_visitor) {
  p_visitor.inspect(*this);
}

} // namespace evosim