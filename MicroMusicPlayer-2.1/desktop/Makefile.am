desktopdir  = /usr/share/applications

# I don't know if i must write:
#
# $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop
#
# Or
#
# $(desktopdir)/$(PACKAGE_NAME).desktop
#
# So be indulgent Mr the packager.


desktop:
	- @echo "[Desktop Entry]" > $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop
	- @echo "Version=2.0" >> $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop
	- @echo "Name=MicroMusicPlayer" >> $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop
	- @echo "GenericName=Micro Music Player" >> $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop
	- @echo "Comment=Micro Music Player a very simple play a folder content or files music player." >> $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop
	- @echo "Exec=MicroMusicPlayer %F" >> $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop
	- @echo "Icon=$(DESTDIR)$(pkgdatadir)/images/images/Micro_Music_Player.png" >> $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop
	- @echo "Terminal=false" >> $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop
	- @echo "X-MultipleArgs=false" >> $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop
	- @echo "StartupNotify=true" >> $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop
	- @echo "Type=Application" >> $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop
	- @echo "MimeType=audio/mpeg;audio/ogg;audio/x-wav;audio/x-flac;" >> $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop
	- @echo "Keywords=Audio;Player;Song;mmp;mp3;wav;ogg;wav;flac;" >> $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop
	- @echo "Categories=AudioVideo;Audio;Player;GNOME;GTK;" >> $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop
	- @echo "desktop file generated at: $(DESTDIR)$(desktopdir)/$(PACKAGE_NAME).desktop"

update-desktop:
	- $(XDG_DESKTOP_MENU)  install --novendor --mode system "$(desktopdir)/$(PACKAGE_NAME).desktop"
	- $(XDG_DESKTOP_MENU) forceupdate --mode system
          
unupdate-desktop:
	- $(XDG_DESKTOP_MENU) forceupdate --mode system

install-data-hook:
	- $(MAKE) desktop
	- $(MAKE) update-desktop
	$(CHMOD) -R a+rx "$(DESTDIR)$(pkgdatadir)"
	if `test ! -d "$(DESTDIR)$(pkgdatadir)/Configuration"` ; then $(MKDIR_P) $(DESTDIR)$(pkgdatadir)/Configuration ; fi
	$(CHMOD) -R a+rwx "$(DESTDIR)$(pkgdatadir)/Configuration"
	$(MV) "$(DESTDIR)$(pkgdatadir)/Makefile.mk" "$(DESTDIR)$(pkgdatadir)/Makefile"
	$(MKDIR_P) "$(DESTDIR)$(pkgdatadir)/bin"
	$(CHMOD) -R a+rwx "$(DESTDIR)$(pkgdatadir)/source"
	$(CHMOD) -R a+rwx "$(DESTDIR)$(pkgdatadir)/bin"
	if `test ! -L  "$(DESTDIR)$(prefix)/bin/mmp"` ; then $(LN_S) "$(DESTDIR)$(prefix)/bin/$(PACKAGE_NAME)" "$(DESTDIR)$(prefix)/bin/mmp" ; fi

uninstall-hook:
	- $(RM) -f $(desktopdir)/$(PACKAGE_NAME).desktop
	- $(MAKE) unupdate-desktop
	- $(RM) -R -f "$(DESTDIR)$(pkgdatadir)"
	- $(RM) "$(DESTDIR)$(prefix)/bin/mmp"