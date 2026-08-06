#include <array>

namespace evosim {

// in:    direction_to_food, distance_to_food, energy, distance_to_border,
// out:   speed, direction
using Genome = std::array<float, 12>;
using NeuronInputs = std::array<float, 5>;
using NeuronOutputs = std::array<float, 2>;

} // namespace evosim
