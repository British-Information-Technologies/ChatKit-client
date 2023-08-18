cmake_minimum_required(VERSION 3.16)

project(cpp-chat-client)
set(PROJECT_VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})


# --- find required locally installed libraries ---
find_package(PkgConfig REQUIRED)

pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(Libevent REQUIRED libevent)
pkg_check_modules(Libsodium REQUIRED libsodium)


# --- FetchContents ---
include(FetchContent)

# json
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

# thread msd channels
FetchContent_Declare(channel
    GIT_REPOSITORY https://github.com/andreiavrammsd/cpp-channel
    GIT_TAG v0.7.3
)
FetchContent_MakeAvailable(channel)
include_directories(${channel_SOURCE_DIR}/include)

# fmt (format) library
FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG 10.0.0
)
FetchContent_MakeAvailable(fmt)

# GCR_CMake extension tool
FetchContent_Declare(gcr
    GIT_REPOSITORY https://github.com/Makman2/GCR_CMake
    GIT_TAG 4.0
)
FetchContent_MakeAvailable(gcr)
list(APPEND CMAKE_MODULE_PATH ${gcr_SOURCE_DIR}/macros)
include(GlibCompileResourcesSupport)


# --- setup src ---
include_directories(src /usr/local/include)
link_directories(/usr/local/lib)

add_subdirectory(src)
#add_subdirectory(lib/googletest)


# --- enable GoogleTest ---
#option(PACKAGE_TESTS "Build the tests" ON)
#if(PACKAGE_TESTS)
 #   enable_testing()
 #   include(GoogleTest)
    #add_subdirectory(test)
#endif()