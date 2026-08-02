#include "Simulation.h"
#include "Agent.h"
#include "raylib.h"
#include <cstddef>
#include <memory>

Simulation::Simulation() {
  m_population.reserve(20);

  for (int i = 0; i < 20; i++) {
    int random_x = GetRandomValue(0, 1919);
    int random_y = GetRandomValue(0, 1079);
    m_population.push_back(std::make_unique<Agent>(
        Vector2{static_cast<float>(random_x), static_cast<float>(random_y)}));
  }

  m_food.reserve(20);
  for (int i = 0; i < 20; i++) {
    int random_x = GetRandomValue(0, 1919);
    int random_y = GetRandomValue(0, 1079);
    m_food.push_back(std::make_unique<Food>(
        Vector2{static_cast<float>(random_x), static_cast<float>(random_y)}));
  }
}

void Simulation::update(float p_dt) {
  std::vector<std::unique_ptr<Agent>> offspring;

  for (const auto &agent : m_population) {
    if (agent == nullptr) {
      continue;
    }

    agent->update(p_dt, m_food);

    // sprawdzanie czy trzeba dodac dzieciaki do kolejki spawnowania
    if (agent->get_energy() > agent->get_reproduce_threshold() &&
        agent->get_reproduction_cooldown() <= 0) {
      Genome gens = agent->repruduce();
      offspring.push_back(std::make_unique<Agent>(agent->get_position(), gens));
    }
  }

  // spawnowanie kolejki dzieciakow
  for (auto &child : offspring) {
    m_population.push_back(std::move(child));
  }

  std::erase_if(m_population, [](const std::unique_ptr<Agent> &agent) {
    return agent == nullptr || agent->is_dead();
  });

  for (auto &food : m_food) {
    if (food->is_consumed()) {
      int random_x = GetRandomValue(0, 1919);
      int random_y = GetRandomValue(0, 1079);
      food->set_position(
          Vector2{static_cast<float>(random_x), static_cast<float>(random_y)});
      food->set_energy(0.2F);
    }
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

size_t Simulation::get_agent_count() {
  return m_population.size();
}