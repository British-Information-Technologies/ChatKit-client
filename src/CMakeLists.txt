set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
    main.cpp
)

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})