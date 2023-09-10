set(BINARY ${CMAKE_PROJECT_NAME}_test)

set(SOURCES
    main.cc
    
    model/networking/utility/buffer-writer-reader_test.cc
    model/networking/utility/encode-decode_test.cc
    model/networking/utility/insecure-data-handler_test.cc
    model/networking/utility/secure-data-handler_test.cc
)

add_executable(${BINARY} ${SOURCES})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gtest_main)

add_test(NAME ${BINARY} COMMAND ${BINARY})

# Keep CACHE clear
mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

# Keep IDEs that support folders clean
set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)