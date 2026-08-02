#include "Panel.h"

class InspectorPanel : public Panel {
public:
  using Panel::Panel;
  void on_gui_render() override;
};