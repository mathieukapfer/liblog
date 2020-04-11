CC=g++

CFLAGS=  -I../../logForLogger  -I../../.. -I../../../test/doctest/

test: testParsing
	./testParsing

testParsing: parseConfigurationString.cpp  ../../logForLogger/log_utils.cpp ../../../log_level.cpp
