#include "Panel.h"

class StatisticsPanel : public Panel {
public:
  using Panel::Panel;
  void on_gui_render() override;
};