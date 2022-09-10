cmake_minimum_required(VERSION 3.11)

project(cpp-chat-client VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include_directories(src /usr/local/include)
link_directories(/usr/local/lib)

find_package(Git REQUIRED)

# update git submodules
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

find_package(OpenSSL REQUIRED)
find_package(Libevent CONFIG REQUIRED)

add_subdirectory(lib/json)

add_subdirectory(src)

add_subdirectory(lib/googletest)
add_subdirectory(test)