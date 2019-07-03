# main target
help: help-display

build-x86:
	mkdir -p build_x86; cd build_x86; cmake -D_X86_=ON ..; make all test

config-m3:
	mkdir -p build_arm_m3; cd build_arm_m3; cmake -DCROSS_COMPILE_M3=ON ..;

build-m3: config-m3
	cd build_arm_m3; make

build-a7:
	mkdir -p build_arm_a7; cd build_arm_a7; cmake -DCROSS_COMPILE_A7=ON ..; make

clean:
	find . -iname "*cmake*" -not -name CMakeLists.txt -exec rm -rf {} \+
	rm Makefile

help-display:
	@echo
	@echo "Main targets:"
	@echo	"  make build-x86 : build for host "
	@echo "  make build-m3  : crosscompilation for Free-RTOS M3 "
	@echo	"  make build-a7  : crosscompilation for Linux A7 "
	@echo
