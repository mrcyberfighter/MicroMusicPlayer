
AM_MAKEINFOFLAGS = --no-split
AM_MAKEINFOHTMLFLAGS = --no-headers --no-split

info_TEXINFOS = MicroMusicPlayer.texi

install-data-hook:
	- ${INSTALL_DATA} ./mmp.info "$(DESTDIR)/${infodir}"
	- if `test -x $(INSTALL_INFO)` ; then $(INSTALL_INFO) --info-dir="$(DESTDIR)$(infodir)" "$(DESTDIR)$(infodir)/mmp.info" ; fi

uninstall-hook:
	- if `test -f "$(DESTDIR)/${infodir}./mmp.info"` ; then $(RM) -f "$(DESTDIR)/${infodir}./mmp.info" ; fi 