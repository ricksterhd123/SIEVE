cmake_minimum_required(VERSION 3.10)

project(SIEVE CXX)

add_executable(SIEVE SIEVE.cpp)

# add_library(gmp STATIC lib/gmp-6.3.0)

target_link_directories(SIEVE PUBLIC ~/opt/lib)
target_include_directories(SIEVE PUBLIC ~/opt/include)
target_link_libraries(SIEVE PUBLIC gmp gmpxx)
