#pragma once

#include "Pin.h"
#include "core/Object.h"

#include <string>
#include <vector>

namespace evosim {

class Node : public Object {
public:
  void accept_inspector(InspectorVisitor &p_visitor) override;

  void add_input_pin(std::string p_name);
  void remove_input_pin(PinID p_pin_id);
  void add_output_pin(std::string p_name);
  void remove_output_pin(PinID p_pin_id);

  const std::vector<Pin> &get_inputs() const;
  const std::vector<Pin> &get_outputs() const;
  const std::string &get_name() const;

protected:
  explicit Node(std::string p_name);

private:
  PinID m_next_pin_id = 0;
  std::vector<Pin> m_inputs;
  std::vector<Pin> m_outputs;
  std::string m_name;
};

} // namespace evosim
