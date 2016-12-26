bin_PROGRAMS = MicroMusicPlayer

MicroMusicPlayer_SOURCES =  dialogs.cpp \
                            folder_parsing.cpp \
                            generate_menu.cpp \
                            global_vars.cpp \
                            gui_configuration.cpp \
                            main.cpp \
                            music_hooks.cpp \
                            other_callbacks.cpp \
                            playing_controls_callback.cpp \
                            Resizer.cpp \
                            shuffle.cpp \
                            view_playlist.cpp





EXTRA_DIST =  defines.h \
              dialogs.h \
              folder_parsing.h \
              generate_menu.h \
              global_vars.h \
              gui_configuration.h \
              includes.h \
              main.h \
              music_hooks.h \
              other_callbacks.h \
              playing_controls_callback.h \
              Resizer.h \
              shuffle.h \
              structures.h \
              view_playlist.h

MicroMusicPlayer_CPPFLAGS = -DPREFIX=\"$(DESTDIR)$(prefix)\" ${GTK_CFLAGS} ${VLC_CFLAGS}

MicroMusicPlayer_CXXFLAGS = -Wno-deprecated -Wno-deprecated-declarations

MicroMusicPlayer_LDADD = ${GTK_LIBS} ${VLC_LIBS}

MicroMusicPlayer_LDFLAGS =


if PLATFORM_WIN32

if NATIVE_WIN32

MicroMusicPlayer_LDFLAGS += -mwindows

endif

endif

if PLATFORM_DARWIN


# Add the definition of MOCOSX and the gtk-mac-integration and quartz-gtk3 cflags
MicroMusicPlayer_CPPFLAGS += -DMACOSX ${GTK_MAC_INTEGRATION_CFLAGS} ${GTK_QUARTZ_CFLAGS}


#add the gtk-mac-integration and quartz-gtk3 libs
MicroMusicPlayer_LDADD += ${GTK_MAC_INTEGRATION_LIBS} ${GTK_QUARTZ_LIBS}

endif
