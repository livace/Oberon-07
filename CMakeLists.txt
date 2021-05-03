project(oberon)

cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-nullability-completeness -Wall -Werror -Wno-return-type-c-linkage")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/")

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

add_subdirectory(parser kek/parser)
add_subdirectory(compiler kek/compiler)
