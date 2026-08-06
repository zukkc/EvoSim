#include "InspectorVisitor.h"
#include "Panel.h"

namespace evosim {

class InspectorPanel : public Panel, public InspectorVisitor {
public:
  using Panel::Panel;
  void on_gui_render() override;

  void inspect(Agent &p_agent) override;
  void inspect(Food &p_food) override;

private:
  void draw_genome_table(Agent &p_agent);
};

} // namespace evosim
