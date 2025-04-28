cmake_minimum_required(VERSION 3.24)
project(Whitted)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++20")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB SOURCE_FILES "src/*.cpp")

get_filename_component(main_cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ABSOLUTE)
list(REMOVE_ITEM SOURCE_FILES ${main_cpp})

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

enable_testing()

file(GLOB TEST_FILES "test/*.cpp")
add_executable(
        test_app ${SOURCE_FILES} ${TEST_FILES}
)
target_link_libraries(
        test_app
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_app)