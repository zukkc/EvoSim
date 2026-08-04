#include "Panel.h"

namespace evosim {

class ViewportPanel : public Panel {
public:
  using Panel::Panel;
  void on_gui_render() override;

private:
  bool m_is_panning = false;

  void handle_input(bool p_is_viewport_hovered);
};

} // namespace evosim