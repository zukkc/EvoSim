cmake_minimum_required(VERSION 3.25)

project(
    EvoSim
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# --------------------------------------------------
# raylib
# --------------------------------------------------

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(raylib)

# --------------------------------------------------
# Dear ImGui
# --------------------------------------------------

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.92.7-docking
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(imgui)

# --------------------------------------------------
# rlImGui
# --------------------------------------------------

FetchContent_Declare(
    rlimgui
    GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
    GIT_TAG Raylib_6_0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(rlimgui)

# --------------------------------------------------
# Target Dear ImGui
# --------------------------------------------------

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
)

target_include_directories(imgui
    PUBLIC
        ${imgui_SOURCE_DIR}
)

# Opcjonalne ostrzeżenia tylko dla naszego targetu
target_compile_features(imgui PUBLIC cxx_std_20)

# --------------------------------------------------
# Target rlImGui
# --------------------------------------------------

add_library(rlimgui STATIC
    ${rlimgui_SOURCE_DIR}/rlImGui.cpp
)

target_include_directories(rlimgui
    PUBLIC
        ${rlimgui_SOURCE_DIR}
)

target_link_libraries(rlimgui
    PUBLIC
        raylib
        imgui
)

target_compile_features(rlimgui PUBLIC cxx_std_20)

add_executable(
    evosim
    src/main.cpp
    src/app/Application.cpp
    src/app/Window.cpp
    src/layers/SimulationLayer.cpp
    src/layers/EditorLayer.cpp
    src/simulation/Simulation.cpp
    src/simulation/Agent.cpp
    src/simulation/Food.cpp
    src/neural/NeuralNetwork.cpp
    src/ui/Theme.cpp
    src/ui/ViewportPanel.cpp
    src/ui/InspectorPanel.cpp
    src/ui/StatisticsPanel.cpp
)

target_include_directories(
    evosim
    PRIVATE
        src
)

target_link_libraries(
    evosim
    PRIVATE
        rlimgui
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(
        evosim
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wshadow
    )
elseif(MSVC)
    target_compile_options(
        evosim
        PRIVATE
            /W4
            /permissive-
    )
endif()