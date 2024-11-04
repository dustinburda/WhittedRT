cmake_minimum_required(VERSION 3.24)
project(Whitted)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${CMAKE_PROJECT_NAME}
        src/main.cpp
        src/Canvas.cpp
        src/Vector.cpp
        src/Normal.cpp
        src/Point.cpp
        src/Ray.cpp
        src/Camera.cpp
        include/Camera.h
        src/Color.cpp
        include/Color.h
)

enable_testing()

add_executable(
        test_app
        test/VectorTest.cpp
)
target_link_libraries(
        test_app
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_app)