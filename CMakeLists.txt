cmake_minimum_required(VERSION 3.10)

project(SistemaIoT
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(.)

set(SOURCE_FILES
    main.cpp
)

add_executable(ValdoEjecutable ${SOURCE_FILES})

