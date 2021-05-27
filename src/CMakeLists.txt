set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
    main.cpp
)

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})

# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtkmm-3.0)

target_link_libraries(${BINARY}_run PRIVATE ${GTKMM_LIBRARIES})

# Add other flags to the compiler
target_compile_definitions(${BINARY}_run PRIVATE ${GTKMM_CFLAGS_OTHER})

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
target_include_directories(${BINARY}_run PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_directories(${BINARY}_run PRIVATE ${GTKMM_LIBRARY_DIRS})