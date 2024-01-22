cmake_minimum_required(VERSION 3.10)

project(SIEVE VERSION 1.0 LANGUAGES CXX)

add_executable(SIEVE SIEVE.cpp)

# when gmp compiled on emscripten using settings in docker image
if (EMSCRIPTEN)
  target_link_directories(SIEVE PUBLIC ~/opt/lib)
  target_include_directories(SIEVE PUBLIC ~/opt/include)
endif()

target_link_libraries(SIEVE PUBLIC gmp gmpxx)
