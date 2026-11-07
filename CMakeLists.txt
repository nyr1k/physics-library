cmake_minimum_required(VERSION 3.20)
project(
    physics_library
    VERSION 0.1 
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(phys_lib INTERFACE
)

target_include_directories(phys_lib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(phys_lib INTERFACE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic;-Wconversion;-O3;-march=native>
)

add_executable(phys_sim main.cpp)
target_link_libraries(phys_sim PRIVATE phys_lib)

add_executable(phys_unit 
    tests/test.cpp
)
target_link_libraries(phys_unit PRIVATE phys_lib)