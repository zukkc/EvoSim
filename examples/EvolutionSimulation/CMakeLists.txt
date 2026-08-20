add_executable(
    evolution-simulation
    src/main.cpp
    src/EvolutionSimulation.cpp
    src/Agent.cpp
    src/Food.cpp
)

target_link_libraries(
    evolution-simulation
    PRIVATE EvoSim::EvoSim
)

target_include_directories(
    evolution-simulation
    PRIVATE src
)
