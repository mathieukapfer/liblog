cmake_minimum_required(VERSION 3.0)

# cross compilation
if(CROSS_COMPILE_M3)
  set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
  set(CMAKE_C_COMPILER arm-none-eabi-gcc)
endif()

if(CROSS_COMPILE_YOCTO)
  # TODO
endif()

# force c++
SET(CMAKE_C_COMPILER ${CMAKE_CXX_COMPILER})

# library generation
add_library(log STATIC
log_const.h
log_event.h
formater/log_event.cpp
node/Node.h
node/NodeVisitorI.h
node/Node.cpp
LogFile.h
log_level.cpp
log_level.h
LogFile.cpp
log_macro.h
LogFacade.h
LogFacade.cpp
logNode/LogNodeFactory.h
logNode/LogNodeFactory.cpp
logNode/LogNodeVisitor_ShowTree.h
logNode/LogNodeVisitor_ConfigureLevel.cpp
logNode/LogNodeVisitor_ConfigureLevel.h
logNode/LogNode.cpp
logNode/LogNode.h
log.h
log_internal/log_utils.cpp
parse/parseConfigurationString.cpp
)

# include dir
include_directories(.)
include_directories(node)
include_directories(logNode)
include_directories(parse)
include_directories(log_internal)
include_directories(formater)

# sub dir
if(_X86_)
  # use cmake test framework
  enable_testing()
  # add test subdir
  add_subdirectory(test)
endif()
