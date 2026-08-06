#include "Panel.h"

namespace evosim {

class NeuralPanel : public Panel {
public:
  using Panel::Panel;
  void on_gui_render() override;

private:
};

} // namespace evosim
