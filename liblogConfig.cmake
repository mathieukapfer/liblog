
message("*** Package found for " ${CMAKE_CURRENT_SOURCE_DIR})

# include path
set(log_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/lib/liblog )
# archive path
set(log_LIBRARIES ${CMAKE_BINARY_DIR}/lib/liblog/liblog.a )
# compilation switch to use with
include(${CMAKE_SOURCE_DIR}/lib/liblog/CMakeLists_LogConfig.txt)
