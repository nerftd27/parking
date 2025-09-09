cmake_minimum_required(VERSION 3.10)

project(BrakeParking VERSION 0.1)

#set(THIRDPARTY_PARKING_LIB ${THIRDPARTY_LIB})
set(BRAKE_PARKING_LIB ${PROJECT_NAME})

add_library(${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/thirdparty
)

target_sources(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include/interfaces.h
        ${CMAKE_SOURCE_DIR}/thirdparty/thirdparty.h
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/area.h
        ${CMAKE_SOURCE_DIR}/include/accounting.h
        ${CMAKE_SOURCE_DIR}/include/accountingDB.h
        ${CMAKE_SOURCE_DIR}/include/accountingListener.h
        ${CMAKE_SOURCE_DIR}/include/barrier.h
        ${CMAKE_SOURCE_DIR}/include/barrierNotifier.h
        ${CMAKE_SOURCE_DIR}/include/parking.h

        ${CMAKE_SOURCE_DIR}/src/area.cpp
        ${CMAKE_SOURCE_DIR}/src/accounting.cpp
        ${CMAKE_SOURCE_DIR}/src/accountingDB.cpp
        ${CMAKE_SOURCE_DIR}/src/barrier.cpp
        ${CMAKE_SOURCE_DIR}/src/parking.cpp

)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        Thirdparty
)

add_subdirectory(thirdparty)
add_subdirectory(tests)