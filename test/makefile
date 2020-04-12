test:
	cd ..; make test

test-manual:
	cd ../build_x86; make && cd test && make test_manual && ./test_manual

test-simple: 
	cp log.cfg ../build_x86/test
	cd ../build_x86; make && cd test && make test_simple && ./test_simple

test-formater:
	make test_formater && ./test_formater
