cmake_minimum_required(VERSION 3.0)

# define project template
# ============================
project(liblog)

# set compiler & flags IF NEEDED
# (else keep setup from parent project or environement)
# ======================================================
if(STANDALONE_MODE)
  if(CROSS_COMPILE_M3)
    include(CMakeLists_CrossCompiler.cmake)
  endif()
  include(CMakeLists_CompilerFlags.cmake)
endif()

# Library option
# ============================
if(CROSS_COMPILE_M3)
  message("Set liblog option for M3: disable file system and stdio")
elseif(CROSS_COMPILE_A7)
  # A7 linux
  message("Set liblog option for A7: enable file system and stdio")
  set(ENABLE_FILE_SYSTEM 1)
  set(ENABLE_STDIO 1)
else()
  # X86 (unit test)
  message("Set liblog option for x86: enable file system and stdio")
  set(ENABLE_FILE_SYSTEM 1)
  set(ENABLE_STDIO 1)
endif()

# force c++
SET(CMAKE_C_COMPILER ${CMAKE_CXX_COMPILER})

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
  log.h
  log_internal/log_utils.cpp
  parse/parseConfigurationString.cpp
  )

if(ENABLE_FILE_SYSTEM)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D ENABLE_FILE_SYSTEM")
  set(LIBLOG_FILE_SYSTEM
    LogFile.h
    LogFile.cpp
    )
endif()

add_library(log STATIC ${LIBLOG_COMMUN_SOURCES} ${LIBLOG_FILE_SYSTEM})

# Compilation option
# ============================


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
if(_X86_)
  # use cmake test framework
  enable_testing()
  # add test subdir
  add_subdirectory(test)
endif()
