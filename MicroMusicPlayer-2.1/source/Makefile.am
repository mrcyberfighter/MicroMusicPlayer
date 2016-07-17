bin_PROGRAMS = MicroMusicPlayer

MicroMusicPlayer_SOURCES =  Resizer.cpp \
                            main.cpp \
                            global_vars.cpp \
                            dialogs.cpp \
                            folder_parsing.cpp \
                            generate_menu.cpp \
                            gui_configuration.cpp \
                            music_hooks.cpp \
                            playing_controls_callback.cpp \
                            shuffle.cpp \
                            view_playlist.cpp

                  

EXTRA_DIST = *.h

MicroMusicPlayer_CPPFLAGS = -DPREFIX=\"$(DESTDIR)$(prefix)\"
          
MicroMusicPlayer_CXXFLAGS = -Wno-deprecated -Wno-deprecated-declarations ${GTK_CFLAGS} ${VLC_CFLAGS}

MicroMusicPlayer_LDADD = ${GTK_LIBS} ${VLC_LIBS}            