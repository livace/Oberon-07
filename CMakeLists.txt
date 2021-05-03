project(oberon)

cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-nullability-completeness -Wall -Werror -Wno-return-type-c-linkage")

include_directories(parser)
include_directories(compiler)