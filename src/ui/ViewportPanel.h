#include "Panel.h"

class ViewportPanel : public Panel {
public:
  using Panel::Panel;
  void on_gui_render() override;
};