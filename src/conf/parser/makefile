CC=g++

CFLAGS= -g -I../../logForLogger  -I../../.. -I../../../test/doctest/

test: testParsing
	./testParsing

testParsing: parseConfString.cpp  ../../logForLogger/log_utils.cpp ../../../log_level.cpp

clean:
	rm testParsing
