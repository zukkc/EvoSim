#include "Panel.h"

class InspectorPanel : public Panel {
public:
  using Panel::Panel;
  void on_update(float) override;
  void on_gui_render() override;
  
private:
  Agent *m_active = nullptr;

  void draw_genome_table();
};