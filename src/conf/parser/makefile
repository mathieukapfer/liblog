CC=g++

CFLAGS= -I../../../Tools/doctest -I.. -I../node -I../logNode -I../internal -I../formater


test: testParsing
	./testParsing

testParsing: parseConfigurationString.cpp ../internal/log_utils.cpp ../log_level.cpp
