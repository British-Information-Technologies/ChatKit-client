set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
    controller/client-controller.cc
    controller/view-factory.cc
    
    controller/observers/addfriend-observer.cc
    controller/observers/deletefriend-observer.cc
    controller/observers/send-message-observer.cc

    controller/networking/network-receiver.cc

    controller/networking/callbacks/read-callback.cc
    controller/networking/callbacks/error-callback.cc

    model/networking/connection.cc
    model/networking/connection-factory.cc
    model/networking/network-sender.cc

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

    model/server-functionality/server-hashmap.cc
    model/server-functionality/server-utility.cc
    model/server-functionality/server-node.cc

    model/message-functionality/client-stream-out/update-command.cc
    model/message-functionality/client-stream-out/send-message-command.cc
    model/message-functionality/client-stream-out/send-global-message-command.cc
    model/message-functionality/client-stream-out/disconnect-command.cc

    model/message-functionality/client-stream-in/connect-command.cc
    model/message-functionality/client-stream-in/user-message-command.cc
    model/message-functionality/client-stream-in/global-message-command.cc
    model/message-functionality/client-stream-in/update-command.cc
    model/message-functionality/client-stream-in/disconnected-command.cc
    model/message-functionality/client-stream-in/error-command.cc

    model/message-functionality/network-stream-in/request-command.cc
    model/message-functionality/network-stream-in/got-info-command.cc
    model/message-functionality/network-stream-in/connecting-command.cc
    model/message-functionality/network-stream-in/key-command.cc

    model/message-functionality/network-stream-out/connect-command.cc
    model/message-functionality/network-stream-out/info-command.cc
    model/message-functionality/network-stream-out/encrypt-command.cc

    model/message-functionality/general/invalid-command.cc

    model/message-functionality/client-stream-in-factory.cc
    model/message-functionality/client-stream-out-factory.cc
    model/message-functionality/network-stream-in-factory.cc
    model/message-functionality/network-stream-out-factory.cc

    model/client-model.cc

    view/MainApplication.cc

    main.cc
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(${BINARY}_run ${SOURCES})
target_link_directories(${BINARY}_run PRIVATE ${GTKMM_LIBRARY_DIRS})
target_include_directories(${BINARY}_run PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(${BINARY}_run PRIVATE ${GTKMM_LIBRARIES} OpenSSL::SSL nlohmann_json::nlohmann_json libevent::core libevent::extra libevent::pthreads)

add_library(${BINARY}_lib STATIC ${SOURCES})
target_link_directories(${BINARY}_lib PRIVATE ${GTKMM_LIBRARY_DIRS})
target_include_directories(${BINARY}_lib PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(${BINARY}_lib PRIVATE ${GTKMM_LIBRARIES} OpenSSL::SSL nlohmann_json::nlohmann_json libevent::core libevent::extra libevent::pthreads)

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