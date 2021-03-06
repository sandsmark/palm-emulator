dnl ======================================================================================
dnl	Copyright (c) 1998-2001 Palm, Inc. or its subsidiaries.
dnl	All rights reserved.
dnl ======================================================================================

dnl ========================================================
dnl Process this file with autoconf to produce a configure script.
dnl ========================================================

AC_INIT(pose, 0, no)
AC_CANONICAL_SYSTEM
AC_CONFIG_SRCDIR([../SrcUnix/Platform_Unix.cpp])
AM_INIT_AUTOMAKE

AC_PROG_MAKE_SET
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB


dnl ========================================================
dnl Check for programs.
dnl ========================================================

AC_PROG_CPP


dnl ========================================================
dnl Check for libraries.
dnl ========================================================

AC_PATH_XTRA

AC_ARG_WITH(fltk,
	[  --with-fltk=DIR         use FLTK in DIR], [
	CPPFLAGS="${CPPFLAGS} -I$withval/include"
	LDFLAGS="${LDFLAGS} -L$withval/lib"
	test "${FLUID+set}" != set && test -r "$withval/bin/fluid" && FLUID="$withval/bin/fluid"])


dnl ========================================================
dnl Check for header files.
dnl ========================================================

AC_HEADER_DIRENT
AC_HEADER_STDC
AC_CHECK_HEADERS(endian.h machine/endian.h sys/isa_defs.h fcntl.h limits.h strings.h sys/time.h unistd.h)


dnl ========================================================
dnl Check for typedefs, structures, and compiler characteristics.
dnl ========================================================

AC_C_CONST
AC_C_INLINE


dnl ----------------------------
dnl Check sa_len of sockaddr
dnl ----------------------------

AC_DEFUN([AC_STRUCT_SA_LEN],
	[AC_CACHE_CHECK([for 'sa_len' in 'struct sockaddr'], ac_cv_struct_sa_len,
	[AC_TRY_COMPILE([
		#include <sys/types.h>
		#include <sys/socket.h>
	], [
		struct sockaddr sa;
		sa.sa_len = 0;
	], ac_cv_struct_sa_len=yes, ac_cv_struct_sa_len=no)])
	if test "$ac_cv_struct_sa_len" = yes; then
		AC_DEFINE(HAVE_SA_LEN)
	fi])

AC_DEFUN([AC_STRUCT_SIN_LEN],
	[AC_CACHE_CHECK([for 'sin_len' in 'struct sockaddr_in'], ac_cv_struct_sin_len,
	[AC_TRY_COMPILE([
		#include <sys/types.h>
		#include <sys/socket.h>
		#include <netinet/in.h>
	], [
		struct sockaddr_in sin;
		sin.sin_len = 0;
	], ac_cv_struct_sin_len=yes, ac_cv_struct_sin_len=no)])
	if test "$ac_cv_struct_sin_len" = yes; then
		AC_DEFINE(HAVE_SIN_LEN)
	fi])

AC_DEFUN([AC_TYPE_SOCKLEN_T],
	[AC_CACHE_CHECK([for 'socklen_t'], ac_cv_type_socklen_t,
	[AC_TRY_COMPILE([
		#include <sys/types.h>
		#include <sys/socket.h>
	], [
		socklen_t var;
		var = 0;
	], ac_cv_type_socklen_t=yes, ac_cv_type_socklen_t=no)])
	if test "$ac_cv_type_socklen_t" = yes; then
		AC_DEFINE(HAVE_TYPE_SOCKLEN_T)
	fi])

AC_STRUCT_SA_LEN
AC_STRUCT_SIN_LEN
AC_TYPE_SOCKLEN_T


dnl ========================================================
dnl Check for library functions.
dnl ========================================================

AC_FUNC_ALLOCA
AC_CHECK_FUNCS(mkdir)
AC_CHECK_FUNCS(mkstemp)
AC_CHECK_FUNCS(tempnam)


dnl ========================================================
dnl Set the defaults first
dnl ========================================================

AR='ar'
FLAGS_COMMON="-DPLATFORM_UNIX=1 -D__PALMOS_TRAPS__=0 -DEMULATION_LEVEL=EMULATION_UNIX -m32"

dnl force 32bit for now

LDFLAGS="${LDFLAGS} -m32"

dnl ========================================================
dnl Define some standard warning flags 
dnl ========================================================

_WARNINGS_CFLAGS="${_WARNINGS_CFLAGS} -fexceptions -Wall -Wno-multichar -Wno-unknown-pragmas -Wno-conversion -Wno-missing-braces"
_WARNINGS_CXXFLAGS="${_WARNINGS_CXXFLAGS} -fexceptions -Wall -Wno-multichar -Wno-unknown-pragmas -Wno-conversion"

_COMPILER_CFLAGS="${_COMPILER_CFLAGS}"
_COMPILER_CXXFLAGS="${_COMPILER_CXXFLAGS}"


