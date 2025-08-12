cmake_minimum_required(VERSION 3.10)

project(BrakeParking VERSION 0.1)
set(BRAKE_PARKING_LIB ${PROJECT_NAME})

add_library(${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_sources(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include/interfaces.h
        ${CMAKE_SOURCE_DIR}/include/thirdparty.h
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/barrier.h
        ${CMAKE_SOURCE_DIR}/include/area.h
        ${CMAKE_SOURCE_DIR}/include/parking.h
        ${CMAKE_SOURCE_DIR}/src/barrier.cpp
        ${CMAKE_SOURCE_DIR}/src/area.cpp
        ${CMAKE_SOURCE_DIR}/src/parking.cpp
        
)

add_subdirectory(tests)