PROVIDED_INCLUDEDIR=`pwd`/../provided/include
PROVIDED_DEBUGLIBDIR=`pwd`/../provided/lib/debug/`arch`/
PROVIDED_RELEASELIBDIR=`pwd`/../provided/lib/release/`arch`/

all: debug release

debug:
	mkdir -p debug-build
	cd debug-build && cmake ../src -DCMAKE_BUILD_TYPE=Debug "-DPROVIDED_INCLUDEDIR:STRING=${PROVIDED_INCLUDEDIR}" "-DPROVIDED_LIBDIR:STRING=${PROVIDED_DEBUGLIBDIR}"
	cd debug-build && cmake ../src -DCMAKE_BUILD_TYPE=Debug "-DPROVIDED_INCLUDEDIR:STRING=${PROVIDED_INCLUDEDIR}" "-DPROVIDED_LIBDIR:STRING=${PROVIDED_DEBUGLIBDIR}" -G "Eclipse CDT4 - Unix Makefiles"
	cd debug-build && cmake ../src -DCMAKE_BUILD_TYPE=Debug "-DPROVIDED_INCLUDEDIR:STRING=${PROVIDED_INCLUDEDIR}" "-DPROVIDED_LIBDIR:STRING=${PROVIDED_DEBUGLIBDIR}" -G "CodeBlocks - Unix Makefiles"
	cd debug-build && make

release:
	mkdir -p release-build
	cd release-build && cmake ../src -DCMAKE_BUILD_TYPE=Release "-DPROVIDED_INCLUDEDIR:STRING=${PROVIDED_INCLUDEDIR}" "-DPROVIDED_LIBDIR:STRING=${PROVIDED_RELEASELIBDIR}"
	cd release-build && cmake ../src -DCMAKE_BUILD_TYPE=Release "-DPROVIDED_INCLUDEDIR:STRING=${PROVIDED_INCLUDEDIR}" "-DPROVIDED_LIBDIR:STRING=${PROVIDED_RELEASELIBDIR}" -G "Eclipse CDT4 - Unix Makefiles"
	cd release-build && cmake ../src -DCMAKE_BUILD_TYPE=Release "-DPROVIDED_INCLUDEDIR:STRING=${PROVIDED_INCLUDEDIR}" "-DPROVIDED_LIBDIR:STRING=${PROVIDED_RELEASELIBDIR}" -G "CodeBlocks - Unix Makefiles"
	cd release-build && make



