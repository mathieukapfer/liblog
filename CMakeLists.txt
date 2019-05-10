# use cmake test framework
enable_testing()

# force c++
SET(CMAKE_C_COMPILER ${CMAKE_CXX_COMPILER})

# library generation
add_library(log STATIC
log_const.h
formater/log_event.h
formater/log_event.cpp
node/Node.h
node/NodeVisitorI.h
node/Node.cpp
LogFile.h
log_level.cpp
log_level.h
LogFile.cpp
internal/log_macro.h
logNode/LogNodeFactory.h
logNode/LogNodeFactory.cpp
logNode/LogNodeVisitor_ShowTree.h
logNode/LogNodeVisitor_ConfigureLevel.cpp
logNode/LogNodeVisitor_ConfigureLevel.h
logNode/LogNode.cpp
logNode/LogNode.h
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
