#include "SimulationLayer.h"
#include "raylib.h"

SimulationLayer::SimulationLayer(AppContext &context) : m_context(context) {
  m_context.viewport.render_texture = LoadRenderTexture(1920, 1080);

  SetTextureFilter(m_context.viewport.render_texture.texture,
                   TEXTURE_FILTER_BILINEAR);

  context.viewport.camera.target = {0.0f, 0.0f};
  context.viewport.camera.offset = {0.0f, 0.0f};
  context.viewport.camera.rotation = 0.0f;
  context.viewport.camera.zoom = 1.0f;
}

SimulationLayer::~SimulationLayer() {
  UnloadRenderTexture(m_context.viewport.render_texture);
}

void SimulationLayer::on_update(float p_dt) {
  // if speed up wanted
  // const float scaled_dt = dt * m_context.simulation_speed;
  m_context.simulation.update(p_dt);
}

void SimulationLayer::on_render() {
  resize_viewport_if_needed();

  BeginTextureMode(m_context.viewport.render_texture);
  ClearBackground(BLACK);

  BeginMode2D(m_context.viewport.camera);
  m_context.simulation.render();
  EndMode2D();

  EndTextureMode();
}

void SimulationLayer::resize_viewport_if_needed() {
  auto &viewport = m_context.viewport;

  if (viewport.width == viewport.requested_width &&
      viewport.height == viewport.requested_height) {
    return;
  }

  if (viewport.render_texture.texture.id != 0) {
    UnloadRenderTexture(viewport.render_texture);
  }

  viewport.width = viewport.requested_width;
  viewport.height = viewport.requested_height;

  viewport.render_texture = LoadRenderTexture(viewport.width, viewport.height);

  SetTextureFilter(viewport.render_texture.texture, TEXTURE_FILTER_BILINEAR);
}