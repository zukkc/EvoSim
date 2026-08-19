#include "./core/Context.h"
#include "./ui/Panel.h"
#include "layers/Layer.h"
#include <memory>
#include <vector>

namespace evosim {

class EditorLayer : public Layer {

public:
  explicit EditorLayer(AppContext &context);
  void on_update(float p_dt) override;
  void on_gui_render() override;
  
  void add_panel(std::unique_ptr<Panel> p_panel);

private:
  AppContext &m_context;
  std::vector<std::unique_ptr<Panel>> m_panels;
};

} // namespace evosim