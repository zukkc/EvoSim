#include "layers/Layer.h"
#include "./app/Context.h"
#include "./ui/Panel.h"
#include <memory>
#include <vector>

class EditorLayer : public Layer {

public:
  explicit EditorLayer(AppContext &context);
  void on_gui_render() override;

  private:
  AppContext &m_context;
  std::vector<std::unique_ptr<Panel>> m_panels;
};