dnl ========================================================
dnl Define the standard OMNITHREAD options
dnl ========================================================

THREAD_FLAGS="-D_REENTRANT -DNoNanoSleep -DPthreadDraftVersion=10"
THREAD_LIBS="-lpthread"


dnl ========================================================
dnl System overrides of the defaults
dnl ========================================================

case "$target" in
*-aix*)
	THREAD_FLAGS="-DNoNanoSleep -DPthreadDraftVersion=8"
	THREAD_LIBS="-lpthread"
	;;

*-hpux*)
	THREAD_FLAGS="-D_REENTRANT -DPthreadDraftVersion=4"
	THREAD_LIBS="-lpthread -lmach -lc_r"
	;;

*-irix*)
	THREAD_FLAGS="-DUsePthread -D_REENTRANT -DPthreadDraftVersion=10 -DPthreadSupportThreadPriority"
	THREAD_LIBS="-lpthread"
	;;

*-linux*) 
	THREAD_FLAGS="-D_REENTRANT -DNoNanoSleep -DPthreadDraftVersion=10"
	THREAD_LIBS="-lpthread"
	;;

*-nto*) 
	THREAD_FLAGS="-D_REENTRANT -DPthreadDraftVersion=10"
	THREAD_LIBS=""
	POSER_CFLAGS="$POSER_CFLAGS  -D_QNX_SOURCE -D_POSIX_SOURCE -D__i386__ -D_i386 -DNSCAP_NO_EXPLICIT -DNO_REGEX -DSTRINGS_ALIGNED -D_SEEKPOS_DEFINED_ -I/usr/gcc/lib/gcc-lib/ntox86/2.8.1/include"
	POSER_CXXFLAGS="$POSER_CFLAGS"
	_WARNINGS_CFLAGS='-w'
	_WARNINGS_CXXFLAGS='-w'
	LIBS="$LIBS -lsocket"
	poser_optimize="-O2"
	poser_debug="-gdwarf-2"
	AR='/usr/local/bin/ar.elf'
	;;

*-osf*)
dnl I am not sure how to test for these versions...
dnl Options for OSF 1.3.2
dnl	THREAD_FLAGS="-D_REENTRANT -DNoNanoSleep -DPthreadDraftVersion=4"
dnl	THREAD_LIBS="-lpthread -lmach -lc_r"
dnl Options for OSF 1.4
	THREAD_FLAGS="-D_REENTRANT -pthread -DNoNanoSleep -DPthreadDraftVersion=10"
	THREAD_LIBS="-lcma"
	;;

*-freebsd*)
	THREAD_FLAGS="-pthread -D_THREAD_SAFE -D_REENTRANT -DPthreadDraftVersion=10"
	THREAD_LIBS=
	;;

*-bsdi4*)
	THREAD_LIBS=
	;;
esac


dnl ========================================================
dnl Check for gprof profiling
dnl ========================================================

AC_ARG_ENABLE(profile,
	[  --enable-profile        include gprof profiling (default no)],
	FLAGS_PROFILE="-pg",
	FLAGS_PROFILE="")


dnl ========================================================
dnl Check for built-in profiling
dnl ========================================================

AC_ARG_ENABLE(palm_profile,
	[  --enable-palm-profile   include profiling of Palm applications (default no)],
	FLAGS_PALM_PROFILE="-DHAS_PROFILING=1",
	FLAGS_PALM_PROFILE="-DHAS_PROFILING=0")


dnl ========================================================
dnl Check for static link.
dnl ========================================================

AC_ARG_ENABLE(static-link,
	[  --enable-static-link    static link; no shared libraries (default no)],
	LDFLAGS="${LDFLAGS} -static"
)


dnl ========================================================
dnl Check for Optimize
dnl
dnl NOTE: turning on optimizations when using egcs 1.1.2
dnl runs afoul of a code generation bug on x86's (as
dnl shipped with RedHat 6.0).  The specific cases I know
dnl about (in SkinScaleDown and SkinScaleUp) are coded
dnl around, but there may be more lurking...
dnl
dnl I haven't checked this, but I hear the bug is fixed
dnl in gcc 2.95.
dnl ========================================================

dnl This is now on by default.  It gets turned off if the
dnl user selects --enable-debug.
dnl
dnl AC_ARG_ENABLE(optimize,
dnl	[  --enable-optimize       optimize code (default no)],
dnl	FLAGS_OPTIMIZE="-O2",
dnl	FLAGS_OPTIMIZE="")

FLAGS_OPTIMIZE="-O2"


dnl ========================================================
dnl Check whether default arguments which call a virtual
dnl function in another object work -- GCC 2.95.x crashes
dnl trying to compile something like this.
dnl ========================================================

AC_LANG_CPLUSPLUS
AC_CACHE_CHECK([whether virtual function default arguments work],
	pose_cv_virtual_defarg_ok,
	AC_TRY_COMPILE([
		class C
		{ 
			public:
				virtual int foo ();
		} *c;
		void bar (int = c->foo ());
		], [bar ();],
		pose_cv_virtual_defarg_ok=yes, pose_cv_virtual_defarg_ok=no))

