cmake_minimum_required(VERSION 3.0.0)
project(cpp-chat-client VERSION 0.1.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include_directories(src)

add_subdirectory(src)
add_subdirectory(lib/googletest)

include(CPack)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif()