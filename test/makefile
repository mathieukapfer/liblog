# run ctest
test:
	cp log.cfg ../build_x86/test
	cd ../build_x86 && make test

# run example (see README.md)
test-example:
	-cd ../build_x86/test && rm log.cfg
	cd ../build_x86;  make && cd test && make example && ./example

# execute test out of ctest
test-simple:
	cp log.cfg ../build_x86/test
	cd ../build_x86; make && cd test && make test_simple && ./test_simple

# see formater result
test-formater:
	CXXFLAGS=-I.. make  test_formater && ./test_formater
