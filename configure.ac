# Initialization

AC_INIT([SigProCxx], [0.3.0], [], [sigprocxx])

AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall -Werror])


# Libtool init and language selection

# Workaround for newer vs. older versions of Automake:
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])

AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL
AC_PROG_CXX

CXX_PROJECT_INIT


# Optional features

REQ_LIBS=""

AH_TEMPLATE([WITH_BLITZWAVE], [BLITZWAVE support available and enabled])
AC_ARG_WITH(
	[blitzwave], [AS_HELP_STRING([--with-blitzwave],
	[enable BLITZWAVE support @<:@default=no@:>@])], [],
	[with_blitzwave=no]
)
AS_IF([test "x$with_blitzwave" != xno],
	[REQ_LIBS="${REQ_LIBS} blitzwave blitz"]
	[AC_DEFINE([WITH_BLITZWAVE])]
)
AM_CONDITIONAL([WITH_BLITZWAVE], [test "x$with_blitzwave" != xno])


# Checks for dependencies

ROOTSYS_DEPS([glibs], [])

CXX_PROJECT_DEPS([$REQ_LIBS])


# Output

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([
	Makefile
	sigprocxx.pc
	sigprocxx-config
	src/Makefile
	doc/Makefile doc/Doxyfile
])

AC_OUTPUT
