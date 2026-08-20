#include <evosim/EvoSim.h>
#include "EvolutionSimulation.h"

#include <memory>

int main() {
  return evosim::run(std::make_unique<evosim::EvolutionSimulation>());
}
