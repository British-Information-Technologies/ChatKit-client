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

include(FetchContent)

FetchContent_Declare(json
GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
GIT_TAG v3.9.1
)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

include(cppcheck.cmake)
include(clang-format.cmake)