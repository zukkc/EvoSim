#include "AddNode.h"

namespace evosim {

AddNode::AddNode() : Node("Add") {
  add_input_pin("A");
  add_input_pin("B");
  add_output_pin("Result");
}

} // namespace evosim
