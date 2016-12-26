desktopdir  = $(DESTDIR)$(prefix)/share/applications

desktop_file_name_base_on_id = mmp.mrcyberfighter.desktop

desktop:
	- @echo "[Desktop Entry]" > "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Version=1.0" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Name=Micro Music Player" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "GenericName=Micro Music Player" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Comment=Micro Music Player a very simple play a folder content or files music player." >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Exec=MicroMusicPlayer %F" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Icon=$(DESTDIR)$(pkgdatadir)/images/images/Micro_Music_Player.png" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Terminal=false" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "X-MultipleArgs=false" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "StartupNotify=true" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Type=Application" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "MimeType=audio/mpeg;audio/ogg;audio/flac;audio/x-wav;audio/x-flac;" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Keywords=Audio;Player;Song;mmp;mp3;wav;ogg;wav;flac;" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Categories=AudioVideo;Audio;Player;GNOME;GTK;" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "#DBusActivatable=true" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "desktop file generated at: "$(desktopdir)/$(desktop_file_name_base_on_id)""

update-desktop:
if DESTOP_FILE_UTILS
	- $(DESKTOP_FILE_INSTALL) --rebuild-mime-info-cache "$(desktopdir)/$(desktop_file_name_base_on_id)" ;
	- $(UPDATE_DESKTOP_DATABASE) -q ;
else if XDG_UTILS
	- $(XDG_DESKTOP_MENU)  install --noupdate --novendor --mode system "$(desktopdir)/$(desktop_file_name_base_on_id)" ;
	- $(XDG_DESKTOP_MENU) forceupdate --mode system ;
endif

     
unupdate-desktop:
if DESTOP_FILE_UTILS
	- $(XDG_DESKTOP_MENU) forceupdate --mode system ;
else if XDG_UTILS
	- $(UPDATE_DESKTOP_DATABASE) -q
endif


install-data-hook:
	- $(MAKE) desktop
	- $(MAKE) update-desktop
	$(CHMOD) -R a+rx "$(DESTDIR)$(pkgdatadir)"
	if `test ! -d "$(DESTDIR)$(pkgdatadir)/Configuration"` ; then $(MKDIR_P) $(DESTDIR)$(pkgdatadir)/Configuration ; fi
	$(CHMOD) -R a+rwx "$(DESTDIR)$(pkgdatadir)/Configuration"
	if `test ! -L  "$(DESTDIR)$(bindir)/mmp"` ; then $(LN_S) "$(DESTDIR)$(bindir)/$(PACKAGE_TARNAME)" "$(DESTDIR)$(bindir)/mmp" ; fi

uninstall-hook:
	- $(RM) -f "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- $(MAKE) unupdate-desktop
	- $(RM) -R -f "$(DESTDIR)$(pkgdatadir)"
	- $(RMDIR) -p "$(DESTDIR)$(pkgdatadir)"
	- if `test -L  "$(DESTDIR)$(bindir)/mmp"` ; then $(UNLINK) "$(DESTDIR)$(bindir)/bin/mmp" ; fi