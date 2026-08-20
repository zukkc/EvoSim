#include "EvolutionSimulation.h"
#include "Agent.h"
#include "Food.h"

#include "imgui.h"
#include "raylib.h"

#include <array>
#include <cstddef>
#include <memory>

namespace evosim {

EvolutionSimulation::EvolutionSimulation() {
  m_population.reserve(20);
  for (int i = 0; i < 20; i++) {
    m_population.push_back(create_agent({}));
  }

  m_food.reserve(20);
  for (int i = 0; i < 20; i++) {
    m_food.push_back(create_food({}));
  }
}

EvolutionSimulation::~EvolutionSimulation() = default;

void EvolutionSimulation::update(float p_dt) {
  std::vector<std::unique_ptr<Agent>> offspring;
  std::vector<std::unique_ptr<Food>> new_food;

  for (const auto &agent : m_population) {
    if (agent == nullptr) {
      continue;
    }

    agent->update(p_dt, m_food);

    if (agent->get_energy() > agent->get_reproduce_threshold() &&
        agent->get_reproduction_cooldown() <= 0) {
      offspring.push_back(
          create_agent({.position = agent->get_transform().position,
                        .genome = agent->repruduce()}));
    }
  }

  // erese dead agents
  std::erase_if(m_population, [](const std::unique_ptr<Agent> &agent) {
    if (agent == nullptr)
      return true;

    return agent->is_dead();
  });

  // erese eaten food
  std::erase_if(m_food, [this, &new_food](const std::unique_ptr<Food> &food) {
    const bool is_food_eaten = food == nullptr || food->is_consumed();
    if (is_food_eaten) {
      new_food.push_back(create_food(FoodSpawnParams()));
    }
    return is_food_eaten;
  });

  // move offspring from queue to world
  for (auto &child : offspring) {
    m_population.push_back(std::move(child));
  }

  // move new_food from queue to world
  for (auto &food : new_food) {
    m_food.push_back(std::move(food));
  }
}

void EvolutionSimulation::render() const {
  for (const auto &agent : m_population) {
    if (agent == nullptr) {
      continue;
    }

    agent->render();
  }

  for (const auto &food : m_food) {
    if (food == nullptr) {
      continue;
    }

    food->render();
  }
}

Object *EvolutionSimulation::find_object_at(Vector2 world_position) {
  for (auto &agent : m_population) {
    if (is_point_inside_agent(world_position, *agent)) {
      return agent.get();
    }
  }

  for (auto &food : m_food) {
    if (is_point_inside_agent(world_position, *food)) {
      return food.get();
    }
  }

  return nullptr;
}

Object *EvolutionSimulation::find_object_by_id(Object::ID p_id) {
  for (auto &agent : m_population) {
    if (agent && agent->get_id() == p_id) {
      return agent.get();
    }
  }

  for (auto &food : m_food) {
    if (food && food->get_id() == p_id) {
      return food.get();
    }
  }

  return nullptr;
}

void EvolutionSimulation::render_selection_overlay(
    const Object &p_object) const {
  const auto *world_object = dynamic_cast<const WorldObject *>(&p_object);
  if (world_object) {
    world_object->render_selection_overlay();
  }
}

void EvolutionSimulation::draw_inspector(Object &p_object) {
  if (auto *agent = dynamic_cast<Agent *>(&p_object)) {
    if (agent->is_dead()) {
      ImGui::TextUnformatted("Agent died");
      return;
    }

    ImGui::Text("Agent ID: %llu",
                static_cast<unsigned long long>(agent->get_id()));
    ImGui::Text("Energy: %f", agent->get_energy());
    ImGui::Text("Position: x=%f, y=%f", agent->get_transform().position.x,
                agent->get_transform().position.y);
    ImGui::Text("Reproduction threshold: %f",
                agent->get_reproduce_threshold());
    ImGui::Text("Reproduction cooldown remaining: %f",
                agent->get_reproduction_cooldown());

    const Genome &genome = agent->get_genome();
    constexpr std::array input_names{
        "Direction to food", "Distance to food", "Energy",
        "Distance to border", "null", "bias",
    };
    constexpr std::size_t input_count = input_names.size();

    constexpr ImGuiTableFlags flags = ImGuiTableFlags_Borders |
                                      ImGuiTableFlags_RowBg |
                                      ImGuiTableFlags_SizingStretchProp;

    if (ImGui::BeginTable("Genome", 3, flags)) {
      ImGui::TableSetupColumn("Input", ImGuiTableColumnFlags_WidthStretch,
                              2.0F);
      ImGui::TableSetupColumn("Direction", ImGuiTableColumnFlags_WidthStretch,
                              1.0F);
      ImGui::TableSetupColumn("Speed", ImGuiTableColumnFlags_WidthStretch,
                              1.0F);
      ImGui::TableHeadersRow();

      for (std::size_t input = 0; input < input_count; ++input) {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TextUnformatted(input_names[input]);
        ImGui::TableSetColumnIndex(1);
        ImGui::Text("%.3f", genome[input]);
        ImGui::TableSetColumnIndex(2);
        ImGui::Text("%.3f", genome[input_count + input]);
      }

      ImGui::EndTable();
    }
    return;
  }

  if (auto *food = dynamic_cast<Food *>(&p_object)) {
    if (food->is_consumed()) {
      ImGui::TextUnformatted("Food eaten");
    } else {
      ImGui::Text("Food ID: %llu",
                  static_cast<unsigned long long>(food->get_id()));
    }
  }
}

void EvolutionSimulation::draw_statistics() {
  ImGui::Text("Agents: %zu", get_agent_count());
  ImGui::Text("Food: %zu", m_food.size());
}

std::size_t EvolutionSimulation::get_agent_count() const {
  return m_population.size();
}

/////////////////////////////////////

std::unique_ptr<Agent> EvolutionSimulation::create_agent(AgentSpawnParams p_params) {
  Vector2 position =
      p_params.position ? *p_params.position : get_random_world_position();
  return std::make_unique<Agent>(position);
}

std::unique_ptr<Food> EvolutionSimulation::create_food(FoodSpawnParams p_params) {
  Vector2 position =
      p_params.position ? *p_params.position : get_random_world_position();
  return std::make_unique<Food>(position);
}

bool EvolutionSimulation::is_point_inside_agent(Vector2 p_point,
                                       const Object2D &p_object) {
  const float dx = p_point.x - p_object.get_transform().position.x;
  const float dy = p_point.y - p_object.get_transform().position.y;

  const float distance_squared = dx * dx + dy * dy;
  const float radius = p_object.get_transform().radius;

  return distance_squared <= radius * radius;
}

Vector2 EvolutionSimulation::get_random_world_position() {
  return Vector2{
      static_cast<float>(GetRandomValue(-m_spawn_distance, m_spawn_distance)),
      static_cast<float>(GetRandomValue(-m_spawn_distance, m_spawn_distance)),
  };
}

} // namespace evosim
