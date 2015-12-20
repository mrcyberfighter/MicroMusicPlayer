#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([MicroMusicPlayer], [2.0], [mrcyberfighter@gmail.com], [MicroMusicPlayer-2.0], [http://www.open-source-projects.net/Micro_Music_Player/Micro_Music_Player_presentation.html] )


: ${CXXFLAGS=""}


AC_CONFIG_SRCDIR([./mmp-2.0/Resizer.h])
AC_CONFIG_HEADERS([config.h])

AC_COPYRIGHT([GPLv3])

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P
AC_PROG_LN_S

AC_PATH_PROG([CHMOD], [chmod])
AC_PATH_PROG([CP], [cp])
AC_PATH_PROG([RM], [rm])


PKG_CHECK_MODULES([GTK], [gtk+-3.0], [none], AC_MSG_ERROR(   gtk+3.0 library not detected !!!

   ************* GTK 3 library required for Micro Music Player ************
   Install the GTK 3 library from your package manager or from source
   WARNING: Take care to install the development files from gtk-3 !!!
            Often call: libgtk-3-dev or libgtk-3-devel.

   Then retry to launch the ./configure script...
   ************************************************************************
   ))

PKG_CHECK_MODULES([VLC], [libvlc], [none], AC_MSG_ERROR(   libvlc library not detected !!!

   ************* libvlc library required for Micro Music Player ***********
   Install the libvlc library from your package manager or from source
   WARNING: Take care to install the development files from libvlc !!!
            Often call: libvlc-dev or libvlc-devel.

   WARNING: Install the vlc-nox package too for required codecs !!!

   Then retry to launch the ./configure script...
   ************************************************************************
   ))


# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_STRTOD
AC_CHECK_FUNCS([realpath scandir alphasort])

AC_CONFIG_FILES([Makefile mmp-2.0/Makefile])
AC_OUTPUT

echo \
"********************************************************************************

${PACKAGE_NAME} Version ${PACKAGE_VERSION}
Prefix: ${prefix}
Compiler: ${CXX} ${CXXFLAGS} ${CPPFLAGS}
Depends: gtk+-3.0 libvlc

  Now enter:

  $ make  # Build all binaries

  $ sudo make install # Install Micro Music Player.

You can launch the program with the commandline:
$ MicroMusicPlayer
or
$ mmp # if your system support symbolic links.

or with the icon from your desktop menu.

********************* Enjoy to use Micro Media Player !!! **********************"