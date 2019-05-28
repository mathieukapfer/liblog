
all: test_no_log test_log

test_no_log:
	rm test_log_local
	make test_log_local
	@echo "\ntest without log:\n"
	./test_log_local
	@echo "<end if test>\n\n"

test_log:
	rm test_log_local
	CXXFLAGS=-DLOG_ENABLE make test_log_local
	@echo "\ntest with log:\n"
	./test_log_local
