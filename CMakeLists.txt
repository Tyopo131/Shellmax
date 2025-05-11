cmake_minimum_required(VERSION 3.28.0)

include(FetchContent)

project(Shellmax LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(Shellmax
    "src/main.cpp"
    "src/config.cpp"
    "src/exit.cpp"
    "include/Shellmax/exit.h"
    "include/Shellmax/exit.h"
    "include/Shellmax/buffer.h"
    "src/buffer.cpp"
    "include/Shellmax/command.h"
)

FetchContent_Declare(

    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

target_include_directories(Shellmax PRIVATE "include/")
target_include_directories(Shellmax PRIVATE "include/shellmax")
target_link_libraries(Shellmax PRIVATE nlohmann_json::nlohmann_json)
