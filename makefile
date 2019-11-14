# dir
BUILD_X86_DIR=build_x86

# main target
help: help-display

# build target
build-x86:
	mkdir -p ${BUILD_X86_DIR}; cd ${BUILD_X86_DIR}; cmake -D_X86_=ON ..; make all test

# clean target
clean:
	-rm -rf ${BUILD_X86_DIR}
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
	@echo "  make build-x86       : build for host and do test with cmake"
	@echo "  make test            : do test (out of cmake)"
