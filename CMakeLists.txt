# library generation
add_library(log STATIC
LogNodeVisitor_ShowTree.h
LogNodeVisitor_ConfigureLevel.cpp
log_event.h
log_const.h
LogNodeFactory.h
log_event.cpp
node/Node.h
node/NodeVisitorI.h
node/Node.cpp
LogFile.h
LogNode.cpp
log_level.cpp
LogNode.h
log_level.h
LogFile.cpp
log_macro.h
LogNodeVisitor_ConfigureLevel.h
log.h
LogNodeFactory.cpp
log_utils.cpp
parse/parseConfigurationString.cpp
)

# include dir
include_directories(node)
include_directories(parse)

# sub dir
add_subdirectory(test)
