cmake_minimum_required(VERSION 3.11)
project(cpp-chat-client VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_C_STANDARD 17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

link_directories(/usr/local/lib)

include_directories(src /usr/local/include)

add_subdirectory(src)
add_subdirectory(lib/googletest)

include(CPack)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif()

include(cppcheck.cmake)
include(clang-format.cmake)