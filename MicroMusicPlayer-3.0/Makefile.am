SUBDIRS = source data man texi desktop

nobase_dist_pkgdata_DATA   =  ./source/defines.h \
                              ./source/dialogs.cpp \
                              ./source/dialogs.h \
                              ./source/folder_parsing.cpp \
                              ./source/folder_parsing.h \
                              ./source/generate_menu.cpp \
                              ./source/generate_menu.h \
                              ./source/global_vars.cpp \
                              ./source/global_vars.h \
                              ./source/gui_configuration.cpp \
                              ./source/gui_configuration.h \
                              ./source/includes.h \
                              ./source/main.cpp \
                              ./source/main.h \
                              ./source/Makefile \
                              ./source/Makefile.am \
                              ./source/Makefile.in \
                              ./source/music_hooks.cpp \
                              ./source/music_hooks.h \
                              ./source/other_callbacks.cpp \
                              ./source/other_callbacks.h \
                              ./source/playing_controls_callback.cpp \
                              ./source/playing_controls_callback.h \
                              ./source/Resizer.cpp \
                              ./source/Resizer.h \
                              ./source/shuffle.cpp \
                              ./source/shuffle.h \
                              ./source/structures.h \
                              ./source/view_playlist.cpp \
                              ./source/view_playlist.h \
                              ./Makefile.mk
                      
EXTRA_DIST = ./Makefile.mk ./texi/mmp.info ./texi/mmp.texi

install-data-hook:
	$(MV) $(DESTDIR)$(pkgdatadir)/Makefile.mk $(DESTDIR)$(pkgdatadir)/Makefile
	$(CHMOD) -R a+rwx "$(DESTDIR)${pkgdatadir}/source"
	if `test ! -d "$(DESTDIR)${pkgdatadir}/bin"` ; then $(MKDIR_P) "$(DESTDIR)${pkgdatadir}/bin" ; fi
	$(CHMOD) -R a+rwx "$(DESTDIR)${pkgdatadir}/bin"
	- if `test ! -d $(HOME)/.local/share` ; then $(MKDIR_P) $(HOME)/.local/share ; $(TOUCH) $(HOME)/.local/share/recently-used.xbel ; fi
	@echo "**********************************"
	@echo "Enjoy using Micro Music Player !!!"
	@echo "**********************************"
                     