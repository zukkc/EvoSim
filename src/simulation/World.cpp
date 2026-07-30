#include "World.h"
#include "Agent.h"

World::World() {
  m_population.reserve(20);
  for (int i = 0; i < 20; i++) {
    int randomX = GetRandomValue(0, 1919);
    int randomY = GetRandomValue(0, 1079);
    Agent *agent = new Agent(randomX, randomY);
    m_population.push_back(agent);
  }

  m_food.reserve(20);
  for (int i = 0; i < 20; i++) {
    int randomX = GetRandomValue(0, 1919);
    int randomY = GetRandomValue(0, 1079);
    Food *food = new Food(randomX, randomY);
    m_food.push_back(food);
  }
}

World::~World() {
  for (Agent *agent : m_population) {
    delete agent;
  }
}

void World::update() {
  for (const auto &agent : m_population) {
    if (agent == nullptr) {
      continue;
    }

    agent->update(m_food);
  }
}

void World::render() {
  ClearBackground(backgroundColor);

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