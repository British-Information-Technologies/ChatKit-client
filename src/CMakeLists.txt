set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
    # controller
    controller/client-controller.cc

    # model
    model/client-model.cc

    model/friend-functionality/friend-hashmap.cc
    model/friend-functionality/friend-node.cc
    model/friend-functionality/friend-utility.cc

    model/server-functionality/server-hashmap.cc
    model/server-functionality/server-node.cc
    model/server-functionality/server-utility.cc

    model/networking/connection-factory.cc
    model/networking/connection.cc
    model/networking/network-manager.cc
    model/networking/server-connection.cc
    
    model/networking/messages/message.cc

    model/networking/messages/internal/event-error.cc

    model/networking/messages/stream-in/network/connecting.cc
    model/networking/messages/stream-in/network/error.cc
    model/networking/messages/stream-in/network/got-info.cc
    model/networking/messages/stream-in/network/request.cc

    model/networking/messages/stream-in/server/client-connected.cc
    model/networking/messages/stream-in/server/client-removed.cc
    model/networking/messages/stream-in/server/connected-clients.cc
    model/networking/messages/stream-in/server/connected.cc
    model/networking/messages/stream-in/server/disconnected.cc
    model/networking/messages/stream-in/server/error.cc
    model/networking/messages/stream-in/server/global-chat-messages.cc
    model/networking/messages/stream-in/server/global-message.cc
    model/networking/messages/stream-in/server/user-message.cc
    model/networking/messages/stream-in/server/public-key.cc

    model/networking/messages/stream-out/network/connect.cc
    model/networking/messages/stream-out/network/info.cc

    model/networking/messages/stream-out/server/disconnect.cc
    model/networking/messages/stream-out/server/get-clients.cc
    model/networking/messages/stream-out/server/get-messages.cc
    model/networking/messages/stream-out/server/send-global-message.cc
    model/networking/messages/stream-out/server/send-message.cc

    model/networking/utility/buffer-reader.cc
    model/networking/utility/buffer-writer.cc
    model/networking/utility/insecure-data-handler.cc
    model/networking/utility/secure-data-handler.cc

    # view
    view/MainApplication.cc

    # root
    main.cc
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lsodium")

# todo - must change as machine specific
find_package(Libevent CONFIG REQUIRED PATHS /home/mitchell/Documents/packages/libevent/build)

add_executable(${BINARY}_run ${SOURCES})
target_link_directories(${BINARY}_run PRIVATE ${GTKMM_LIBRARY_DIRS})
target_include_directories(${BINARY}_run PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(${BINARY}_run PRIVATE ${GTKMM_LIBRARIES} nlohmann_json::nlohmann_json libevent::core libevent::extra libevent::pthreads msd_channel fmt)

add_library(${BINARY}_lib STATIC ${SOURCES})
target_link_directories(${BINARY}_lib PRIVATE ${GTKMM_LIBRARY_DIRS})
target_include_directories(${BINARY}_lib PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(${BINARY}_lib PRIVATE ${GTKMM_LIBRARIES} nlohmann_json::nlohmann_json libevent::core libevent::extra libevent::pthreads msd_channel fmt)

# Don't want to copy if we're building in the source dir
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    # List of resources to add a copy rule
    set(data_SHADOW
        view/login.ui
        view/home.ui
    )

    foreach(item IN LISTS data_SHADOW)
        message(STATUS "Item: ${item}")

        add_custom_command(
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
        )
    endforeach()
endif()

# Files only copied if a target depends on them
add_custom_target(data-target ALL DEPENDS 
    "${CMAKE_CURRENT_BINARY_DIR}/view/login.ui"
    "${CMAKE_CURRENT_BINARY_DIR}/view/home.ui"
)

add_dependencies(${BINARY}_run data-target)