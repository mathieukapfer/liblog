cmake_minimum_required(VERSION 3.0)

# define project template
# ============================
# project(liblog)

include(CMakeLists_LogConfig.txt)

# force c++
# SET(CMAKE_C_COMPILER ${CMAKE_CXX_COMPILER})

# library generation
# ============================
set(LIBLOG_COMMUN_SOURCES
  log_const.h
  log_event.h
  formater/log_event.cpp
  formater/LogFifo.cpp
  node/Node.h
  node/NodeVisitorI.h
  node/Node.cpp
  log_level.cpp
  log_level.h
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
  LogConf.cpp
  LogConf.h
  log.h
  log_internal/log_utils.cpp
  parse/parseConfigurationString.cpp
  )

if(ENABLE_FILE_SYSTEM)
  set(LIBLOG_CONF
    LogConfFile.h
    LogConfFile.cpp)
else()
  set(LIBLOG_CONF
    LogConfMem.h
    LogConfMem.cpp)
endif()

add_library(log STATIC ${LIBLOG_COMMUN_SOURCES} ${LIBLOG_CONF})


# include dir
# ============================
include_directories(.)
include_directories(node)
include_directories(logNode)
include_directories(parse)
include_directories(log_internal)
include_directories(formater)

# sub dir
# ============================
if(_X86_ OR _UNIT_TEST_)
  # use cmake test framework
  enable_testing()
  # add test subdir
  add_subdirectory(test)
endif()

# install target with static lib and header
# install(FILES
# ${CMAKE_CURRENT_SOURCE_DIR}/log_const.h
# ${CMAKE_CURRENT_SOURCE_DIR}/log_event.h
# ${CMAKE_CURRENT_SOURCE_DIR}/LogFacade.h
# ${CMAKE_CURRENT_SOURCE_DIR}/LogFifo.h
# ${CMAKE_CURRENT_SOURCE_DIR}/LogFifoI.h
# ${CMAKE_CURRENT_SOURCE_DIR}/LogFile.h
# ${CMAKE_CURRENT_SOURCE_DIR}/log_formater.h
# ${CMAKE_CURRENT_SOURCE_DIR}/log.h
# ${CMAKE_CURRENT_SOURCE_DIR}/log_level.h
# ${CMAKE_CURRENT_SOURCE_DIR}/log_macro.h
# ${CMAKE_CURRENT_SOURCE_DIR}/LogMutexI.h
# ${CMAKE_CURRENT_SOURCE_DIR}/log_utils.h
# ${CMAKE_CURRENT_SOURCE_DIR}/logNode/LogNode.h
#   DESTINATION liblog/include)

# install(TARGETS log
#   ARCHIVE DESTINATION liblog/lib/static)
