#include "Panel.h"
#include "core/InspectorVisitor.h"

namespace evosim {

class Node;

class InspectorPanel : public Panel, public InspectorVisitor {
public:
  using Panel::Panel;
  void on_gui_render() override;

  void inspect(Agent &p_agent) override;
  void inspect(Food &p_food) override;
  void inspect(Node &p_node) override;

private:
  void draw_genome_table(Agent &p_agent);
};

} // namespace evosim
