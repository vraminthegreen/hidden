cmake_minimum_required(VERSION 3.16)
project(EvilEye CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch Raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

add_executable(EvilEye
    src/main.cpp
    src/Game.cpp
    src/Map.cpp
    src/UI.cpp
    src/Entity.cpp
    src/Eye.cpp
    src/Crystal.cpp
    src/Enemy.cpp
    src/Input.cpp
    src/Blueprint.cpp
    src/Minion.cpp
    src/Reward.cpp
)

target_link_libraries(EvilEye PRIVATE raylib)
