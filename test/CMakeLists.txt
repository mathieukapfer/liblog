
add_executable(test_log
	log_test.cpp
	MyClass.cpp
	MyClass2.cpp
	subdir/MyClass3.cpp
)


target_link_libraries(test_log log)

if(_X86_)
add_executable(sample
  sample.cpp
  )

target_link_libraries(sample log)

add_executable(test_simple
  test_simple.cpp
  )

target_link_libraries(test_simple log)

add_executable(test_manual
  test_manual.cpp
  MyClass.cpp
  MyClass2.cpp
  subdir/MyClass3.cpp
  )
target_link_libraries(test_manual log)

endif()

add_test(
  NAME run_test_log
  COMMAND "${CMAKE_CURRENT_BINARY_DIR}/test_simple"
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

# include dir
include_directories(subdir)
include_directories(doctest)

# force c++11
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set_target_properties(test_log PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu11 -std=c++11 -g" )
#set_target_properties(test_log PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS})
