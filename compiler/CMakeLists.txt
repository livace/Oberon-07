project(compiler)

add_executable(main main.cpp)

find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(main parser ${llvm_libs})
target_include_directories(main PUBLIC ..)
