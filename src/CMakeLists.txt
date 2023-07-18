aux_source_directory(. SRC_LIST)
add_library(ConnectionPool SHARED ${SRC_LIST})
target_link_libraries(ConnectionPool mysqlclient pthread lua5.3)