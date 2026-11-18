cmake_minimum_required(VERSION 3.28)
project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # lets the editor find include paths

# Library: the code we test.
add_library(raytracer_core src/hello.cpp src/math/vector.cpp src/ray/ray.cpp src/camera/camera.cpp src/geometry/sphere.cpp)
target_include_directories(raytracer_core PUBLIC src)

# Program: the Hello World demo.
add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core)

# Tests (Catch2, version fixed).
include(CTest)
include(FetchContent)
FetchContent_Declare(
  Catch2
  URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.7.1.tar.gz
)
FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

add_executable(raytracer_tests tests/hello_test.cpp tests/float_test.cpp tests/math/vector_test.cpp tests/ray/ray_test.cpp tests/camera/camera_test.cpp tests/geometry/sphere_test.cpp)
target_link_libraries(raytracer_tests PRIVATE raytracer_core Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(raytracer_tests)
