# use cmake test framework
enable_testing()

# force c++
SET(CMAKE_C_COMPILER ${CMAKE_CXX_COMPILER})

# library generation
add_library(log STATIC
log_const.h
log_event.h
formater/log_event.cpp
Node.h
node/NodeVisitorI.h
node/Node.cpp
LogFile.h
log_level.cpp
log_level.h
LogFile.cpp
log_macro.h
LogNodeFactory.h
logNode/LogNodeFactory.cpp
logNode/LogNodeVisitor_ShowTree.h
logNode/LogNodeVisitor_ConfigureLevel.cpp
logNode/LogNodeVisitor_ConfigureLevel.h
logNode/LogNode.cpp
LogNode.h
log.h
internal/log_utils.cpp
parse/parseConfigurationString.cpp
)

# include dir
include_directories(.)
include_directories(node)
include_directories(logNode)
include_directories(parse)
include_directories(internal)
include_directories(formater)

# sub dir
add_subdirectory(test)
