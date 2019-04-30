add_executable(test_log
	log_test.c
	MyClass.cpp
	MyClass2.cpp
)

add_test(
  NAME run_test_log
  COMMAND "${CMAKE_CURRENT_BINARY_DIR}/test_log"
)

target_link_libraries(test_log log)