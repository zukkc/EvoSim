#pragma once

#include <evosim/ISimulation.h>

#include "nodegraph/NetworkGraph.h"

#include <algorithm>
#include <memory>
#include <optional>
#include <utility>

struct ImFont;

namespace evosim {

struct UIContext {
  ImFont *font_regular = nullptr;
  ImFont *font_bold = nullptr;
};

struct ViewportContext {
  RenderTexture2D render_texture{};

  int width = 1;
  int height = 1;

  int requested_width = 1;
  int requested_height = 1;

  Camera2D camera{};
};

struct PlaybackContext {
  bool is_running = false;
  float time_scale = 1.0F;

  void slow_down() { time_scale = std::max(0.125F, time_scale * 0.5F); }
  void reset_speed() { time_scale = 1.0F; }
  void speed_up() { time_scale = std::min(16.0F, time_scale * 2.0F); }
};

class SelectionContext {
public:
  void select(const Object *p_object) {
    if (p_object) {
      m_selected_object_id = p_object->get_id();
    } else {
      clear();
    }
  }

  void clear() { m_selected_object_id.reset(); }

  bool is_selected(const Object &p_object) const {
    return m_selected_object_id && *m_selected_object_id == p_object.get_id();
  }

  std::optional<Object::ID> get_selected_id() const {
    return m_selected_object_id;
  }

private:
  std::optional<Object::ID> m_selected_object_id;
};

struct AppContext {
  explicit AppContext(std::unique_ptr<ISimulation> p_simulation)
      : simulation(std::move(p_simulation)) {}

  std::unique_ptr<ISimulation> simulation;
  UIContext ui;
  NetworkGraph network;
  ViewportContext viewport;
  PlaybackContext playback;
  SelectionContext selection;

  Object *find_object_by_id(Object::ID p_id) {
    if (simulation) {
      if (Object *object = simulation->find_object_by_id(p_id)) {
        return object;
      }
    }

    return network.get_node_by_id(p_id);
  }

  Object *get_selected_object() {
    const std::optional<Object::ID> selected_id = selection.get_selected_id();
    if (!selected_id) {
      return nullptr;
    }

    Object *object = find_object_by_id(*selected_id);
    if (!object) {
      selection.clear();
    }

    return object;
  }
};

} // namespace evosim
