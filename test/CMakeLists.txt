set(BINARY ${CMAKE_PROJECT_NAME}_test)

# file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.cc)

# set(SOURCES ${TEST_SOURCES})

set(SOURCES
    main.cc
    ../src/model/friend-functionality/friend-node.cc
    ../src/model/friend-functionality/friend-hashmap.cc
    ../src/model/friend-functionality/friend-utility.cc

    ../src/model/networking/utility/elliptic-curve-diffiehellman.cc
    ../src/model/networking/utility/sha-3-512.cc
    
    ../src/model/client-model.cc

    model/friend-functionality/friend-node_test.cc
    model/friend-functionality/friend-hashmap_test.cc
    model/friend-functionality/friend-utility_test.cc
    
    model/networking/utility/elliptic-curve-diffiehellman_test.cc
    model/networking/utility/sha-3-512_test.cc

    model/client-model_test.cc
)

add_executable(${BINARY} ${SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)

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