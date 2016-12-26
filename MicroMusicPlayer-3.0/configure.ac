AC_PREREQ([2.69])
AC_INIT([Micro Music Player], [3.0], [mrcyberfighter@gmail.com], [MicroMusicPlayer], [www.open-source-projects.net/mmp/mmp])

AC_CONFIG_SRCDIR([./source])

AC_CONFIG_HEADERS([config.h])

AC_LANG([C++])

AC_COPYRIGHT([GPLv3])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CXX_C_O
AC_PROG_CXXCPP

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE([foreign -Wall -Werror])

case $host_os in

  *mingw*)
    platform_win32=yes
    native_win32=yes
    platform_linux=no
    platform_darwin=no
    ;;

  *linux-gnu*)
    platform_linux=yes
    platform_win32=no
    native_win32=no
     platform_darwin=no
    ;;

  pw32* | *cygwin*)
    # Case not work at my site, bad libvlc build.
    platform_win32=yes
    native_win32=no
    platform_linux=no
    platform_darwin=no
    ;;

  *darwin*)
    platform_darwin=yes
    platform_linux=no
    platform_win32=no
    native_win32=no
    ;;

esac

AM_CONDITIONAL(PLATFORM_WIN32, test x"$platform_win32" = "xyes")
AM_CONDITIONAL(NATIVE_WIN32, test x"$native_win32" = "xyes")
AM_CONDITIONAL(PLATFORM_LINUX, test x"$platform_linux" = "xyes")
AM_CONDITIONAL(PLATFORM_DARWIN, test x"$platform_darwin" = "xyes")








# std=c++11 Mac Bug tmp commentedÒ
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

# vector.at(...)
AX_CXX_HAVE_VECTOR_AT

# POSIX programs detection.
AC_PROG_INSTALL
AC_PROG_MKDIR_P
AC_PROG_LN_S
AC_PROG_MAKE_SET
#AC_PROG_SED

# coreutils package
AC_PATH_PROG([CHMOD],       [chmod],      [no])
AC_PATH_PROG([RM],          [rm],         [no])
AC_PATH_PROG([MV],          [mv],         [no])
AC_PATH_PROG([UNLINK],      [unlink],     [no])
AC_PATH_PROG([RMDIR],       [rmdir],      [no])
AC_PATH_PROG([TOUCH],       [touch],      [no])

if test x"$CHMOD" = xno ; then

  AC_MSG_ERROR(Install the coreutils package (chmod is missing) !, 1)

fi


if test x"$RM" = xno ; then

  AC_MSG_ERROR(Install the coreutils package (rm is missing) !, 1)

fi


if test x"$MV" = xno ; then

  AC_MSG_ERROR(Install the coreutils package (mv is missing) !, 1)

fi

if test x"$UNLINK" = xno ; then

  AC_MSG_ERROR(Install the coreutils package (unlink is missing) !, 1)

fi

if test x"$RMDIR" = xno ; then

  AC_MSG_ERROR(Install the coreutils package (rmdir is missing) !, 1)

fi

if test x"$TOUCH" = xno ; then

  AC_MSG_ERROR(Install the coreutils package (touch is missing) !, 1)

fi


# desktop-file-utils package:
AC_PATH_PROG([DESKTOP_FILE_INSTALL],     [desktop-file-install],      [no])
AC_PATH_PROG([UPDATE_DESKTOP_DATABASE],  [update-desktop-database],   [no])
# xdg-utils package:
AC_PATH_PROG([XDG_DESKTOP_MENU],         [xdg-desktop-menu],          [no])

if test x"$DESKTOP_FILE_INSTALL" = xno ; then
if test x"$XDG_DESKTOP_MENU" = xno ; then

  AC_MSG_WARN(Install either the xdg-utils or desktop-file-utils package !)

  AC_MSG_WARN(This is not absolutely required.)

  AC_MSG_WARN(But recommand to install desktop files.)

fi
fi

destop_file_utils=no

if test x"$DESKTOP_FILE_INSTALL" = xno ; then

  AC_MSG_NOTICE(The desktop-file-install tool is used to install the *.desktop file.)
  AC_MSG_NOTICE(The desktop-file-install tool is used to update the cache database)
  AC_MSG_NOTICE(of the MIME types handled by desktop files)

else

desktop_file_utils=yes

fi

xdg_utils=no

if test x"$XDG_DESKTOP_MENU" = xno ; then

  AC_MSG_NOTICE(The xdg-desktop-menu tool is used to install the *.desktop file.)
  AC_MSG_NOTICE(The xdg-desktop-menu tool is used to update the cache database)
  AC_MSG_NOTICE(of the MIME types handled by desktop files)

else

xdg_utils=yes

fi

AM_CONDITIONAL(DESTOP_FILE_UTILS, test x"$destop_file_utils" = "xyes")
AM_CONDITIONAL(XDG_UTILS,         test x"$xdg_utils" = "xyes")

# install-info check.
AC_PATH_PROG([INSTALL_INFO],         [install-info],          [no])

# Checks for libraries.
PKG_CHECK_MODULES([GTK], [gtk+-3.0], [ ], AC_MSG_ERROR(   gtk+3.0 library not detected !!!

   ************** GTK 3 library required for Micro Music Player ***********
   Install the GTK 3 library from your package manager or from source.

   WARNING: Take care to install the development files from gtk-3 !!!
            Often call: libgtk-3-dev or libgtk-3-devel.

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))

