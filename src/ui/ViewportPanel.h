#include "Panel.h"
#include <imgui.h>

namespace evosim {

class ViewportPanel : public Panel {
public:
  using Panel::Panel;
  void on_gui_render() override;

private:
  bool m_is_panning = false;

  void handle_input(bool p_is_viewport_hovered, const ImVec2 &p_image_min,
                    const ImVec2 &p_image_size);
  bool draw_viewport_controls(const ImVec2 &p_image_min,
                              const ImVec2 &p_image_max);
};

} // namespace evosim