set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
    controller/client-controller.cc
    controller/view-factory.cc
    controller/addfriend-observer.cc
    controller/deletefriend-observer.cc

    model/networking/utility/elliptic-curve-diffiehellman.cc
    model/networking/utility/sha-3-256.cc
    model/networking/utility/aes-gcm.cc
    model/networking/utility/base64.cc
    model/networking/utility/buffer-writer.cc
    model/networking/utility/buffer-reader.cc
    model/networking/utility/socket-handler.cc
    model/networking/utility/secure-socket-handler.cc
    model/networking/utility/insecure-socket-handler.cc
    
    model/networking/server/server-connection.cc

    model/friend-functionality/friend-hashmap.cc
    model/friend-functionality/friend-utility.cc
    model/friend-functionality/friend-node.cc

    model/message-functionality/client-stream-in/update-message.cc
    model/message-functionality/client-stream-in/send-message.cc
    model/message-functionality/client-stream-in/send-global-message.cc
    model/message-functionality/client-stream-in/disconnect-message.cc

    model/message-functionality/client-stream-out/connect-message.cc

    model/client-model.cc

    view/gui-view.cc

    main.cc
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

find_package(OpenSSL REQUIRED)

add_executable(${BINARY}_run ${SOURCES})
target_link_directories(${BINARY}_run PRIVATE ${GTKMM_LIBRARY_DIRS})
target_include_directories(${BINARY}_run PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(${BINARY}_run PRIVATE ${GTKMM_LIBRARIES} OpenSSL::SSL nlohmann_json::nlohmann_json)

add_library(${BINARY}_lib STATIC ${SOURCES})
target_link_directories(${BINARY}_lib PRIVATE ${GTKMM_LIBRARY_DIRS})
target_include_directories(${BINARY}_lib PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(${BINARY}_lib PRIVATE ${GTKMM_LIBRARIES} OpenSSL::SSL nlohmann_json::nlohmann_json)

# Don't want to copy if we're building in the source dir
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)

    # List of resources
    set(data_SHADOW resources/mickyb18-chat-client.glade)

    foreach(item IN LISTS data_SHADOW)
        message(STATUS ${item})
        add_custom_command(
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
        )
    endforeach()
endif()

# Files only copied if a target depends on them
add_custom_target(data-target ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/resources/mickyb18-chat-client.glade")