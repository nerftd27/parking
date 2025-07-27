cmake_minimum_required(VERSION 3.10)

project(BrakeParking VERSION 0.1)

add_library(${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        include
)

target_sources(
    ${PROJECT_NAME}
    PUBLIC
        include/interfaces.h
        include/impl.h
    PRIVATE
        src/impl.cpp
)