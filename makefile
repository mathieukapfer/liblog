# dir
BUILD_M3_DIR=build_arm_m3
BUILD_A7_DIR=build_arm_a7
BUILD_X86_DIR=build_x86

# main target
help: help-display

# config
config-m3:
	mkdir -p build_arm_m3; cd build_arm_m3; /usr/bin/cmake -DCMAKE_TOOLCHAIN_FILE:PATH="../CMakeLists_CrossCompiler.cmake" -DSTANDALONE_MODE=ON  -DCROSS_COMPILE_M3=ON  VERBOSE=1 ..

# build target
build-x86:
	mkdir -p ${BUILD_X86_DIR}; cd ${BUILD_X86_DIR}; /usr/bin/cmake -D_X86_=ON ..; make all test

build-m3: config-m3
	cd build_arm_m3; make VERBOSE=1

build-a7:
	mkdir -p build_arm_a7; cd build_arm_a7; /usr/bin/cmake -DSTANDALONE_MODE=ON -DCROSS_COMPILE_A7=ON ..; make

# install target
install-local:
	cd ${BUILD_X86_DIR}; DESTDIR="install" make install

install:
	cd ${BUILD_X86_DIR};  make install

# clean target
clean:
	-rm -rf ${BUILD_X86_DIR} build_arm_m3 build_arm_a7
	-find . -iname "*cmake*" -not -name "CMakeLists*" -exec rm -rf {} \+
	-rm Makefile

# tag for emacs
index:
	-rm TAGS; find . -name "*.*[hcp]" | xargs etags -a -l c++

# test
.PHONY:test
test:
	cd ${BUILD_X86_DIR}; make
	cd ${BUILD_X86_DIR}; make test_log
	cd test; ../${BUILD_X86_DIR}/test/test_log

help-display:
	@echo
	@echo "Main targets:"
	@echo	"  make build-x86 : build for host "
	@echo "  make build-m3  : crosscompilation for Free-RTOS M3 "
	@echo	"  make build-a7  : crosscompilation for Linux A7  - [TODO !!!!] "
	@echo "  make install-local   : install lib and header in build dir"
	@echo "  make install         : install lib and header in machine dir"
