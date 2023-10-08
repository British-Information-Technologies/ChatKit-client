set(BINARY ${CMAKE_PROJECT_NAME})

set(RESOURCE_LIST
    view/res/login.ui
    view/res/main.ui
    view/res/friend_list.ui
    view/res/server_list.ui
    view/res/profile_card.ui
    view/res/friend_profile_card.ui
    view/res/homepage.ui
    view/res/add_friend.ui
    view/res/direct_message.ui
 
    view/res/panel_style.css
)

compile_gresources(
    RESOURCE_FILE
    XML_OUT
    TYPE BUNDLE
    RESOURCES ${RESOURCE_LIST}
)

add_custom_target(glib-resource-target ALL DEPENDS ${RESOURCE_FILE})

set(SOURCES
    # controller
    view-model/injector.cc
    
    view-model/network-view-model.cc
    view-model/account-view-model.cc

    # model
    model/injector.cc
    
    model/data-model.cc
    model/network-model.cc

    model/friend-functionality/friend-hashmap.cc
    model/friend-functionality/friend-node.cc
    model/friend-functionality/friend-utility.cc

    model/server-functionality/server-hashmap.cc
    model/server-functionality/server-node.cc
    model/server-functionality/server-utility.cc

    model/networking/network-manager.cc
    
    model/networking/connection/connection-factory.cc
    model/networking/connection/connection.cc
    model/networking/connection/server-connection.cc
    model/networking/connection/client-connection.cc
    
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
    
    model/networking/messages/stream-in/client/send-message.cc

    model/networking/messages/stream-out/network/connect.cc
    model/networking/messages/stream-out/network/info.cc

    model/networking/messages/stream-out/server/disconnect.cc
    model/networking/messages/stream-out/server/get-clients.cc
    model/networking/messages/stream-out/server/get-messages.cc
    model/networking/messages/stream-out/server/send-global-message.cc
    model/networking/messages/stream-out/server/send-message.cc
    model/networking/messages/stream-out/server/public-key.cc
    
    model/networking/messages/stream-out/client/send-message.cc

    model/networking/utility/encode.cc
    model/networking/utility/decode.cc
    model/networking/utility/buffer-reader.cc
    model/networking/utility/buffer-writer.cc
    model/networking/utility/insecure-data-handler.cc
    model/networking/utility/secure-data-handler.cc

    # view
    view/injector.cc

    view/MainApplication.cc

    view/main/main-application-window.cc

    view/main/left/friend-list-box.cc
    view/main/left/server-list-box.cc
    view/main/left/friend-profile-card-button.cc

    view/main/right/add-friend-box.cc
    view/main/right/direct-message-box.cc
    
    view/login/login-application-window.cc

    # root
    injector.cc
    main.cc
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_definitions(${GTKMM_CFLAGS_OTHER})

add_executable(${BINARY}_run ${SOURCES})
target_link_directories(${BINARY}_run PRIVATE ${GTKMM_LIBRARY_DIRS})
target_include_directories(${BINARY}_run PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(${BINARY}_run PRIVATE ${GTKMM_LIBRARIES} nlohmann_json::nlohmann_json event sodium msd_channel fmt magic_enum::magic_enum)

add_library(${BINARY}_lib STATIC ${SOURCES})
target_link_directories(${BINARY}_lib PRIVATE ${GTKMM_LIBRARY_DIRS})
target_include_directories(${BINARY}_lib PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(${BINARY}_lib PRIVATE ${GTKMM_LIBRARIES} nlohmann_json::nlohmann_json event sodium msd_channel fmt magic_enum::magic_enum)

# Don't want to copy if we're building in the source dir
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    # List of resources to add a copy rule
    set(data_SHADOW
        view/res/add-friend.png
        view/res/add-server.png
        view/res/delete-friend.png
        view/res/delete-server.png
        view/res/friendlist.png
        view/res/headphone.png
        view/res/homepage.png
        view/res/mic.png
        view/res/notification.png
        view/res/search-icon.png
        view/res/serverlist.png
        view/res/settings.png
        view/res/signal_00.png
        view/res/signal_01.png
        view/res/signal_02.png
        view/res/signal_03.png
        view/res/signal_04.png
        view/res/user-profile.png
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
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/add-friend.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/add-server.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/delete-friend.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/delete-server.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/friendlist.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/headphone.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/homepage.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/mic.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/notification.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/search-icon.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/serverlist.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/settings.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/signal_00.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/signal_01.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/signal_02.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/signal_03.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/signal_04.png"
    "${CMAKE_CURRENT_BINARY_DIR}/view/res/user-profile.png"
)

add_dependencies(${BINARY}_run glib-resource-target data-target)