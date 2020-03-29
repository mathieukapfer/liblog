cmake_minimum_required(VERSION 3.0)

# debug
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")


# define project template
# ============================
# project(liblog)

include(CMakeLists_LogConfig.txt)

# force c++
# SET(CMAKE_C_COMPILER ${CMAKE_CXX_COMPILER})

# library generation
# ============================
set(LIBLOG_COMMUN_SOURCES
./src/fifo/LogFifo.cpp
./src/fifo/test_fifo.cpp
./src/conf/parser/parseConfigurationString.cpp
./src/conf/LogConf.cpp
./src/logForLogger/log_utils.cpp
./src/node/ConfigureLevel.cpp
./src/node/LogNodeVisitor_ConfigureLevel.cpp
./src/node/LogNode.cpp
./src/node/Node.cpp
./src/node/LogNodeFactory.cpp
./src/formater/log_event.cpp
./src/LogFacade.cpp
./log_level.cpp
)

if(ENABLE_FILE_SYSTEM)
  set(LIBLOG_CONF
    src/conf/LogConfFile.cpp)
else()
  set(LIBLOG_CONF
    src/conf/LogConfMem.cpp)
endif()

add_library(log STATIC ${LIBLOG_COMMUN_SOURCES} ${LIBLOG_CONF})


# include dir
# ============================

include_directories(.)
include_directories(src)
include_directories(src/conf)
include_directories(src/conf/parser)
include_directories(src/logForLogger)
include_directories(src/fifo)
include_directories(src/node)
include_directories(src/formater)
include_directories(parse)

# sub dir
# ============================
if(_X86_ OR _DO_UNIT_TEST_)
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
