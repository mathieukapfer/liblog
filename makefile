# dir
BUILD_X86_DIR=build_x86
BUILD_X86_CONF_M3_DIR=build_x86_conf_m3
BUILD_X86_CONF_A7_DIR=build_x86_conf_a7

# main target
help: help-display

all:build-x86 build-x86-conf-m3 build-x86-conf-a7

# build target
build-x86:
	mkdir -p ${BUILD_X86_DIR}; cd ${BUILD_X86_DIR}; cmake -D_X86_=ON ..; make all test

# build target with M3 configuration for unit test
build-x86-conf-m3:
	mkdir -p ${BUILD_X86_CONF_M3_DIR}; cd ${BUILD_X86_CONF_M3_DIR}; cmake -DCROSS_COMPILE_M3=ON -D_DO_UNIT_TEST_=ON ..; make all test

build-x86-conf-a7:
	mkdir -p ${BUILD_X86_CONF_A7_DIR}; cd ${BUILD_X86_CONF_A7_DIR}; cmake -DCROSS_COMPILE_A7=ON -D_DO_UNIT_TEST_=ON ..; make all test

# clean target
clean:
	-rm -rf ${BUILD_X86_DIR} ${BUILD_X86_CONF_M3_DIR}

#-find . -iname "*cmake*" -not -name "CMakeLists*" -exec rm -rf {} \+
#	-rm Makefile

# tag for emacs
index:
	-rm TAGS; find . -name "*.*[hcp]" | xargs etags -a -l c++

# test
.PHONY:test

test: test-x86 test-m3 test-a7

test-x86:
	@echo "\n\n#### Check conf from file\n\n"
	cd ${BUILD_X86_DIR}; make
	cd ${BUILD_X86_DIR}; make test_log
	cd test; ../${BUILD_X86_DIR}/test/test_log

test-m3:
	@echo "\n\n#### Check M3 conf (from memory)\n\n"
	cd ${BUILD_X86_CONF_M3_DIR}; make
	cd ${BUILD_X86_CONF_M3_DIR}; make test_log
	cd test; ../${BUILD_X86_CONF_M3_DIR}/test/test_log

test-a7:
	@echo "\n\n#### Check A7 conf (cp to memory)\n\n"
	cd ${BUILD_X86_CONF_A7_DIR}; make
	cd ${BUILD_X86_CONF_A7_DIR}; make test_log
	cd test; ../${BUILD_X86_CONF_A7_DIR}/test/test_log

help-display:
	@echo
	@echo "Main targets:"
	@echo "  make build-all           : build & test for host for all configs below:"
	@echo "  make build-x86           : build & test for host with x86 config"
	@echo "  make build-x86-conf-m3   : build & test for host with m3 config"
	@echo "  make build-x86-conf-a7   : build & test for host with a7 config"
	@echo "  make test                : do test (out of cmake to see the output)"


index:
	-rm TAGS;
	find . -name "*.*[hcp]" | xargs etags -a -lc
