#include "Panel.h"

namespace evosim {

class Node;

class InspectorPanel : public Panel {
public:
  using Panel::Panel;
  void on_gui_render() override;

private:
  void draw_node_inspector(Node &p_node);
};

} // namespace evosim
