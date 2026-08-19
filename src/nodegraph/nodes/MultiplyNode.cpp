#include "MultiplyNode.h"

namespace evosim {

MultiplyNode::MultiplyNode() : Node("Multiply") {
  add_input_pin("A");
  add_input_pin("B");
  add_output_pin("Result");
}

} // namespace evosim