PKG_CHECK_MODULES([VLC], [libvlc], [], AC_MSG_ERROR(   libvlc library not detected !!!

   ************* libvlc library required for Micro Music Player ***********

   Install the libvlc library from your package manager or from source.

   GNU/Linux:
   ==========

   WARNING: Take care to install the development files from libvlc !!!
            package often call: libvlc-dev or libvlc-devel.

            Install the vlc-nox package too for the required codecs.

            Install the libvlccore-dev package too.

   Normally vlc-nox and libvlccore-dev are dependencies from libvlc-dev(el).

   WIN32:
   ======

         Try to use the pacman package manager from MSYS2.
         Else take a look at: https://nightlies.videolan.org/build/

   MACOSX:
   =======

          Currently not available with the package manager brew.
          Take a look at http://wwww.open-source-projects/index/
          I will post my build from libvlc for MACOSX.

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))

if test x"$platform_darwin" = "xyes" ; then

  PKG_CHECK_MODULES([GTK_MAC_INTEGRATION], [gtk-mac-integration-gtk3], [], AC_MSG_ERROR(   gtk-mac-integration-gtk3 library not detected !!!

   *** gtk-mac-integration-gtk3 library required for Micro Music Player ***

   Install the gtk-mac-integration-gtk3 library.

   You can easily get it through the package manager brew on Mac OSX.

   $ brew install gtk-mac-integration

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))

  PKG_CHECK_MODULES([GTK_QUARTZ], [gdk-quartz-3.0], [], AC_MSG_ERROR(   gdk-quartz-3.0 library not detected !!!

   ******** gdk-quartz-3.0 library required for Micro Music Player ********

   Install the gdk-quartz-3.0 library.

   You can easily get it through the package manager brew on Mac OSX.

   $ brew install gtk+3 # gdk-quartz-3.0 depends from gtk+3

   Then retry to launch the ./configure script...
   ************************************************************************
   , 1))

fi



# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_INT16_T
AC_TYPE_INT64_T
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([atexit putenv setlocale])

AC_CONFIG_FILES([Makefile
                source/Makefile
                texi/Makefile
                man/Makefile
                data/Makefile
                desktop/Makefile
                ])

AC_OUTPUT

AC_MSG_NOTICE(System check OK !!!)

if test x"$platform_linux" = "xyes" ; then

echo "
  ************************** ${PACKAGE_STRING} ************************

  ${PACKAGE_NAME} a simple play a folder content or file(s) music player.

  Package dependencies: gtk+-3, libvlc.

  Host:     ${host}
  Compiler: ${CXX} ${CXXFLAGS} ${CPPFLAGS}
  Prefix:   ${prefix}

  Author: Brüggemann Eddie <${PACKAGE_BUGREPORT}>.

  Now enter:

  $ make
  $ sudo make install

  To build and install ${PACKAGE_NAME}.

  You can launch the program with the commandline:
  $ MicroMusicPlayer [[dir|file(s)]path]
  or
  $ mmp [[dir|file(s)]path]
  or from your desktop menu, the file manager: \"open with\" option works fine.
"

elif test x"$platform_win32" = "xyes" ; then

echo "
  ************************** ${PACKAGE_STRING} ************************

  ${PACKAGE_NAME} a simple play a folder content or file(s) music player.

  Package dependencies: gtk+-3, libvlc.

  Host:     ${host}
  Compiler: ${CXX} ${CXXFLAGS} ${CPPFLAGS}
  Prefix:   ${prefix}

  Author: Brüggemann Eddie <${PACKAGE_BUGREPORT}>.

  Now enter:

  $ make
  $ sudo make install

  To build and install ${PACKAGE_NAME}.

  You can launch the program with the commandline:
  $ MicroMusicPlayer [[dir|file(s)]path]
  or
  $ mmp [[dir|file(s)]path]
"


elif test x"$platform_darwin" = "xyes" ; then

echo "
************************** ${PACKAGE_STRING} ************************

${PACKAGE_NAME} a simple play a folder content or file(s) music player.

Package dependencies: gtk+-3, libvlc.

Host:     ${host}
Compiler: ${CXX} ${CXXFLAGS} ${CPPFLAGS}
Prefix:   ${prefix}

Author: Brüggemann Eddie <${PACKAGE_BUGREPORT}>.

Now enter:

$ make
$ sudo make install

To build and install ${PACKAGE_NAME}.

You can launch the program with the commandline:
$ MicroMusicPlayer [[dir|file(s)]path]
or
$ mmp [[dir|file(s)]path]
"


else

echo "
  ************************** ${PACKAGE_STRING} ************************

  ${PACKAGE_NAME} a simple play a folder content or file(s) music player.

  Package dependencies: gtk+-3, libvlc.

  Host:     ${host}
  Compiler: ${CXX} ${CXXFLAGS} ${CPPFLAGS}
  Prefix:   ${prefix}

  Author: Brüggemann Eddie <${PACKAGE_BUGREPORT}>.

  Now enter:

  $ make
  $ sudo make install

  To build and install ${PACKAGE_NAME}.

  You can launch the program with the commandline:
  $ MicroMusicPlayer [[dir|file(s)]path]
  or
  $ mmp [[dir|file(s)]path]
  or from your desktop menu.
"

fi