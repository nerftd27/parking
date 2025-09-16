project(Parkinkg_tests)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME}
    component.cpp
    areaUnits.cpp
    barrierUnits.cpp
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC 
        gtest
        gtest_main
        BrakeParking
)
