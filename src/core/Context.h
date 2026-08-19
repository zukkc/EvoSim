#pragma once

#include "neuralnetwork/NetworkGraph.h"
#include "simulation/Simulation.h"

#include <optional>

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
  UIContext ui;
  Simulation simulation;
  NetworkGraph network;
  ViewportContext viewport;
  SelectionContext selection;

  Object *find_object_by_id(Object::ID p_id) {
    if (Object *object = simulation.get_object_by_id(p_id)) {
      return object;
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
