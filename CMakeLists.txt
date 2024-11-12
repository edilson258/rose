cmake_minimum_required(VERSION 3.20)

project(
  Rose
  VERSION 0.1.0
  DESCRIPTION "C graphics library"
  LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_compile_options(-Wall -Wextra -Werror)

file(GLOB rose_sources "src/*.c")
add_library(rose STATIC ${rose_sources})
target_link_libraries(rose m) # link with math lib.

add_subdirectory(examples)
