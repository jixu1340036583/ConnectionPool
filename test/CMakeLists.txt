aux_source_directory(. TEST_LIST)
add_executable(test ${TEST_LIST})
target_link_libraries(test ConnectionPool)