#pragma once

#include <imgui.h>

#include "./app/Context.h"
#include "Layer.h"

class SimulationLayer : public Layer {
public:
  explicit SimulationLayer(AppContext &context);
  ~SimulationLayer() override;
  void on_update(float p_dt) override;
  void on_render() override;

private:
  AppContext &m_context;

  void resize_viewport_if_needed();
};