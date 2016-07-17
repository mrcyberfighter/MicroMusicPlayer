AC_PREREQ([2.69])
AC_INIT([MicroMusicPlayer], [2.1], [mrcyberfighter@gmail.com], [MicroMusicPlayer], [www.open-source-projects.net/Micro_Music_Player/Micro_Music_Player_presentation.html])

AC_CONFIG_SRCDIR([])

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])



AC_LANG([C++])

AC_COPYRIGHT([GPLv3])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CXX_C_O
AC_PROG_CXXCPP

AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

AX_CXX_HAVE_VECTOR_AT

AC_PROG_INSTALL
AC_PROG_MKDIR_P
AC_PROG_LN_S
AC_PROG_MAKE_SET


# coreutils package
AC_PATH_PROG([CHMOD], [chmod], [no])
AC_PATH_PROG([RM],    [rm],    [no])
AC_PATH_PROG([MV],    [mv],   [no])

if test "$CHMOD" = no ; then

  AC_MSG_ERROR(Install the coreutils package !, 1)

fi


if test "$RM" = no ; then

  AC_MSG_ERROR(Install the coreutils package !, 1)

fi


if test "$MV" = no ; then

  AC_MSG_ERROR(Install the coreutils package !, 1)

fi

# xdg-utils package:
AC_PATH_PROG([XDG_DESKTOP_MENU],    [xdg-desktop-menu],   [no])

if test "$XDG_DESKTOP_MENU" = no ; then

  AC_MSG_ERROR(Install the xdg-utils package !, 1)

fi

# Checks for libraries.
PKG_CHECK_MODULES([GTK], [gtk+-3.0], [], AC_MSG_ERROR(   gtk+3.0 library not detected !!!

   ************** GTK 3 library required for Micro Music Player ***********
   Install the GTK 3 library from your package manager or from source.

   WARNING: Take care to install the development files from gtk-3 !!!
            Often call: libgtk-3-dev or libgtk-3-devel.

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))

PKG_CHECK_MODULES([VLC], [libvlc], [], AC_MSG_ERROR(   libvlc library not detected !!!

   ************* libvlc library required for Micro Music Player ***********
   Install the libvlc library from your package manager or from source
   WARNING: Take care to install the development files from libvlc !!!
            Often call: libvlc-dev or libvlc-devel.

   WARNING: Install the vlc-nox package too for required codecs !!!

   NOTE: I think it's better you install the libvlccore-dev package too !

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))



# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT16_T
AC_TYPE_INT64_T
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([realpath setlocale scandir alphasort])

AC_CONFIG_FILES([Makefile
                source/Makefile
                texi/Makefile
                man/Makefile
                data/Makefile
                desktop/Makefile
                ])

AC_OUTPUT

AC_MSG_NOTICE(System check OK !!!)

echo "
  ************************** ${PACKAGE_STRING} ************************

  ${PACKAGE_NAME} a simple play a folder content or file(s) music player.

  Package dependencies: gtk-3, vlc.

  Compiler: ${CXX} ${CXXFLAGS} ${CPPFLAGS}

  Prefix: ${prefix}

  Author: Brüggemann Eddie.
  contact: ${PACKAGE_BUGREPORT}

  Now enter:

  $ make
  $ sudo make install

  To build and install ${PACKAGE_NAME}.

  You can launch the program with the commandline:
  $ MicroMusicPlayer [[dir|file(s)]path]
  or
  $ mmp [[dir|file(s)]path]
  or with the icon from your desktop menu (don't forget the open with option).
"