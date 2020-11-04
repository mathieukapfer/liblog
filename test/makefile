test:
	cd ..; make test

test-sample:
	-cd ../build_x86/test && rm log.cfg
	cd ../build_x86;  make && cd test && make sample && ./sample

test-manual:
	cd ../build_x86; make && cd test && make test_manual && ./test_manual

test-simple:
	cp log.cfg ../build_x86/test
	cd ../build_x86; make && cd test && make test_simple && ./test_simple

test-formater:
	CXXFLAGS=-I.. make  test_formater && ./test_formater
