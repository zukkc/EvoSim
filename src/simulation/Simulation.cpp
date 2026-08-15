#include "Simulation.h"
#include "Agent.h"
#include "raylib.h"
#include "simulation/Food.h"
#include <cstddef>
#include <memory>

namespace evosim {
  
  constexpr float get_speed_multiplier(Simulation::Speed p_speed) {
    switch (p_speed) {
      case Simulation::Speed::FAST_X2: return 2.0f;
      case Simulation::Speed::FAST_X1: return 1.0f;
      case Simulation::Speed::NORMAL : return 1.0f;
      case Simulation::Speed::SLOW_X1: return 0.5f;
      case Simulation::Speed::SLOW_X2: return 0.25f;
    }

    return 1.0f;
}

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

Simulation::~Simulation() = default;

void Simulation::update(float p_dt) {
  if (!m_running)
    return;
  
  float delta_time = p_dt * get_speed_multiplier(m_speed);
  TraceLog(LOG_INFO, "%f", get_speed_multiplier(m_speed));
  std::vector<std::unique_ptr<Agent>> offspring;
  std::vector<std::unique_ptr<Food>> new_food;

  for (const auto &agent : m_population) {
    if (agent == nullptr) {
      continue;
    }

    agent->update(delta_time, m_food);

    if (agent->get_energy() > agent->get_reproduce_threshold() &&
        agent->get_reproduction_cooldown() <= 0) {
      offspring.push_back(
          create_agent({.position = agent->get_transform().position,
                        .genome = agent->repruduce()}));
    }
  }

  // erese dead agents
  std::erase_if(m_population, [this](const std::unique_ptr<Agent> &agent) {
    if (agent == nullptr)
      return true;

    // if agent just die and he is active in inspector then clear him out from
    // inspector
    if (agent->is_dead() && agent->is_active()) {
      m_active_object_id.reset();
    }
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

void Simulation::start_simulation() { m_running = true; }

void Simulation::end_simulation() { m_running = false; }

void Simulation::set_simulation_speed(Speed p_speed) {
  m_speed = p_speed; 
}

const Simulation::Speed &Simulation::get_simulation_speed() const {
  return m_speed;
}

Object *Simulation::find_object_at(Vector2 world_position) {
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

bool Simulation::contains_object(const Object *object) const {
  if (object == nullptr) {
    return false;
  }

  for (const auto &agent : m_population) {
    if (agent.get() == object) {
      return true;
    }
  }

  for (const auto &food : m_food) {
    if (food.get() == object) {
      return true;
    }
  }

  return false;
}

void Simulation::set_active_object(Object *p_object) {
  // set old active object to "not active"
  Object *old_object = get_active_object();
  if (old_object) {
    old_object->set_is_active(false);
  }
  m_active_object_id.reset();

  // set new object to be active
  if (p_object == nullptr) {
    return;
  }
  p_object->set_is_active(true);
  m_active_object_id = p_object->get_id();
}

Object *Simulation::get_active_object() {
  if (!m_active_object_id) {
    return nullptr;
  }

  Object *object = get_object_by_id(*m_active_object_id);

  if (object == nullptr) {
    m_active_object_id.reset();
  }

  return object;
}

Object *Simulation::get_object_by_id(Object::ID p_id) {
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

bool Simulation::is_running() const { return m_running; }
size_t Simulation::get_agent_count() { return m_population.size(); }

/////////////////////////////////////

std::unique_ptr<Agent> Simulation::create_agent(AgentSpawnParams p_params) {
  Vector2 position =
      p_params.position ? *p_params.position : get_random_world_position();
  return std::make_unique<Agent>(position);
}

std::unique_ptr<Food> Simulation::create_food(FoodSpawnParams p_params) {
  Vector2 position =
      p_params.position ? *p_params.position : get_random_world_position();
  return std::make_unique<Food>(position);
}

bool Simulation::is_point_inside_agent(Vector2 p_point,
                                       const Object2D &p_object) {
  const float dx = p_point.x - p_object.get_transform().position.x;
  const float dy = p_point.y - p_object.get_transform().position.y;

  const float distance_squared = dx * dx + dy * dy;
  const float radius = p_object.get_transform().radius;

  return distance_squared <= radius * radius;
}

Vector2 Simulation::get_random_world_position() {
  return Vector2{
      static_cast<float>(GetRandomValue(-m_spawn_distance, m_spawn_distance)),
      static_cast<float>(GetRandomValue(-m_spawn_distance, m_spawn_distance)),
  };
}

} // namespace evosim
