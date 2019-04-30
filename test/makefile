CFLAGS = -I.. -I../node -g

test:
	-rm log_test;
	make log_test && ./log_test

log_test: \
	../LogNode.cpp ../LogNode.h \
	log_test.c MyClass.cpp MyClass2.cpp \
	../node/Node.cpp \
	../LogNodeFactory.cpp \
	../LogNodeVisitor_ConfigureLevel.cpp \
	../log_event.cpp \
	../log_level.cpp \
	../LogFile.cpp


# ../LogNodeVisitor_ShowTree.h

CC=g++
