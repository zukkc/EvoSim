cmake_minimum_required(VERSION 3.25)

project(
    EvoSim
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(raylib)

add_executable(
    evosim
    src/main.cpp
    src/simulation/World.cpp
    src/simulation/Agent.cpp
    src/simulation/Food.cpp
)

target_include_directories(
    evosim
    PRIVATE
        src
)

target_link_libraries(
    evosim
    PRIVATE
        raylib
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