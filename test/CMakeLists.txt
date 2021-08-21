set(BINARY ${CMAKE_PROJECT_NAME}_test)

# file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.cc)

# set(SOURCES ${TEST_SOURCES})

set(SOURCES
    main.cc
    ../src/model/friend-functionality/friend-node.cc
    ../src/model/friend-functionality/friend-hashmap.cc
    ../src/model/friend-functionality/friend-utility.cc

    ../src/model/message-functionality/client-stream-out/update-command.cc
    ../src/model/message-functionality/client-stream-out/send-message-command.cc
    ../src/model/message-functionality/client-stream-out/send-global-message-command.cc
    ../src/model/message-functionality/client-stream-out/disconnect-command.cc

    ../src/model/message-functionality/client-stream-in/connect-command.cc
    ../src/model/message-functionality/client-stream-in/user-message-command.cc
    ../src/model/message-functionality/client-stream-in/global-message-command.cc
    ../src/model/message-functionality/client-stream-in/update-command.cc
    ../src/model/message-functionality/client-stream-in/disconnected-command.cc
    ../src/model/message-functionality/client-stream-in/error-command.cc

    ../src/model/message-functionality/network-stream-in/request-command.cc
    ../src/model/message-functionality/network-stream-in/got-info-command.cc
    ../src/model/message-functionality/network-stream-in/connecting-command.cc

    ../src/model/message-functionality/network-stream-out/connect-command.cc
    ../src/model/message-functionality/network-stream-out/info-command.cc

    ../src/model/message-functionality/client-stream-in-factory.cc
    ../src/model/message-functionality/client-stream-out-factory.cc
    ../src/model/message-functionality/network-stream-in-factory.cc

    ../src/model/networking/utility/elliptic-curve-diffiehellman.cc
    ../src/model/networking/utility/sha-3-256.cc
    ../src/model/networking/utility/aes-gcm.cc
    ../src/model/networking/utility/socket-handler.cc
    ../src/model/networking/utility/secure-socket-handler.cc
    ../src/model/networking/utility/buffer-writer.cc
    ../src/model/networking/utility/buffer-reader.cc
    
    ../src/model/networking/server/server-connection.cc

    ../src/model/client-model.cc

    model/friend-functionality/friend-node_test.cc
    model/friend-functionality/friend-hashmap_test.cc
    model/friend-functionality/friend-utility_test.cc
    
    model/message-functionality/client-stream-out/update-command_test.cc
    model/message-functionality/client-stream-out/send-message-command_test.cc
    model/message-functionality/client-stream-out/send-global-message-command_test.cc
    model/message-functionality/client-stream-out/disconnect-command_test.cc

    model/message-functionality/client-stream-in/connect-command_test.cc
    model/message-functionality/client-stream-in/user-message-command_test.cc
    model/message-functionality/client-stream-in/global-message-command_test.cc
    model/message-functionality/client-stream-in/update-command_test.cc
    model/message-functionality/client-stream-in/disconnected-command_test.cc
    model/message-functionality/client-stream-in/error-command_test.cc

    model/message-functionality/network-stream-in/request-command_test.cc
    model/message-functionality/network-stream-in/got-info-command_test.cc
    model/message-functionality/network-stream-in/connecting-command_test.cc

    model/message-functionality/network-stream-out/connect-command_test.cc
    model/message-functionality/network-stream-out/info-command_test.cc

    model/message-functionality/client-stream-in-factory_test.cc
    model/message-functionality/client-stream-out-factory_test.cc
    model/message-functionality/network-stream-in-factory_test.cc

    model/networking/temporary-server.cc
    model/networking/temporary-client.cc

    model/networking/utility/elliptic-curve-diffiehellman_test.cc
    model/networking/utility/sha-3-256_test.cc
    model/networking/utility/aes-gcm_test.cc
    model/networking/utility/secure-socket-handler_test.cc
    model/networking/utility/buffer-writer-reader_test.cc

    model/networking/server/server-connection_test.cc

    model/client-model_test.cc
)

add_executable(${BINARY} ${SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest nlohmann_json::nlohmann_json)

# Keeps CACHE clearer
mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

# Keeps IDEs that support folders clean
set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)