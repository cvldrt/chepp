cmake_minimum_required(VERSION 3.15)
project(chepp)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE board_sources CONFIGURE_DEPENDS "src/board/*.cpp")
file(GLOB_RECURSE engine_sources CONFIGURE_DEPENDS "src/engine/*.cpp")
file(GLOB_RECURSE pieces_sources CONFIGURE_DEPENDS "src/pieces/*.cpp")
file(GLOB_RECURSE utils_sources CONFIGURE_DEPENDS "src/utils/*.cpp")

set(sources 
    ${board_sources}
    ${pieces_sources}
    ${engine_sources}
    ${utils_sources}
)

add_executable(chepp 
    src/main.cpp
    ${sources}
)

target_include_directories(chepp PUBLIC 
    "include/"
    "include/board"
    "include/engine"
    "include/magic"
    "include/pieces"
    "include/utils"
)

option(DEBUG "Disable optimization and add debug information" OFF)

if(DEBUG)
    target_compile_options(chepp PRIVATE -g)
    message(STATUS "Added debug information")
else()
    target_compile_options(chepp PRIVATE -O3)
    message(STATUS "Using -O3 optimization")
endif()

target_compile_options(chepp PRIVATE -fconstexpr-depth=4096)
