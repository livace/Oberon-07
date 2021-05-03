project(parser)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(
        HEADERS
        ${PROJECT_SOURCE_DIR}/driver.hh
        ${PROJECT_SOURCE_DIR}/parser.hh
)

BISON_TARGET(
        MyParser
        parser.y
        ${PROJECT_SOURCE_DIR}/parser.cpp
        DEFINES_FILE ${PROJECT_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
        MyScanner
        ${PROJECT_SOURCE_DIR}/scanner.l
        ${PROJECT_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_library(
    ${PROJECT_NAME}
    driver.cpp
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS}
)

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC ${PROJECT_SOURCE_DIR} ..)
    