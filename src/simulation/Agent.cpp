#include "Agent.h"
#include "Food.h"
#include "core/InspectorVisitor.h"
#include "neuralnetwork/NeuralNetwork.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <memory>
#include <raylib.h>
#include <sys/types.h>
#include <vector>

namespace evosim {

constexpr float k_max_speed = 100.0F;
constexpr float k_turn_speed = 2.0F;
constexpr float k_energy_cost_per_pixel = 0.001F;

Agent::Agent(Vector2 p_position)
    : Object2D(p_position, 10),
      m_neural_network(std::make_unique<NeuralNetwork>()) {}

Agent::Agent(Vector2 p_position, std::array<float, 12> p_genome)
    : Object2D(p_position, 10),
      m_neural_network(std::make_unique<NeuralNetwork>(p_genome)) {}

Agent::~Agent() = default;

void Agent::accept_inspector(InspectorVisitor &p_visitor) {
  p_visitor.inspect(*this);
}

void Agent::update(float p_deltaTime,
                   const std::vector<std::unique_ptr<Food>> &p_all_food) {
  if (m_reproduction_cooldown > 0) {
    m_reproduction_cooldown -= p_deltaTime;
  }

  const ClosestFoodData closest = find_closest(p_all_food);
  if (closest.distance <= 10) {
    m_energy += closest.food->consume();
    return;
  }

  const float screen_width = static_cast<float>(GetScreenWidth());
  const float screen_height = static_cast<float>(GetScreenHeight());
  const float screen_diagonal = std::hypot(screen_width, screen_height);
  const float max_border_distance =
      std::min(screen_width, screen_height) * 0.5F;

  std::array<float, 5> inputs{
      closest.direction / PI, closest.distance / screen_diagonal,
      std::clamp(m_energy, 0.0F, 1.0F),
      std::clamp(get_distance_to_border() / max_border_distance, 0.0F, 1.0F),
      0.0F};

  auto outputs = m_neural_network->forward(inputs);

  m_speed = outputs[0] * k_max_speed;

  const float turn_input = outputs[1];

  m_transform.rotation += turn_input * k_turn_speed * p_deltaTime;

  m_transform.position.x +=
      std::cos(m_transform.rotation) * m_speed * p_deltaTime;
  m_transform.position.y +=
      std::sin(m_transform.rotation) * m_speed * p_deltaTime;

  m_energy -= std::abs(m_speed) * k_energy_cost_per_pixel * p_deltaTime;
}

void Agent::render() const {
  DrawCircleV(m_transform.position, m_transform.radius, WHITE);

  DrawRectangleV(
      {m_transform.position.x - 20.0F, m_transform.position.y - 20.0F},
      {40.0F, 5.0F}, GRAY);

  DrawRectangleV(
      {m_transform.position.x - 20.0F, m_transform.position.y - 20.0F},
      {40.0F * std::clamp(m_energy, 0.0F, 1.0F), 5.0F}, RED);
}

Genome Agent::repruduce() {
  m_reproduction_cooldown = 5.F;
  return m_neural_network->mutate();
}

bool Agent::is_dead() const { return m_energy <= 0; }
float Agent::get_energy() const { return m_energy; }
const Genome &Agent::get_genome() const {
  return m_neural_network->get_genome();
}
float Agent::get_reproduce_threshold() const {
  return m_reproduction_threshold;
}
float Agent::get_reproduction_cooldown() const {
  return m_reproduction_cooldown;
}

// ================================================= //

ClosestFoodData
Agent::find_closest(const std::vector<std::unique_ptr<Food>> &p_all_food) {
  ClosestFoodData result{nullptr, 0.0f, 0.0f};

  float closest_distance_squared = std::numeric_limits<float>::max();

  for (const auto &food : p_all_food) {
    if (!food) {
      continue;
    }

    const Vector2 &pos = food->get_transform().position;
    const float dx = static_cast<float>(pos.x) - m_transform.position.x;
    const float dy = static_cast<float>(pos.y) - m_transform.position.y;

    const float distance_squared = dx * dx + dy * dy;

    if (distance_squared < closest_distance_squared) {
      closest_distance_squared = distance_squared;

      result.food = food.get();
      result.distance = std::sqrt(distance_squared);
      const float target_direction = std::atan2(dy, dx);
      result.direction =
          std::atan2(std::sin(target_direction - m_transform.rotation),
                     std::cos(target_direction - m_transform.rotation));
    }
  }

  return result;
}

float Agent::get_distance_to_border() const {
  const float left = m_transform.position.x;
  const float right =
      static_cast<float>(GetScreenWidth()) - m_transform.position.x;
  const float top = m_transform.position.y;
  const float bottom =
      static_cast<float>(GetScreenHeight()) - m_transform.position.y;

  return std::min(std::min(left, right), std::min(top, bottom));
}

} // namespace evosim
