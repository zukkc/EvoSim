#pragma once

#include <evosim/ISimulation.h>

#include <memory>

namespace evosim {

int run(std::unique_ptr<ISimulation> p_simulation);

} // namespace evosim
