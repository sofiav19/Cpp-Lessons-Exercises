cmake_minimum_required(VERSION 3.8)
project(ZIPFProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Matplot++ library
add_subdirectory(external/matplotplusplus)


add_library(zipf_lib INTERFACE)
target_include_directories(zipf_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(zipf_lib INTERFACE matplot)

# Build the main executable `my_executable` and link it with `zipf_lib`
add_executable(my_executable main.cxx)
target_link_libraries(my_executable PUBLIC zipf_lib)

# add_executable(my_executable main.cxx)
# target_link_libraries(my_executable PUBLIC matplot)