cmake_minimum_required(VERSION 3.16)

project(lox
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lox
    src/main.cpp
    src/Lox.cpp
    src/Token.cpp
    src/Scanner.cpp
    src/Parser.cpp


)

target_include_directories(lox
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)