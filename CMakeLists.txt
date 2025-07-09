cmake_minimum_required(VERSION 3.15)
project(chepp)

set(CMAKE_CXX_STANDARD 20)

# Main engine sources (exclude magic generator)
file(GLOB_RECURSE engine_sources CONFIGURE_DEPENDS "src/*.cpp")
list(REMOVE_ITEM engine_sources "src/magic_generator.cpp")

# Main engine library
add_library(chepp_lib STATIC ${engine_sources})
target_include_directories(chepp_lib PUBLIC "include/")

# Main executable
add_executable(chepp main.cpp)
target_link_libraries(chepp PRIVATE chepp_lib)

# Magic number generator (always built)
add_executable(mgen src/magic_generator.cpp)
target_link_libraries(mgen PRIVATE chepp_lib)

# Optimization flag option
option(USE_O3 "Enable -O3 optimization" OFF)
if(USE_O3)
    # Apply -O3 to all targets
    target_compile_options(chepp_lib PRIVATE -O3)
    target_compile_options(chepp PRIVATE -O3)
    target_compile_options(mgen PRIVATE -O3)
    message(STATUS "Using -O3 optimization")
else()
    message(STATUS "Using default optimization")
endif()
