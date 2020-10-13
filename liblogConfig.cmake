
message("*** Package found for " ${CMAKE_CURRENT_SOURCE_DIR})

# compilation switch to use with
include(${CMAKE_SOURCE_DIR}/src/lib/liblog/CMakeLists_LogConfig.txt)

# include path
set(log_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/src/lib/liblog ${CMAKE_SOURCE_DIR}/src/lib/liblog/src ${CMAKE_SOURCE_DIR}/src/lib/liblog/src/fifo)
# archive path
set(log_LIBRARIES ${CMAKE_BINARY_DIR}/src/lib/liblog/liblog.a )
