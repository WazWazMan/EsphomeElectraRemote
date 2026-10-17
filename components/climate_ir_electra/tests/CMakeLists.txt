cmake_minimum_required(VERSION 3.14)
project(electra_remote_tests CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_electra
    test_main.cc
    ../electra_remote_protocol.cpp
)

target_include_directories(test_electra PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(test_electra GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(test_electra)