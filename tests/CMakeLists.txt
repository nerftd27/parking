project(Parkinkg_tests)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME} test1.cpp)
target_link_libraries(${PROJECT_NAME} gtest gtest_main)
