cmake_minimum_required(VERSION 3.1)
project(MPAGSCipher VERSION 0.1.0)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(mpags-cipher
               
               MPAGScipher/mpags-cipher_main.cpp
               MPAGScipher/processCommandLine.cpp
               MPAGScipher/transformChar.cpp 
               MPAGScipher/runCaesarCipher.cpp)
               
               

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wshadow -pedantic ")

set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_STANDARD 17)

target_compile_features(mpags-cipher
   PRIVATE cxx_auto_type cxx_range_for cxx_uniform_initialization
  )