if test $pose_cv_virtual_defarg_ok = no; then
	AC_DEFINE(BROKEN_VIRTUAL_DEFAULT_ARGUMENTS)
fi


dnl ========================================================
dnl Check for debugging
dnl ========================================================

AC_ARG_ENABLE(debug,
	[  --enable-debug          include debugging symbols (default no)],
	FLAGS_DEBUG="-D_DEBUG -g"
	FLAGS_PROFILE="-DHAS_PROFILING=1"
	FLAGS_PALM_PROFILE=""
	FLAGS_OPTIMIZE="",
	FLAGS_DEBUG="-DNDEBUG")


dnl ========================================================
dnl Check for OpenGL.  This is pretty much the same code
dnl that FLTK uses to check for it.  We'll assume that if
dnl OpenGL is present, FLTK was configured to use it, and
dnl so we need to link with it.
dnl ========================================================

dnl ========================================================
dnl Make sure FLTK is available.  It must be installed on
dnl a standard path, or on $x_libraries, or via --with-fltk.
dnl Also check that fluid is available (via PATH or --with-fltk).
dnl ========================================================

AC_CACHE_SAVE

dnl Temporarily add -lfltk and OTHER-LIBRARIES (cf AC_CHECK_LIB) to $LIBS
save_LIBS="$LIBS"
LIBS="-lfltk -lGL -L${ac_x_libraries} -lXext -lX11 -lm $X_EXTRA_LIBS $LIBS"

AC_LANG_CPLUSPLUS

AC_DEFUN([MSG_ERROR_FLTK_MISSING],
[AC_MSG_ERROR([*** FLTK *must* be installed before running configure. ***])])

dnl CHECK_FLTK_FUNC(HEADER, FUNCTION, ARGUMENT_LIST)
AC_DEFUN([CHECK_FLTK_FUNC],
[AC_MSG_CHECKING([for fl_$2 in -lfltk])
AC_TRY_LINK([#include <$1>], [fl_$2 ($3);],
	[result=yes],
	[AC_TRY_LINK([#include <$1>], [$2 ($3);],
		[result=$2
		AC_DEFINE([fl_$2], [$2])],
		[result=no])])
AC_MSG_RESULT($result)
if test $result = no; then
	MSG_ERROR_FLTK_MISSING
fi])

CHECK_FLTK_FUNC([FL/Enumerations.H], [contrast], [FL_BLACK, FL_BLACK])
CHECK_FLTK_FUNC([FL/Enumerations.H], [inactive], [FL_BLACK])
CHECK_FLTK_FUNC([FL/filename.H], [filename_absolute], ["", ""])
CHECK_FLTK_FUNC([FL/filename.H], [filename_ext], [""])
CHECK_FLTK_FUNC([FL/filename.H], [filename_isdir], [""])
CHECK_FLTK_FUNC([FL/filename.H], [filename_list], ["", 0])
CHECK_FLTK_FUNC([FL/filename.H], [filename_match], ["", ""])
CHECK_FLTK_FUNC([FL/filename.H], [filename_setext], ["", ""])

LIBS="$save_LIBS"

dnl $FLUID may have already been set by --with-fltk, above
AC_CHECK_PROG(FLUID, fluid, fluid, no)

if test "$FLUID" = no; then
	MSG_ERROR_FLTK_MISSING
fi

dnl ========================================================
dnl = Append the FLAGS variable that contains options for
dnl = debug, profiling and optimizing poser.
dnl ========================================================

FLAGS="$FLAGS_COMMON $FLAGS_OPTIMIZE $FLAGS_PROFILE $FLAGS_PALM_PROFILE $FLAGS_DEBUG"
POSER_CFLAGS="$POSER_CFLAGS $FLAGS $_WARNINGS_CFLAGS $_COMPILER_CFLAGS"
POSER_CXXFLAGS="$POSER_CXXFLAGS $FLAGS $_WARNINGS_CXXFLAGS $_COMPILER_CXXFLAGS"

AC_SUBST(AR)
AC_SUBST(POSER_CFLAGS)
AC_SUBST(POSER_CXXFLAGS)
AC_SUBST(THREAD_FLAGS)
AC_SUBST(THREAD_LIBS)
AC_SUBST(THREAD_SRC)


dnl ========================================================
dnl Determine which file to use for threading support.  NB:
dnl this may be obvious to most UNIX hacks, but it's very
dnl important to put spaces around the '='.  I didn't do
dnl that the first time, and I guess "test" needs those
dnl in order to know that '=' is an operator.  Without the
dnl spaces, I got incorrect results.
dnl ========================================================

AC_OUTPUT(Makefile Gzip/Makefile jpeg/Makefile espws-2.0/Makefile)
