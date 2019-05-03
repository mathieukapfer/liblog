#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(test_log
	log_test.c
	MyClass.cpp
	MyClass2.cpp
	subdir/MyClass3.cpp
)

add_test(
  NAME run_test_log
  COMMAND "${CMAKE_CURRENT_BINARY_DIR}/test_log"
)

# include dir
include_directories(subdir)

set_target_properties(test_log PROPERTIES COMPILE_FLAGS "-std=c++11" ) # "${CMAKE_CXX_FLAGS})
#set_target_properties(test_log PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS})

target_link_libraries(test_log log)
