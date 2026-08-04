#include "Panel.h"

namespace evosim {

class StatisticsPanel : public Panel {
public:
  using Panel::Panel;
  void on_gui_render() override;
};

} // namespace evosim