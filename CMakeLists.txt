cmake_minimum_required(VERSION 3.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# compilation flags
# ============================

# add debug if needed
if (DEBUG)
  message("enable debug flag")
  set(COMMON_FLAGS "${COMMON_FLAGS} -g -ggdb")
endif()

# apply compilation option
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   ${COMMON_C_FLAGS} ${COMMON_FLAGS} ${CROSS_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_CPP_FLAGS} ${COMMON_FLAGS} ${CROSS_FLAGS}")


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
./src/conf/parser/LogSpecParser.cpp
./src/conf/LogConf.cpp
./src/logForLogger/log_utils.cpp
./src/node/ConfigureLevel.cpp
./src/node/LogNode.cpp
./src/node/Node.cpp
./src/node/LogNodeFactory.cpp
./src/formater/log_event.cpp
./src/formater/log_timestamp.cpp
./src/LogFacade.cpp
./src/log_facade.cpp
./log_level.cpp
)

if(ENABLE_FILE_SYSTEM)
  set(LIBLOG_CONF
    src/conf/LogConfFile.cpp)
else()
  set(LIBLOG_CONF
    src/conf/LogConfMem.cpp)
endif()

if(ENABLE_SYS_LOG)
  set(LIBLOG_SYSLOG
    src/formater/log_event_syslog.cpp)
endif()


add_library(log STATIC ${LIBLOG_COMMUN_SOURCES} ${LIBLOG_CONF} ${LIBLOG_SYSLOG})

# hum .. not working => use liblogConfig.cmake instead
#target_include_directories(log PUBLIC src src/fifo )

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
  add_subdirectory(src/conf/parser)
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
