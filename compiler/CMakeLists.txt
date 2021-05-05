project(compiler)

add_executable(main main.cpp
        ../parser/driver.cpp
        ../parser/scanner.cpp
        ../parser/parser.cpp)

target_include_directories(main PUBLIC ..)
