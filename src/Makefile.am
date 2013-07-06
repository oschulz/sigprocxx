CLEANFILES = *.d *.so *-rdict.cxx *-rdict.h
MAINTAINERCLEANFILES = Makefile.in

# EXTRA_DIST = some extra files, e.g. test-data

lib_LTLIBRARIES = libsigprocxx.la

libsigprocxx_la_SOURCES = \
	comprehensions.cxx \
	filters.cxx \
	util.cxx \
	windowfcts.cxx \
	Dither.cxx \
	Filter.cxx \
	VectorOps.cxx \
	VectorView.cxx \
	VLEncoding.cxx \
	ZigZagEnc.cxx

libsigprocxx_la_headers = \
	comprehensions.h \
	filters.h \
	util.h \
	windowfcts.h \
	Dither.h \
	Filter.h \
	VectorOps.h \
	VectorView.h \
	VLEncoding.h \
	ZigZagEnc.h

pkginclude_HEADERS = $(libsigprocxx_la_headers)

# bin_PROGRAMS = 

# noinst_PROGRAMS =


libsigprocxx_la_linkdefs =

if WITH_BLITZWAVE
libsigprocxx_la_SOURCES += WlDecomp.cxx
libsigprocxx_la_headers += WlDecomp.h
libsigprocxx_la_linkdefs += sigprocxx-LDefs-wavelet.h
endif # WITH_BLITZWAVE

libsigprocxx_la_linkdefs += sigprocxx-LinkDef.h


libsigprocxx_la_SOURCES += libsigprocxx-rdict.cxx

libsigprocxx-rdict.cxx: $(libsigprocxx_la_headers) $(libsigprocxx_la_linkdefs)
	$(ROOTCINT) -f $@ -c -p $(CPPFLAGS) $(CXXFLAGS) $+

rootmapdir = $(libdir)
rootmap_DATA = .libs/libsigprocxx.rootmap

.libs/libsigprocxx.rootmap: libsigprocxx.la | $(libsigprocxx_la_headers) $(libsigprocxx_la_linkdefs)
	$(RLIBMAP) -o $@ -l .libs/libsigprocxx@SHLIBEXT@ -c $|
