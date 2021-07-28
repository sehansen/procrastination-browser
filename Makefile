
default: all

all:
	mkdir -p build
	qmake pb.pro -r -spec linux-g++-64 CONFIG+=debug -o build/Makefile
	make -C build
