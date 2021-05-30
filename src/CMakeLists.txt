set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
    main.cpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

add_executable(${BINARY}_run ${SOURCES})
target_link_directories(${BINARY}_run PRIVATE ${GTKMM_LIBRARY_DIRS})
target_include_directories(${BINARY}_run PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(${BINARY}_run PRIVATE ${GTKMM_LIBRARIES})

add_library(${BINARY}_lib STATIC ${SOURCES})
target_link_directories(${BINARY}_lib PRIVATE ${GTKMM_LIBRARY_DIRS})
target_include_directories(${BINARY}_lib PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(${BINARY}_lib PRIVATE ${GTKMM_LIBRARIES})