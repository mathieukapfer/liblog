# main target
help: help-display

build-x86:
	mkdir -p build_x86; cd build_x86; /usr/bin/cmake -D_X86_=ON ..; make all test

config-m3:
	mkdir -p build_arm_m3; cd build_arm_m3; /usr/bin/cmake -DSTANDALONE_MODE=ON -DCROSS_COMPILE_M3=ON ..;

build-m3: config-m3
	cd build_arm_m3; make VERBOSE=1

build-a7:
	mkdir -p build_arm_a7; cd build_arm_a7; /usr/bin/cmake -DSTANDALONE_MODE=ON -DCROSS_COMPILE_A7=ON ..; make

clean:
	-rm -rf build_x86 build_arm_m3 build_arm_a7
	-find . -iname "*cmake*" -not -name CMakeLists.txt -exec rm -rf {} \+
	-rm Makefile

index:
	-rm TAGS; find . -name "*.*[hcp]" | xargs etags -a -l c++

.PHONY:test
test:
	cd build_x86; make
	cd build_x86; make test_log
	cd test; ../build_x86/test/test_log

help-display:
	@echo
	@echo "Main targets:"
	@echo	"  make build-x86 : build for host "
	@echo "  make build-m3  : crosscompilation for Free-RTOS M3 "
	@echo	"  make build-a7  : crosscompilation for Linux A7 "
	@echo
