if(_X86_)
add_executable(test_parser
  testParsing.cpp
  LogSpecParser.cpp
  ../../logForLogger/log_utils.cpp
  ../../../log_level.cpp
  )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../test/doctest)

add_test(
  NAME run_test_parser
  COMMAND "${CMAKE_CURRENT_BINARY_DIR}/test_parser"
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  )
endif()
