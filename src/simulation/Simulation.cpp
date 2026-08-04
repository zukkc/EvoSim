#include "Simulation.h"
#include "Agent.h"
#include "neural/NeuralNetwork.h"
#include "raylib.h"
#include <cstddef>
#include <memory>

namespace evosim {

Simulation::Simulation() {
  m_population.reserve(20);
  for (int i = 0; i < 20; i++) {
    m_population.push_back(create_agent({}));
  }

  m_food.reserve(20);
  for (int i = 0; i < 20; i++) {
    m_food.push_back(create_food({}));
  }
}

void Simulation::update(float p_dt) {
  std::vector<std::unique_ptr<Agent>> offspring;
  std::vector<std::unique_ptr<Food>> new_food;

  for (const auto &agent : m_population) {
    if (agent == nullptr) {
      continue;
    }

    agent->update(p_dt, m_food);

    if (agent->get_energy() > agent->get_reproduce_threshold() &&
        agent->get_reproduction_cooldown() <= 0) {
      Genome gens = agent->repruduce();
      offspring.push_back(
          create_agent({.position = agent->get_position(), .genome = gens}));
    }
  }

  // erese dead agents
  std::erase_if(m_population, [this](const std::unique_ptr<Agent> &agent) {
    if (agent == nullptr)
      return true;

    const bool is_agent_died = agent->is_dead();
    // if agent just die and he is active in inspector then clear him out from
    // inspector
    if (is_agent_died && m_active_in_ispector != nullptr &&
        agent->get_id() == m_active_in_ispector->get_id()) {
      m_active_in_ispector = nullptr;
    }
    return is_agent_died;
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

void Simulation::render() {
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

Agent *Simulation::find_agent_at(Vector2 world_position) {
  for (auto &agent : m_population) {
    if (is_point_inside_agent(world_position, *agent)) {
      return agent.get();
    }
  }

  return nullptr;
}

void Simulation::set_active_in_inspector(Agent *p_agent) {
  if (m_active_in_ispector != nullptr && p_agent != nullptr) {
    m_active_in_ispector->set_active(false);
  }
  if (p_agent != nullptr) {
    p_agent->set_active(true);
    m_active_in_ispector = p_agent;
  }
}

size_t Simulation::get_agent_count() { return m_population.size(); }
Agent *Simulation::get_active_in_inspector() { return m_active_in_ispector; }

/////////////////////////////////////

std::unique_ptr<Agent> Simulation::create_agent(AgentSpawnParams p_params) {
  Vector2 position =
      p_params.position ? *p_params.position : get_random_world_position();
  return std::make_unique<Agent>(m_reserved_ids++, position);
}

std::unique_ptr<Food> Simulation::create_food(FoodSpawnParams p_params) {
  Vector2 position =
      p_params.position ? *p_params.position : get_random_world_position();
  return std::make_unique<Food>(m_reserved_ids++, position);
}

bool Simulation::is_point_inside_agent(Vector2 point, const Agent &agent) {
  const float dx = point.x - agent.get_position().x;
  const float dy = point.y - agent.get_position().y;

  const float distance_squared = dx * dx + dy * dy;
  const float radius = agent.get_radius();

  return distance_squared <= radius * radius;
}

Vector2 Simulation::get_random_world_position() {
  return Vector2{
      static_cast<float>(GetRandomValue(-m_spawn_distance, m_spawn_distance)),
      static_cast<float>(GetRandomValue(-m_spawn_distance, m_spawn_distance)),
  };
}

} // namespace evosim
