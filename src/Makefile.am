CLEANFILES = *.d *.so *-rdict.cxx *-rdict.h
MAINTAINERCLEANFILES = Makefile.in

# EXTRA_DIST = some extra files, e.g. test-data

lib_LTLIBRARIES = libsigprocxx.la

libsigprocxx_la_SOURCES = \
	util.cxx \
	filters.cxx \
	windowfcts.cxx \
	Dither.cxx \
	Filter.cxx \
	VectorOps.cxx \
	VLEncoding.cxx \
	ZigZagEnc.cxx

libsigprocxx_la_headers = \
	util.h \
	filters.h \
	windowfcts.h \
	Dither.h \
	Filter.h \
	VectorOps.h \
	VLEncoding.h \
	ZigZagEnc.h

pkginclude_HEADERS = $(libsigprocxx_la_headers)

# bin_PROGRAMS = 

# noinst_PROGRAMS =


libsigprocxx_la_SOURCES += libsigprocxx-rdict.cxx

libsigprocxx-rdict.cxx: $(libsigprocxx_la_headers) sigprocxx-LinkDef.h
	$(ROOTCINT) -f $@ -c -p $(CPPFLAGS) $(CXXFLAGS) $+

rootmapdir = $(libdir)
rootmap_DATA = .libs/libsigprocxx.rootmap

.libs/libsigprocxx.rootmap: libsigprocxx.la | $(libsigprocxx_la_headers) sigprocxx-LinkDef.h
	$(RLIBMAP) -o $@ -l .libs/libsigprocxx@SHLIBEXT@ -c $|
