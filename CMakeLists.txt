cmake_minimum_required (VERSION 3.10)
project (RTTI_Example)
add_definitions(-std=c++1z)
#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")
add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions" "-fno-rtti"
  "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)
add_executable(RTTI_Example ${SOURCES})
include_directories(include)

add_executable(run_benchmark benchmark/run.cpp src/Button.cpp src/TextLabel.cpp)
target_link_libraries(run_benchmark benchmark benchmark_main pthread)