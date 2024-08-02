CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

PROJECT(chepp)

SET(CMAKE_CXX_STANDARD 23)

FILE(GLOB_RECURSE source_files CONFIGURE_DEPENDS "src/*")

add_library(chepp_lib STATIC ${source_files})
TARGET_INCLUDE_DIRECTORIES(chepp_lib PUBLIC "include/")

ADD_EXECUTABLE(chepp main.cpp)
target_link_libraries(chepp PRIVATE chepp_lib)
