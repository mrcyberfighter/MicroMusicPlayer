/** ***********************************************************************************
  *                                                                                   *
  * mmp (Micro Music Player) a very simple play a folder or files music player.       *
  * Copyright (C) 2015, 2016  Brüggemann Eddie.                                       *
  *                                                                                   *
  * This file is part of mmp (Micro Music Player).                                    *
  * Micro Music Player is free software: you can redistribute it and/or modify        *
  * it under the terms of the GNU General Public License as published by              *
  * the Free Software Foundation, either version 3 of the License, or                 *
  * (at your option) any later version.                                               *
  *                                                                                   *
  * mmp (Micro Music Player) is distributed in the hope that it will be useful,       *
  * but WITHOUT ANY WARRANTY; without even the implied warranty of                    *
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                      *
  * GNU General Public License for more details.                                      *
  *                                                                                   *
  * You should have received a copy of the GNU General Public License                 *
  * along with mmp (Micro Music Player). If not, see <http://www.gnu.org/licenses/>   *
  *                                                                                   *
  ************************************************************************************/

#include "./dialogs.h"

void display_message_dialog(const char *title, const char *msg, GtkMessageType type, GtkButtonsType button_type) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  /** Display a message dialog for informing the user with a message. **/

  GtkWidget *message_dialog = gtk_message_dialog_new(GTK_WINDOW(gui->window), GTK_DIALOG_MODAL, type, button_type, msg, NULL ) ;

  gtk_window_set_icon_from_file(GTK_WINDOW(message_dialog), PATH_TO_PRG_WIN_ICON, NULL) ;
  gtk_window_set_title(GTK_WINDOW(message_dialog), title) ;
  gtk_window_set_transient_for(GTK_WINDOW(message_dialog), GTK_WINDOW(gui->window)) ;
  gtk_window_set_position(GTK_WINDOW(message_dialog), GTK_WIN_POS_CENTER_ON_PARENT) ;
  gtk_window_set_resizable(GTK_WINDOW(message_dialog), FALSE);
  gtk_widget_set_size_request(message_dialog,-1,-1) ;
  gtk_window_set_modal(GTK_WINDOW(message_dialog), TRUE) ;
  gtk_window_set_destroy_with_parent(GTK_WINDOW(message_dialog), TRUE) ;

  g_signal_connect_swapped(G_OBJECT(message_dialog), "response", G_CALLBACK (gtk_widget_destroy), message_dialog) ;

  gtk_dialog_run(GTK_DIALOG(message_dialog) ) ;

}

void display_about_dialog(GtkWidget *widget, gpointer *user_data) {

  /** Display the about window. **/

  GtkWidget *about_dialog = gtk_about_dialog_new() ;

  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog), g_get_application_name() ) ;

  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_dialog), VERSION) ;

  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(PATH_TO_PRG_ICON, NULL);

  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(about_dialog), pixbuf) ;

  g_object_unref(pixbuf) ;

  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog), COPYRIGHT) ;

  char *license_content ;

  g_file_get_contents(PATH_TO_GPLV3, &license_content, NULL, NULL);

  gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(about_dialog), license_content) ;

  gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG(about_dialog), TRUE) ;

  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_dialog), PRGWEBURL) ;

  gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about_dialog), PRGNAME "Website" ) ;

  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog), "Thanks to my beloved mother, my family and to the doctors.\nStay away from drugs: drugs destroy your brain and your life.") ;

  const char *programmer[] = { AUTHOR " " MAIL, NULL } ;

  gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about_dialog),  programmer) ;

  const char *artist[] = { AUTHOR " " MAIL, NULL } ;

  gtk_about_dialog_set_artists( GTK_ABOUT_DIALOG(about_dialog), artist) ;

  const char *documenters[] = { AUTHOR " " MAIL, NULL } ;

  gtk_about_dialog_set_documenters( GTK_ABOUT_DIALOG(about_dialog), documenters) ;

  const char *icon_set_section[] =  { "Oxygen, HighContrast.", NULL } ;

  gtk_about_dialog_add_credit_section(GTK_ABOUT_DIALOG(about_dialog), "Icon sets:", icon_set_section);


  gtk_window_set_icon_from_file(GTK_WINDOW(about_dialog), PATH_TO_PRG_WIN_ICON, NULL) ;
  gtk_window_set_transient_for(GTK_WINDOW(about_dialog), GTK_WINDOW(gui->window)) ;
  gtk_window_set_position(GTK_WINDOW(about_dialog), GTK_WIN_POS_CENTER_ON_PARENT) ;
  gtk_window_set_resizable(GTK_WINDOW(about_dialog), FALSE);
  gtk_widget_set_size_request(about_dialog, -1, -1) ;
  gtk_window_set_destroy_with_parent(GTK_WINDOW(about_dialog), TRUE) ;

  g_signal_connect_swapped(G_OBJECT(about_dialog), "response", G_CALLBACK(gtk_widget_destroy), about_dialog) ;

  gtk_dialog_run(GTK_DIALOG(about_dialog) ) ;

}

void get_files_to_play(GtkWidget *widget, gpointer user_data) {

  /** User single file selection. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  #ifdef G_OS_UNIX

  GtkWidget *file_chooser_dialog = gtk_file_chooser_dialog_new("Choose music files to listen.", GTK_WINDOW(gui->window), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);

  if ( g_strcmp0(current_folder.c_str(), g_get_home_dir()) != 0) {

    // FIXME: You cannot use the shortcuts for selecting multiple files if the current folder is simply $HOME: Bug of GTK+3.20.

    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser_dialog),  current_folder.c_str() ) ;

  }
  else {

    // FIXME: You cannot use the shortcuts for selecting multiple files if the current folder is simply $HOME: Bug of GTK+3.20.

    const char *user_music_folder = g_get_user_special_dir(G_USER_DIRECTORY_MUSIC) ;

    if (user_music_folder != NULL) {

      gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser_dialog),  current_folder.c_str() ) ;

    }

  }


  gtk_file_chooser_set_show_hidden(GTK_FILE_CHOOSER(file_chooser_dialog), FALSE) ;
  gtk_file_chooser_set_create_folders(GTK_FILE_CHOOSER(file_chooser_dialog), FALSE) ;
  gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(file_chooser_dialog), TRUE) ;
  gtk_file_chooser_set_local_only(GTK_FILE_CHOOSER(file_chooser_dialog), TRUE) ;


  GtkFileFilter *file_filter = gtk_file_filter_new() ;

  for (int c=0  ; c < static_cast<int>(extension_list.size()) ; c++) {

    gtk_file_filter_add_pattern(GTK_FILE_FILTER(file_filter),  extension_list.at(c).c_str())         ;

  }

  gtk_file_filter_set_name(GTK_FILE_FILTER(file_filter), "Supported music filetypes") ;

  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser_dialog), GTK_FILE_FILTER(file_filter)) ;


  #ifdef MAC_INTEGRATION
  gtk_window_set_decorated(GTK_WINDOW(file_chooser_dialog), FALSE) ;
  #endif

  gtk_window_set_position(GTK_WINDOW(file_chooser_dialog), GTK_WIN_POS_CENTER_ALWAYS) ;
  gtk_widget_set_size_request(file_chooser_dialog,-1,-1) ;
  gtk_window_set_modal(GTK_WINDOW(file_chooser_dialog), TRUE) ;
  gtk_window_set_destroy_with_parent(GTK_WINDOW(file_chooser_dialog), TRUE) ;
  gtk_window_set_type_hint(GTK_WINDOW(file_chooser_dialog), GDK_WINDOW_TYPE_HINT_DIALOG) ;
  gtk_window_set_transient_for(GTK_WINDOW(file_chooser_dialog), GTK_WINDOW(gui->window)) ;
  #endif


  #ifdef G_OS_WIN32
  GtkFileChooserNative *file_chooser_dialog = NULL ;
  GtkFileChooserAction action =  GTK_FILE_CHOOSER_ACTION_OPEN ;

  file_chooser_dialog = gtk_file_chooser_native_new("Choose music files to listen.",
                                          GTK_WINDOW(gui->window),
                                          action,
                                          "Open",
                                          "Cancel");

  gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(file_chooser_dialog), TRUE) ;

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser_dialog),  current_folder.c_str() ) ;

  gtk_native_dialog_set_modal( GTK_NATIVE_DIALOG(file_chooser_dialog), TRUE) ;

  gtk_native_dialog_set_transient_for( GTK_NATIVE_DIALOG(file_chooser_dialog), GTK_WINDOW(gui->window)) ;

  gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(file_chooser_dialog), current_folder.c_str()) ;
  #endif


  GSList *filepath_list = NULL ;

  gint result ;

  #ifdef G_OS_UNIX
  result = gtk_dialog_run(GTK_DIALOG(file_chooser_dialog));
  #endif

  #ifdef G_OS_WIN32
  result = gtk_native_dialog_run(GTK_NATIVE_DIALOG(file_chooser_dialog));
  #endif

  gchar *folderpath = NULL ;  // Selected folder.

  switch (result) {

    case GTK_RESPONSE_CANCEL :

      #ifdef G_OS_UNIX
      gtk_widget_destroy(file_chooser_dialog);
      #endif

      #ifdef G_OS_WIN32
      gtk_native_dialog_destroy(GTK_NATIVE_DIALOG(file_chooser_dialog)) ;
      #endif

      return ;

    case GTK_RESPONSE_ACCEPT :

      filepath_list = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(file_chooser_dialog)) ;

      gchar *fileuri = gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(file_chooser_dialog));

      gchar *filepath = g_filename_from_uri(fileuri, NULL, NULL) ;

      folderpath = g_path_get_dirname(filepath) ;

      g_free(fileuri) ;

      g_free(filepath) ;

      #ifdef G_OS_UNIX
      gtk_widget_destroy(file_chooser_dialog);
      #endif

      #ifdef G_OS_WIN32
      gtk_native_dialog_destroy(GTK_NATIVE_DIALOG(file_chooser_dialog)) ;
      #endif

      break ;
  }

  if (filepath_list != NULL) {



    current_folder = folderpath ;


    #ifdef G_OS_WIN32
    gchar *utf8_dirname  = g_locale_to_utf8(folderpath, strlen(folderpath), NULL, NULL, NULL) ;

    current_folder = utf8_dirname ;

    g_free(utf8_dirname) ;
    #endif

    if (not check_files(filepath_list)) {

      g_slist_free(filepath_list) ;

      g_free(folderpath) ;

      return ;
    }



    #ifdef DEBUG
    fprintf(stdout,"\n%s current_folder: %s\n", __func__, current_folder.c_str() ) ;
    #endif

    g_slist_free(filepath_list) ;

  }

  // Registering folder into Recent folders manager:
  add_folder_to_recent_folder_list(folderpath) ;

  g_free(folderpath) ;

  #ifdef DEBUG
  vector<size_t> check_size={ imaging_cover_container.size(),
                              title_author_container.size(),
                              album_names_container.size(),
                              folder_music_playlist_container.size(),
                              playlist_shuffle_indexes.size(),
                              playlist_shuffle_back_up.size() } ;

  for (uint8_t c=0, cc=check_size.size()-1 ; c < check_size.size() ; cc=c, ++c) {

    g_assert( check_size.at(c) == check_size.at(cc) ) ;

  }
  #endif

  // Update the the playlist displaying windows content if actually shown.
  change_playlist() ;

  stop_music(NULL, NULL) ;
  // Start playing music.
  play_music(NULL, NULL) ;

  return ;


}


#ifdef G_OS_UNIX
void get_folder_to_play(GtkWidget *widget, gpointer user_data) {

  /** User folder selection. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  GtkWidget *folder_chooser_dialog = gtk_file_chooser_dialog_new("Choose a folder contains music files to listen.", GTK_WINDOW(gui->window), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(folder_chooser_dialog),  current_folder.c_str() ) ;
  gtk_file_chooser_set_show_hidden(GTK_FILE_CHOOSER(folder_chooser_dialog), FALSE) ;
  gtk_file_chooser_set_create_folders(GTK_FILE_CHOOSER(folder_chooser_dialog), FALSE) ;
  gtk_file_chooser_set_use_preview_label(GTK_FILE_CHOOSER(folder_chooser_dialog), TRUE) ;
  gtk_file_chooser_set_local_only(GTK_FILE_CHOOSER(folder_chooser_dialog), TRUE) ;

  gtk_window_set_position(GTK_WINDOW(folder_chooser_dialog), GTK_WIN_POS_CENTER_ALWAYS) ;
  gtk_widget_set_size_request(folder_chooser_dialog,-1,-1) ;


  #ifdef MAC_INTEGRATION
  gtk_window_set_decorated(GTK_WINDOW(folder_chooser_dialog), FALSE) ;
  #endif
  gtk_window_set_modal(GTK_WINDOW(folder_chooser_dialog), TRUE) ;
  gtk_window_set_destroy_with_parent(GTK_WINDOW(folder_chooser_dialog), TRUE) ;
  gtk_window_set_type_hint(GTK_WINDOW(folder_chooser_dialog), GDK_WINDOW_TYPE_HINT_DIALOG) ;
  //gtk_window_set_transient_for(GTK_WINDOW(folder_chooser_dialog), GTK_WINDOW(gui->window)) ;


  gchar *folderpath = NULL ;  // Selected folder.

  gint result = gtk_dialog_run(GTK_DIALOG (folder_chooser_dialog));

  switch (result) {

      case GTK_RESPONSE_CANCEL :


       if (! is_playing) {
         gtk_button_set_label(GTK_BUTTON(gui->folder_chooser_button), "Select a folder to play content") ;
       }

       gtk_widget_destroy(folder_chooser_dialog);

       return ;

      case GTK_RESPONSE_ACCEPT :

        folderpath = gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(folder_chooser_dialog));

        gtk_widget_destroy(folder_chooser_dialog);

        break ;
  }

  if (not parse_folder(folderpath)) {

    g_free(folderpath) ;

    if (folder_chooser_dialog != NULL) {

      gtk_widget_destroy(folder_chooser_dialog);

    }

    return ;
  }



  current_folder = folderpath ;

  #ifdef DEBUG
  fprintf(stdout,"%s current_folder: %s\n", __func__, current_folder.c_str() ) ;
  #endif


  // Registering folder into Recent folders manager:
  add_folder_to_recent_folder_list(folderpath) ;

  g_free(folderpath) ;


  #ifdef DEBUG
  vector<size_t> check_size={ imaging_cover_container.size(),
                              title_author_container.size(),
                              album_names_container.size(),
                              folder_music_playlist_container.size(),
                              playlist_shuffle_indexes.size(),
                              playlist_shuffle_back_up.size() } ;

  for (uint8_t c=0, cc=check_size.size()-1 ; c < check_size.size() ; cc=c, ++c) {

    g_assert( check_size.at(c) == check_size.at(cc) ) ;

  }
  #endif

  change_playlist() ;

  stop_music(NULL, NULL) ;
  // Start playing music.
  play_music(NULL, NULL) ;

  return ;

}
#endif

#ifdef G_OS_WIN32

static void readme_thread(gpointer data) ;

static void readme_thread(gpointer data) {

  // Used as a method to make busy wait less evil.
  g_thread_yield();

  /** The GAppInfo feature of Gio quasi not work on windows, nor on Mac.
    *
    * For displaying the Notice I have try all:
    * From g_spawn_* to g_app_info_launch_* nothing works
    * This finally works: once installed it has a different behavior as launched from cmd.exe  **/

  GAppInfo *app_for_html = g_app_info_get_default_for_type(g_content_type_from_mime_type("text/html"), FALSE) ;

  //fprintf(stdout,"Find the default program for HTML %p\nOoouuuuuufff it was very hard !\n", (void *) app_for_html) ;

  #ifdef DEBUG
  fprintf(stdout,"Default application for html: %s\n", g_app_info_get_name(app_for_html)) ;
  #endif

  // Using the cmd.exe "start program + file[path|uri]"  works.
  GString *gstring_cmdline = g_string_new("start ");

  // This would using the Netscape navigator (v9) on my system instead of the default for HTML.
  //gstring_cmdline = g_string_append(gstring_cmdline, g_app_info_get_name(app_for_html) ) ;
  //gstring_cmdline = g_string_append(gstring_cmdline, " ") ;

  gstring_cmdline = g_string_append(gstring_cmdline,  g_filename_to_uri(PATH_TO_README, NULL, NULL) ) ;

  gchar *cmdline = g_string_free(gstring_cmdline, FALSE) ;

  #ifdef DEBUG
  fprintf(stdout,"cmdline:\n%s\n", cmdline) ;
  fflush(stdout) ;
  #endif

  if ( system( cmdline ) != 0) { // The command line "start + (PROGRAM +) MY_HTML_FILE" work's well except that the Windows console is display a mini moment at launching but disappear as fast.

    display_message_dialog("Error launching notice !","Error by launching the HTML notice \n"
                                            "Sorry ! You can type \"mmp notice\" into your\n"
                                            "Windows O.S search bar.\nTo find the notice of this program.") ;


  }

  if (cmdline != NULL) {

    g_free(cmdline) ;

  }

  g_object_unref(app_for_html) ;

  g_thread_exit(NULL) ;

  return ;
}

#endif

#ifdef MAC_INTEGRATION

static void readme_thread(gpointer data) ;

static void readme_thread(gpointer data) {

  // Used as a method to make busy wait less evil.
  g_thread_yield();

  // Try: Using the cmd.exe "open + file[path|uri]"  works.
  GString *gstring_cmdline = g_string_new("open ");

  GFile *gfile_readme =	g_file_new_for_path( PATH_TO_README ) ;

  gfile_readme = g_file_resolve_relative_path(gfile_readme, PATH_TO_README) ;

  gstring_cmdline = g_string_append(gstring_cmdline,  g_file_get_uri(gfile_readme)) ;

  g_object_unref(gfile_readme) ;

  gchar *cmdline = g_string_free(gstring_cmdline, FALSE) ;

  //#ifdef DEBUG
  fprintf(stdout,"cmdline:\n%s\n", cmdline) ;
  fflush(stdout) ;
  //#endif


  if ( system( cmdline ) != 0) { // The command line "open PROGRAM MY_HTML_FILE" work's well except that the Windows console is display a mini moment at launching but disappear as fast.

    display_message_dialog("Error launching notice !","Error by launching the HTML notice \n"
                                            "Sorry ! You can find the HTML notice into the installation folder\n"
                                            "of the pallication: surely \"/usr(/local)/share/MicroMusicPlayer\".") ;


  }


  if (cmdline != NULL) {

    g_free(cmdline) ;

  }

  g_thread_exit(NULL) ;

  return ;
}

#endif


void launch_notice_html(GtkWidget *widget, gpointer user_data) {

  /** Launch the README file to display it to the user through the GUI. **/

  GError *error = NULL ;

  if (! g_file_test(PATH_TO_README, G_FILE_TEST_EXISTS) ) {


    fprintf(stderr,"Error find notice file\n%s", error->message) ;

    g_error_free(error) ;

    error = NULL ;

    return ;

  }






  #ifdef G_OS_UNIX

  #ifndef MAC_INTEGRATION

  // This doesn't work on MACOSX !
  GFile *g_file_readme = g_file_new_for_path(PATH_TO_README) ;

  gchar *readme_uri = g_file_get_uri(g_file_readme) ;


  GAppLaunchContext *app_launch_context = g_app_launch_context_new() ;

  g_app_info_launch_default_for_uri(readme_uri, app_launch_context, &error) ;


  g_object_unref(app_launch_context) ;

  g_free(readme_uri) ;

  g_object_unref(g_file_readme) ;

  #else

  // Using Glib threads on Mac and Windows for displaying the notice without blocking the interface:
  // it's freaking because the Gio methods deosn't works on Mac and Windows !

  GThread *readme_display_thread = g_thread_try_new("launch_readme_thread",
                                                    (GThreadFunc) readme_thread,
                                                    NULL,
                                                    &error) ;

  if (error != NULL) {

    string msg = "Error by launching the NOTICE\n" ;

    msg += error->message ;

    display_message_dialog("Error !", msg.c_str()) ;

    g_error_free(error) ;

    error = NULL ;

  }

  g_thread_unref(readme_display_thread) ;

  #endif
  #endif





  #ifdef G_OS_WIN32

  // Using Glib threads on Mac and Windows for displaying the notice without blocking the interface:
  // it's freaking because the Gio methods deosn't works on Mac and Windows !

  GThread *readme_display_thread = g_thread_try_new("launch_readme_thread",
                                                    (GThreadFunc) readme_thread,
                                                    NULL,
                                                    &error) ;

  if (error != NULL) {

    string msg = "Error by launching the NOTICE\n" ;

    msg += error->message ;

    display_message_dialog("Error !", msg.c_str()) ;

    g_error_free(error) ;

    error = NULL ;

  }

  g_thread_unref(readme_display_thread) ;

  #endif



  return ;

}

void configure_program_dialog(GtkWidget *widget, gpointer user_data) {

  /** Program configuration dailog window. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  GtkWidget *configure_dialog = gtk_dialog_new() ;



  gtk_window_set_icon_from_file(GTK_WINDOW(configure_dialog), PATH_TO_PRG_WIN_ICON, NULL) ;
  gtk_window_set_title(GTK_WINDOW(configure_dialog), "Configure program") ;
  gtk_window_set_type_hint(GTK_WINDOW(configure_dialog), GDK_WINDOW_TYPE_HINT_NORMAL) ;
  gtk_window_set_transient_for(GTK_WINDOW(configure_dialog), GTK_WINDOW(gui->window)) ;
  gtk_window_set_position(GTK_WINDOW(configure_dialog), GTK_WIN_POS_CENTER_ON_PARENT) ;
  gtk_window_set_resizable(GTK_WINDOW(configure_dialog), FALSE);
  gtk_widget_set_size_request(configure_dialog,-1,-1) ;
  gtk_window_set_modal(GTK_WINDOW(configure_dialog), FALSE) ;
  gtk_window_set_destroy_with_parent(GTK_WINDOW(configure_dialog), TRUE) ;
  gtk_window_set_decorated(GTK_WINDOW(configure_dialog), TRUE) ;


  #define DIALOG_DEFAULT_SPACE 12

  gtk_container_set_border_width(GTK_CONTAINER(configure_dialog), DIALOG_DEFAULT_SPACE) ;

  /** ***** [START] Icon set choice [START] ***** **/

  GtkWidget *icon_set_choice_frame = gtk_frame_new(" Icon set ") ;

  gtk_container_set_border_width(GTK_CONTAINER(icon_set_choice_frame), DIALOG_DEFAULT_SPACE/2) ;

  GtkWidget *icon_set_choice_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(icon_set_choice_hbox), DIALOG_DEFAULT_SPACE) ;

  gtk_box_set_spacing(GTK_BOX(icon_set_choice_hbox), DIALOG_DEFAULT_SPACE) ;

  gtk_box_set_homogeneous(GTK_BOX(icon_set_choice_hbox), TRUE) ;


  GtkWidget *radiobutton_icons_high_contrast = gtk_radio_button_new_with_label(NULL, " HighContrast") ;

  GtkWidget *image_icons_high_contrast       ;

  GtkWidget *radiobutton_icons_oxygen        = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(radiobutton_icons_high_contrast)), " Oxygen") ;

  GtkWidget *image_icons_oxygen              ;


  gtk_widget_set_tooltip_markup(radiobutton_icons_high_contrast, "Set the <b>HighContrast</b> theme icon set.\nThis will update the interface.\nBut you must press the <b>Apply</b> button to store your configuration.") ;
  gtk_widget_set_tooltip_markup(radiobutton_icons_oxygen,        "Set the <b>Oxygen</b> theme icon set.\nThis will update the interface.\nBut you must press the <b>Apply</b> button to store your configuration.") ;

  gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(radiobutton_icons_high_contrast), FALSE) ;
  gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(radiobutton_icons_oxygen),        FALSE) ;


  if (settings.icon_set_oxygen) {

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton_icons_oxygen), TRUE) ;

    #ifdef G_OS_UNIX
    image_icons_high_contrast = gtk_image_new_from_file( PATH_TO_HIGH_CONTRAST_BUTTON_ICONS  "face-angry.png")     ;

    image_icons_oxygen        = gtk_image_new_from_file( PATH_TO_OXYGEN_BUTTON_ICONS         "face-smile-big.png") ;
    #endif


    #ifdef G_OS_WIN32
    gchar *angry_image_path = g_strdup_printf("%s%s",PATH_TO_HIGH_CONTRAST_BUTTON_ICONS,  "face-angry.png") ;

    gchar *smile_image_path = g_strdup_printf("%s%s",PATH_TO_OXYGEN_BUTTON_ICONS,  "face-smile-big.png") ;

    image_icons_high_contrast = gtk_image_new_from_file(angry_image_path)      ;

    image_icons_oxygen        = gtk_image_new_from_file(smile_image_path) ;

    g_free(angry_image_path) ;
    g_free(smile_image_path) ;
    #endif

  }
  else {

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton_icons_high_contrast), TRUE) ;

    #ifdef G_OS_UNIX
    image_icons_high_contrast = gtk_image_new_from_file( PATH_TO_HIGH_CONTRAST_BUTTON_ICONS  "face-smile-big.png") ;

    image_icons_oxygen        = gtk_image_new_from_file( PATH_TO_OXYGEN_BUTTON_ICONS         "face-angry.png")     ;
    #endif


    #ifdef G_OS_WIN32
    gchar *angry_image_path = g_strdup_printf("%s%s",PATH_TO_OXYGEN_BUTTON_ICONS,  "face-angry.png") ;

    gchar *smile_image_path = g_strdup_printf("%s%s",PATH_TO_HIGH_CONTRAST_BUTTON_ICONS,  "face-smile-big.png") ;

    image_icons_high_contrast = gtk_image_new_from_file( smile_image_path) ;

    image_icons_oxygen        = gtk_image_new_from_file( angry_image_path)  ;
    #endif


  }


  gtk_button_set_image(GTK_BUTTON(radiobutton_icons_high_contrast), image_icons_high_contrast) ;

  gtk_button_set_always_show_image(GTK_BUTTON(radiobutton_icons_high_contrast), TRUE) ;

  gtk_button_set_image(GTK_BUTTON(radiobutton_icons_oxygen), image_icons_oxygen) ;

  gtk_button_set_always_show_image(GTK_BUTTON(radiobutton_icons_oxygen), TRUE)   ;





  gtk_box_pack_start(GTK_BOX(icon_set_choice_hbox), radiobutton_icons_high_contrast, TRUE,  TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(icon_set_choice_hbox), radiobutton_icons_oxygen,        TRUE,  TRUE, 0) ;

  gtk_container_add(GTK_CONTAINER(icon_set_choice_frame), icon_set_choice_hbox) ;

  /** ***** [END] Icon set choice [END] ***** **/



  /** ***** [START] Playing settings [START] ***** **/

  GtkWidget *playing_settings_frame = gtk_frame_new(" Player settings ") ;

  gtk_container_set_border_width(GTK_CONTAINER(playing_settings_frame), DIALOG_DEFAULT_SPACE/2) ;

  GtkWidget *playing_settings_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(playing_settings_vbox), DIALOG_DEFAULT_SPACE) ;

  gtk_box_set_spacing(GTK_BOX(playing_settings_vbox), DIALOG_DEFAULT_SPACE) ;


  GtkWidget *playing_settings_repeat_all = gtk_radio_button_new_with_label(NULL, " Repeat all") ;

  GtkWidget *playing_settings_repeat_one = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON(playing_settings_repeat_all), " Repeat one" ) ;

  GtkWidget *playing_settings_repeat_off = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON(playing_settings_repeat_one), " Repeat off" ) ;

  gtk_widget_set_tooltip_markup(playing_settings_repeat_all, "Enable the <b>repeat all</b> feature.\n"
                                                             "This will update the player settings.\n"
                                                             "But you must press the <b>Apply</b> button to store your configuration.") ;

  gtk_widget_set_tooltip_markup(playing_settings_repeat_one, "Enable the <b>repeat one</b> feature.\n"
                                                             "This will update the player settings.\n"
                                                             "But you must press the <b>Apply</b> button to store your configuration.") ;

  gtk_widget_set_tooltip_markup(playing_settings_repeat_off, "Disable the <b>repeating</b> feature.\n"
                                                             "This will update the player settings.\n"
                                                             "But you must press the <b>Apply</b> button to store your configuration.") ;


  switch (is_repeat_all) {

    case 0 :

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(playing_settings_repeat_off), TRUE ) ;
      break ;

    case 1 :

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(playing_settings_repeat_all), TRUE ) ;
      break ;

    case 2 :

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(playing_settings_repeat_off), TRUE ) ;
      break ;

    default :

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(playing_settings_repeat_off), TRUE ) ;
      break ;
  }













  GtkWidget *playing_settings_shuffle = gtk_check_button_new_with_label(" Shuffle mode. ") ;

  gtk_widget_set_tooltip_markup(playing_settings_shuffle, "Enable the <b>shuffle</b> feature.\n"
                                                          "This will update the player settings.\n"
                                                          "But you must press the <b>Apply</b> button to store your configuration.") ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(playing_settings_shuffle), is_shuffle ) ;

  GtkWidget *playing_settings_volume_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;



  GtkWidget *playing_settings_volume_label_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *playing_settings_volume_image      = gtk_image_new_from_file( (settings.path_to_button_icons + "audio-volume-medium.png").c_str() ) ;

  GtkWidget *playing_settings_volume_label      = gtk_label_new(" Default Volume:") ;

  gtk_box_pack_start(GTK_BOX(playing_settings_volume_label_hbox), playing_settings_volume_image, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(playing_settings_volume_label_hbox), playing_settings_volume_label, FALSE, FALSE, 0) ;


  GtkWidget *playing_settings_volume_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 1.0, 0.01) ;



  gtk_widget_set_tooltip_markup(playing_settings_volume_scale,  "Set the <b>default player volume</b> at start.\n"
                                                                "This will update the interface.\n"
                                                                "But you must press the <b>Apply</b> button to store your configuration.") ;

  gtk_range_set_value(GTK_RANGE(playing_settings_volume_scale), gtk_scale_button_get_value(GTK_SCALE_BUTTON(gui->button_volume))) ;

  gtk_scale_set_draw_value(GTK_SCALE(playing_settings_volume_scale), TRUE) ;
  gtk_scale_set_has_origin(GTK_SCALE(playing_settings_volume_scale), TRUE) ;

  gtk_scale_set_value_pos(GTK_SCALE(playing_settings_volume_scale), GTK_POS_TOP) ;

  gtk_scale_add_mark(GTK_SCALE(playing_settings_volume_scale), 0.5, GTK_POS_TOP, NULL) ;



  gtk_box_pack_start(GTK_BOX(playing_settings_volume_hbox), playing_settings_volume_label_hbox, FALSE,  FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(playing_settings_volume_hbox), playing_settings_volume_scale,      TRUE,   TRUE,  0) ;



  gtk_box_pack_start(GTK_BOX(playing_settings_vbox), playing_settings_repeat_all,               FALSE, FALSE, 0)   ;
  gtk_box_pack_start(GTK_BOX(playing_settings_vbox), playing_settings_repeat_one,               FALSE, FALSE, 0)   ;
  gtk_box_pack_start(GTK_BOX(playing_settings_vbox), playing_settings_repeat_off,               FALSE, FALSE, 0)   ;
  gtk_box_pack_start(GTK_BOX(playing_settings_vbox), playing_settings_shuffle,                  FALSE, FALSE, 0)   ;
  gtk_box_pack_start(GTK_BOX(playing_settings_vbox), playing_settings_volume_hbox,              FALSE, FALSE, 0)   ;

  gtk_container_add(GTK_CONTAINER(playing_settings_frame), playing_settings_vbox) ;

  /** ***** [END] Playing settings [END] ***** **/



  /** ***** [START] Interface size setting [START] ***** **/

  GtkWidget *interface_size_frame = gtk_frame_new(" Interface size ") ;

  gtk_container_set_border_width(GTK_CONTAINER(interface_size_frame), DIALOG_DEFAULT_SPACE/2) ;

  GtkWidget *interface_size_main_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *interface_size_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(interface_size_hbox), DIALOG_DEFAULT_SPACE) ;

  GtkWidget *interface_min_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(interface_min_hbox), DIALOG_DEFAULT_SPACE) ;

  GtkWidget *interface_size_radiobutton_little = gtk_radio_button_new_with_label(NULL, " Little") ;
  GtkWidget *interface_size_radiobutton_middle = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(interface_size_radiobutton_little)), " Medium") ;
  GtkWidget *interface_size_radiobutton_big    = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(interface_size_radiobutton_little)), "  Big  ") ;

  GtkWidget *interface_size_little_image       = gtk_image_new_from_file((settings.path_to_button_icons + "interface-little.png").c_str() ) ;
  GtkWidget *interface_size_middle_image       = gtk_image_new_from_file((settings.path_to_button_icons + "interface-middle.png").c_str() ) ;
  GtkWidget *interface_size_big_image          = gtk_image_new_from_file((settings.path_to_button_icons + "interface-big.png").c_str()    ) ;

  gtk_widget_set_tooltip_markup(interface_size_radiobutton_little, "Set the <b>interface size</b> on <b>little</b>.\n"
                                                                    "This will update the interface.\n"
                                                                    "But you must press the <b>Apply</b> button to store your configuration.") ;

  gtk_widget_set_tooltip_markup(interface_size_radiobutton_middle, "Set the <b>interface size</b> on <b>middle</b>.\n"
                                                                   "This will update the interface.\n"
                                                                   "But you must press the <b>Apply</b> button to store your configuration.") ;

  gtk_widget_set_tooltip_markup(interface_size_radiobutton_big,    "Set the <b>interface size</b> on <b>big</b>.\n"
                                                                   "This will update the interface.\n"
                                                                   "But you must press the <b>Apply</b> button to store your configuration.")    ;

  gtk_button_set_image(GTK_BUTTON(interface_size_radiobutton_little), interface_size_little_image) ;
  gtk_button_set_image(GTK_BUTTON(interface_size_radiobutton_middle), interface_size_middle_image) ;
  gtk_button_set_image(GTK_BUTTON(interface_size_radiobutton_big),    interface_size_big_image   ) ;

  gtk_button_set_always_show_image(GTK_BUTTON(interface_size_radiobutton_little), TRUE) ;
  gtk_button_set_always_show_image(GTK_BUTTON(interface_size_radiobutton_middle), TRUE) ;
  gtk_button_set_always_show_image(GTK_BUTTON(interface_size_radiobutton_big),    TRUE) ;

  gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(interface_size_radiobutton_little), FALSE) ;
  gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(interface_size_radiobutton_middle), FALSE) ;
  gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(interface_size_radiobutton_big),    FALSE) ;


  GtkWidget *interface_min_toggle = gtk_toggle_button_new_with_label("Minimal interface") ;

  GtkWidget *interface_min_image  = gtk_image_new_from_file( (settings.path_to_button_icons + "window-minimize.png").c_str()    ) ;

  gtk_widget_set_tooltip_markup(interface_min_toggle, "Enable/Disable the <b>Minimal interface</b> feature.\n"
                                                      "This will update the interface.\n"
                                                      "But you must press the <b>Apply</b> button to store your configuration.") ;



  switch (settings.image_resized_size) {

    case IMAGE_RESIZED_SIZE_LITTLE :

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(interface_size_radiobutton_little), TRUE) ;
      break ;

    case IMAGE_RESIZED_SIZE_MIDDLE :

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(interface_size_radiobutton_middle), TRUE) ;
      break ;

    case IMAGE_RESIZED_SIZE_BIG :

      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(interface_size_radiobutton_big),    TRUE) ;
      break ;

    default :
      break ;
  }



  gtk_button_set_image(GTK_BUTTON(interface_min_toggle), interface_min_image) ;

  gtk_button_set_always_show_image(GTK_BUTTON(interface_min_toggle),  TRUE)   ;

  gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(interface_min_toggle), FALSE)  ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(interface_min_toggle), settings.minimal_interface) ;


  gtk_box_pack_start(GTK_BOX(interface_size_hbox), interface_size_radiobutton_little, TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(interface_size_hbox), interface_size_radiobutton_middle, TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(interface_size_hbox), interface_size_radiobutton_big,    TRUE, TRUE, 0) ;

  gtk_box_set_homogeneous(GTK_BOX(interface_size_hbox), TRUE) ;

  gtk_box_set_spacing(GTK_BOX(interface_size_hbox), DIALOG_DEFAULT_SPACE) ;



  gtk_box_pack_start(GTK_BOX(interface_min_hbox), gtk_label_new(""),    TRUE,   TRUE,   0) ;
  gtk_box_pack_start(GTK_BOX(interface_min_hbox), interface_min_toggle, FALSE,  FALSE,  0) ;
  gtk_box_pack_start(GTK_BOX(interface_min_hbox), gtk_label_new(""),    TRUE,   TRUE,   0) ;

  gtk_box_set_spacing(GTK_BOX(interface_min_hbox), DIALOG_DEFAULT_SPACE/2) ;



  gtk_box_pack_start(GTK_BOX(interface_size_main_vbox), interface_size_hbox,    FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(interface_size_main_vbox), interface_min_hbox,     FALSE, FALSE, 0) ;

  gtk_container_add(GTK_CONTAINER(interface_size_frame), interface_size_main_vbox) ;

  /** ***** [END] Interface size setting [END] ***** **/



  /** ***** [START] Music folder setting [START] ***** **/



  GtkWidget *folder_selecting_frame = gtk_frame_new(" Music folder ") ;

  gtk_container_set_border_width(GTK_CONTAINER(folder_selecting_frame), DIALOG_DEFAULT_SPACE/2) ;

  GtkWidget *folder_selecting_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;


  gtk_container_set_border_width(GTK_CONTAINER(folder_selecting_box), DIALOG_DEFAULT_SPACE) ;



  const char *user_music_folder = g_get_user_special_dir(G_USER_DIRECTORY_MUSIC) ;

  #ifdef G_OS_UNIX
  GtkWidget *folder_selecting_button = gtk_file_chooser_button_new("Set the Music folder to open per default.", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER) ;

  gtk_widget_set_tooltip_markup(folder_selecting_button, "Set the folder to open per default: your <b>default music folder</b>.\n<i>The default folder from the folder selector</i>.\nSet it simply to your <b>Music folder</b>.\nChanges are immediatly applied.\nBut you must press the <b>Apply</b> button to store your configuration.") ;

  gtk_file_chooser_button_set_title(GTK_FILE_CHOOSER_BUTTON(folder_selecting_button), "Set the Music folder to open per default.") ;

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(folder_selecting_button), (g_file_test(settings.path_to_music_folder.c_str(), G_FILE_TEST_IS_DIR)) ? settings.path_to_music_folder.c_str() : (user_music_folder != NULL) ? user_music_folder : g_get_home_dir()  ) ;
  #endif


  #ifdef G_OS_WIN32
  GtkWidget *folder_selecting_button = gtk_button_new_with_label( g_path_get_basename((g_file_test(settings.path_to_music_folder.c_str(), G_FILE_TEST_IS_DIR)) ? settings.path_to_music_folder.c_str() : (user_music_folder != NULL) ? user_music_folder : g_get_home_dir()) ) ;

  gtk_widget_set_sensitive( folder_selecting_button, FALSE ) ;

  gtk_widget_set_tooltip_text(folder_selecting_button, "Feature not available for Windows !") ;
  #endif

  gtk_box_pack_start(GTK_BOX(folder_selecting_box), folder_selecting_button,  TRUE, TRUE, 0)   ;

  gtk_container_add(GTK_CONTAINER(folder_selecting_frame), folder_selecting_box) ;



  /** ***** [START] Theme variant chooser [START] ***** **/

  GtkWidget *theme_selecting_frame = gtk_frame_new(" Theme ") ;

  gtk_container_set_border_width(GTK_CONTAINER(theme_selecting_frame), DIALOG_DEFAULT_SPACE/2) ;

  GtkWidget *theme_selecting_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12) ;

  gtk_box_set_homogeneous(GTK_BOX(theme_selecting_box), TRUE) ;

  gtk_box_set_spacing(GTK_BOX(theme_selecting_box), DIALOG_DEFAULT_SPACE) ;

  gtk_container_set_border_width(GTK_CONTAINER(theme_selecting_box), DIALOG_DEFAULT_SPACE) ;

  GtkWidget *radiobutton_theme_light = gtk_radio_button_new_with_label(NULL, " Light ") ;

  GtkWidget *radiobutton_theme_dark  = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(radiobutton_theme_light)), " Dark ") ;

  gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(radiobutton_theme_light), FALSE) ;
  gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(radiobutton_theme_dark),  FALSE) ;

  GtkWidget *theme_light_image  = gtk_image_new_from_file((settings.path_to_button_icons + "weather-clear.png").c_str()    ) ;

  GtkWidget *theme_dark_image   = gtk_image_new_from_file((settings.path_to_button_icons + "weather-clear-night.png").c_str()    ) ;


  gtk_button_set_image(GTK_BUTTON(radiobutton_theme_light),   theme_light_image)  ;
  gtk_button_set_image(GTK_BUTTON(radiobutton_theme_dark),    theme_dark_image)   ;

  gtk_button_set_always_show_image(GTK_BUTTON(radiobutton_theme_light),   TRUE)  ;
  gtk_button_set_always_show_image(GTK_BUTTON(radiobutton_theme_dark),    TRUE)  ;

  if (settings.theme_light) {

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton_theme_light), TRUE) ;

  }
  else {

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton_theme_dark), TRUE) ;

  }

  gtk_box_pack_start(GTK_BOX(theme_selecting_box), radiobutton_theme_light,    TRUE, TRUE, 0)   ;
  gtk_box_pack_start(GTK_BOX(theme_selecting_box), radiobutton_theme_dark,     TRUE, TRUE, 0)   ;

  gtk_container_add(GTK_CONTAINER(theme_selecting_frame), theme_selecting_box) ;



  /** ***** [END] Theme variant chooser [END] ***** **/



  /** ***** [START] Dialog main content box [START] ***** **/

  GtkWidget *content_area = gtk_dialog_get_content_area( GTK_DIALOG(configure_dialog) ) ;



  GtkWidget *configuration_main_notebook    = gtk_notebook_new() ;

  GtkWidget *player_settings_main_vbox      = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *appearence_settings_main_vbox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;



  gtk_box_pack_start(GTK_BOX(player_settings_main_vbox), playing_settings_frame, FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(player_settings_main_vbox), folder_selecting_frame, FALSE, FALSE, 0) ;



  gtk_box_pack_start(GTK_BOX(appearence_settings_main_vbox), icon_set_choice_frame,  FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(appearence_settings_main_vbox), theme_selecting_frame,  FALSE, FALSE, 0) ;

  gtk_box_pack_start(GTK_BOX(appearence_settings_main_vbox), interface_size_frame,   FALSE, FALSE, 0) ;


  gtk_box_set_spacing(GTK_BOX(content_area), DIALOG_DEFAULT_SPACE) ;





  #ifdef G_OS_UNIX
  #ifndef MAC_INTEGRATION

  GtkWidget *misc_settings_main_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  GtkWidget *set_as_default_frame = gtk_frame_new(" Set as default ") ;

  gtk_container_set_border_width(GTK_CONTAINER(set_as_default_frame), DIALOG_DEFAULT_SPACE/2) ;

  GtkWidget *set_as_default_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12) ;


  GtkWidget *set_as_default_button      = gtk_button_new_with_label("   Set as default music player ") ;

  GtkWidget *reset_associations_button  = gtk_button_new_with_label("   Reset files associations       ") ;

  GtkWidget *set_as_default_image       = gtk_image_new_from_file((settings.path_to_button_icons + "face-angel.png").c_str()    ) ;

  GtkWidget *reset_associations_image   = gtk_image_new_from_file((settings.path_to_button_icons + "face-devilish.png").c_str()    ) ;

  gtk_button_set_image(GTK_BUTTON(set_as_default_button),     set_as_default_image)     ;
  gtk_button_set_image(GTK_BUTTON(reset_associations_button), reset_associations_image) ;

  gtk_button_set_always_show_image(GTK_BUTTON(set_as_default_button),       TRUE)  ;
  gtk_button_set_always_show_image(GTK_BUTTON(reset_associations_button),   TRUE)  ;

  gtk_box_pack_start(GTK_BOX(set_as_default_box), set_as_default_button,      FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(set_as_default_box), reset_associations_button,  FALSE, FALSE, 0) ;

  gtk_box_set_spacing(GTK_BOX(set_as_default_box), DIALOG_DEFAULT_SPACE) ;

  gtk_box_set_homogeneous(GTK_BOX(set_as_default_box), TRUE) ;

  gtk_container_set_border_width(GTK_CONTAINER(set_as_default_box), DIALOG_DEFAULT_SPACE) ;

  gtk_container_add(GTK_CONTAINER(set_as_default_frame), set_as_default_box) ;



  GtkWidget *send_notifications_frame = gtk_frame_new(" Notifications ") ;

  gtk_container_set_border_width(GTK_CONTAINER(send_notifications_frame), DIALOG_DEFAULT_SPACE/2) ;

  GtkWidget *send_notifications_check_button = gtk_check_button_new_with_label("  Send notifications  ") ;

  gtk_widget_set_tooltip_text(send_notifications_check_button, "Enable/Disable notifications:\n\n"
                                                               "There is no guarantee that the notification is displayed immediately,\n"
                                                               "or even at all.") ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(send_notifications_check_button), settings.send_notification) ;

  gtk_container_set_border_width(GTK_CONTAINER(send_notifications_check_button), DIALOG_DEFAULT_SPACE) ;

  gtk_container_add(GTK_CONTAINER(send_notifications_frame), send_notifications_check_button) ;


  gtk_box_pack_start(GTK_BOX(misc_settings_main_vbox),  set_as_default_frame,     FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(misc_settings_main_vbox),  send_notifications_frame, FALSE, FALSE, 0) ;
  #endif
  #endif

  gtk_notebook_append_page(GTK_NOTEBOOK(configuration_main_notebook), player_settings_main_vbox,      gtk_label_new("Player settings")) ;
  gtk_notebook_append_page(GTK_NOTEBOOK(configuration_main_notebook), appearence_settings_main_vbox,  gtk_label_new("Appearance")) ;

  #ifdef G_OS_UNIX
  #ifndef MAC_INTEGRATION
  gtk_notebook_append_page(GTK_NOTEBOOK(configuration_main_notebook), misc_settings_main_vbox,        gtk_label_new("Misc")) ;
  #endif
  #endif

  gtk_box_pack_start(GTK_BOX(content_area), configuration_main_notebook, FALSE, FALSE, 0) ;


  /** ***** [END] Dialog main content box [END] ***** **/



  /** ***** [START] Dialog action buttons [START] ***** **/

  // Using the action action area is depreecated but very usefull for displaying a buttons with icons
  // on the bottom of the dialog.
  // Instead of the using the header-bar which the gtk+-3 developers want us to use.

  GtkWidget *button_close = gtk_button_new_with_label("Close") ;

  GtkWidget *image_close  = gtk_image_new_from_file((settings.path_to_button_icons + "dialog-close.png").c_str()) ;

  gtk_widget_set_tooltip_markup(button_close, "<b>Close</b> the configuration window and don't store any setting.") ;

  gtk_button_set_image(GTK_BUTTON(button_close), image_close) ;

  gtk_button_set_always_show_image(GTK_BUTTON(button_close), TRUE) ;


  GtkWidget *button_ok = gtk_button_new_with_label("Apply") ;

  GtkWidget *image_ok  = gtk_image_new_from_file((settings.path_to_button_icons + "dialog-ok.png").c_str()) ;

  gtk_widget_set_tooltip_markup(button_ok, "<b>Register</b> all the settings as <i>your default configuration</i> at start.") ;

  gtk_button_set_image(GTK_BUTTON(button_ok), image_ok) ;

  gtk_button_set_always_show_image(GTK_BUTTON(button_ok), TRUE) ;


  gtk_dialog_add_action_widget(GTK_DIALOG(configure_dialog), button_close, GTK_RESPONSE_CLOSE) ;

  gtk_dialog_add_action_widget(GTK_DIALOG(configure_dialog), button_ok,     GTK_RESPONSE_APPLY)  ;

  // Deprecated but usefull to configure the action area of a GTK_DIALOG.
  GtkWidget *action_area = gtk_dialog_get_action_area(GTK_DIALOG(configure_dialog)) ;

  gtk_container_set_border_width(GTK_CONTAINER(action_area), 0) ;

  gtk_button_box_set_layout(GTK_BUTTON_BOX(action_area), GTK_BUTTONBOX_EDGE) ;

  /** ***** [END] Dialog action buttons [END] ***** **/




  // Using a structure to pass all required parameters to the function: configure_high_contrast_radiobutton(...).
  Radio_Config high_contrast_radiobutton ;

  high_contrast_radiobutton.button  = radiobutton_icons_high_contrast ;
  high_contrast_radiobutton.image   = image_icons_high_contrast       ;

  high_contrast_radiobutton.volume  = playing_settings_volume_image       ;
  high_contrast_radiobutton.cancel  = image_close    ;
  high_contrast_radiobutton.apply   = image_ok       ;

  high_contrast_radiobutton.little  = interface_size_little_image ;
  high_contrast_radiobutton.middle  = interface_size_middle_image ;
  high_contrast_radiobutton.big     = interface_size_big_image    ;

  high_contrast_radiobutton.min     = interface_min_image ;

  #ifdef G_OS_UNIX
  #ifndef MAC_INTEGRATION
  high_contrast_radiobutton.set_as_default     = set_as_default_image     ;
  high_contrast_radiobutton.reset_association  = reset_associations_image ;
  #endif
  #endif

  high_contrast_radiobutton.theme_light = theme_light_image   ;
  high_contrast_radiobutton.theme_dark  = theme_dark_image    ;


  // Using a structure to pass all required parameters to the function: configure_oxygen_radiobutton(...).
  Radio_Config oxygen_radiobutton ;

  oxygen_radiobutton.button  = radiobutton_icons_oxygen ;
  oxygen_radiobutton.image   = image_icons_oxygen       ;

  oxygen_radiobutton.volume  = playing_settings_volume_image       ;
  oxygen_radiobutton.cancel  = image_close    ;
  oxygen_radiobutton.apply   = image_ok       ;

  oxygen_radiobutton.little  = interface_size_little_image ;
  oxygen_radiobutton.middle  = interface_size_middle_image ;
  oxygen_radiobutton.big     = interface_size_big_image    ;

  oxygen_radiobutton.min     = interface_min_image ;

  #ifdef G_OS_UNIX
  #ifndef MAC_INTEGRATION
  oxygen_radiobutton.set_as_default     = set_as_default_image     ;
  oxygen_radiobutton.reset_association  = reset_associations_image ;
  #endif
  #endif

  oxygen_radiobutton.theme_light = theme_light_image   ;
  oxygen_radiobutton.theme_dark  = theme_dark_image    ;

  g_signal_connect(G_OBJECT(radiobutton_icons_high_contrast), "clicked", G_CALLBACK(configure_high_contrast_radiobutton), &high_contrast_radiobutton) ;
  g_signal_connect(G_OBJECT(radiobutton_icons_oxygen),        "clicked", G_CALLBACK(configure_oxygen_radiobutton),        &oxygen_radiobutton       ) ;


  int little = -1 ;
  int middle =  0 ;
  int big    =  1 ;

  g_signal_connect(G_OBJECT(interface_size_radiobutton_little), "clicked",       G_CALLBACK(reconfigure_interface_size), &little) ;
  g_signal_connect(G_OBJECT(interface_size_radiobutton_middle), "clicked",       G_CALLBACK(reconfigure_interface_size), &middle) ;
  g_signal_connect(G_OBJECT(interface_size_radiobutton_big),    "clicked",       G_CALLBACK(reconfigure_interface_size), &big)    ;

  g_signal_connect_swapped(G_OBJECT(interface_min_toggle),       "toggled",      G_CALLBACK(gtk_menu_item_activate), GTK_MENU_ITEM(gui->menu->button_min_interface->menuitem) )    ;

  int off = 0 ;
  int all = 1 ;
  int one = 2 ;

  g_signal_connect(G_OBJECT(playing_settings_repeat_off),       "toggled",       G_CALLBACK(repeat_all_feature_set),      &off)    ;
  g_signal_connect(G_OBJECT(playing_settings_repeat_all),       "toggled",       G_CALLBACK(repeat_all_feature_set),      &all)    ;
  g_signal_connect(G_OBJECT(playing_settings_repeat_one),       "toggled",       G_CALLBACK(repeat_all_feature_set),      &one)    ;
  g_signal_connect(G_OBJECT(playing_settings_shuffle),          "toggled",       G_CALLBACK(shuffle_music),               NULL)    ;
  g_signal_connect(G_OBJECT(playing_settings_volume_scale),     "value-changed", G_CALLBACK(set_volume),                  NULL)    ;


  g_signal_connect(G_OBJECT(radiobutton_theme_light), "clicked", G_CALLBACK(configure_theme_light), NULL) ;
  g_signal_connect(G_OBJECT(radiobutton_theme_dark),  "clicked", G_CALLBACK(configure_theme_dark),  NULL) ;

  #ifdef G_OS_UNIX
  #ifndef MAC_INTEGRATION
  g_signal_connect(G_OBJECT(set_as_default_button),       "clicked", G_CALLBACK(set_as_default_music_player), NULL) ;
  g_signal_connect(G_OBJECT(reset_associations_button),   "clicked", G_CALLBACK(reset_associations),          NULL) ;
  #endif
  #endif

  gtk_widget_show_all(configure_dialog) ;



  int response = gtk_dialog_run(GTK_DIALOG(configure_dialog))  ;

  switch (response) {

    case GTK_RESPONSE_APPLY :

      {

        GKeyFile *conf_file = g_key_file_new() ;

        GError *error = NULL ;

        settings.is_repeat_all      = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(playing_settings_repeat_one)) ? 2 : gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(playing_settings_repeat_all)) ? 1 : 0 ;

        settings.is_shuffle         = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(playing_settings_shuffle))    ;
         
        settings.minimal_interface  = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(interface_min_toggle)) ;

        settings.volume = gtk_range_get_value( GTK_RANGE(playing_settings_volume_scale) ) ;

        #ifdef G_OS_UNIX
        #ifndef MAC_INTEGRATION
        settings.send_notification  = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(send_notifications_check_button)) ;
        #endif
        #endif

        set_repeat(settings.is_repeat_all) ;

        set_shuffle(settings.is_shuffle) ;

        // Set configuration settings to configuration file buffer.
        g_key_file_set_string(conf_file,   "Config",  "Buttons_Icons_Path",   settings.path_to_button_icons.c_str()) ;

        g_key_file_set_string(conf_file,   "Config",  "Menu_Icons_Path",      settings.path_to_menu_icons.c_str())   ;

        g_key_file_set_string(conf_file,   "Config",  "Music_Folder",         settings.path_to_music_folder.c_str())   ;

        g_key_file_set_boolean(conf_file,  "Config",  "Is_Oxygen",            settings.icon_set_oxygen) ;

        g_key_file_set_boolean(conf_file,  "Config",  "Shuffle",              settings.is_shuffle) ;

        g_key_file_set_integer(conf_file,  "Config",  "Repeat_all",           settings.is_repeat_all)  ;


        g_key_file_set_boolean(conf_file,  "Config",  "Theme_light",          settings.theme_light)  ;

        g_key_file_set_boolean(conf_file,   "Config", "Minimal_Interface",    settings.minimal_interface) ;

        g_key_file_set_boolean(conf_file,   "Config", "Notifications",        settings.send_notification) ;



        g_key_file_set_double(conf_file,   "Config",  "Volume",               settings.volume) ;

        g_key_file_set_uint64(conf_file,   "Config",  "Buttons_space",        settings.space_buttons) ;

        g_key_file_set_uint64(conf_file,   "Config",  "Image_Resizing",       settings.image_resized_size) ;

        g_key_file_set_string(conf_file,   "Config",  "Sized_Default_Image",  settings.path_to_default_image.c_str())   ;

        // Write to configuration file
        g_key_file_save_to_file(conf_file, PATH_TO_CONF_FILE, &error);

        if ( error != NULL ) {

          display_message_dialog("Error store configuration !", "Cannot store the configuration.") ;

          #ifdef DEBUG
          fprintf(stdout,"\n%s: Error store configuratiom settings.\n", g_get_prgname() )    ; fflush(stdout) ;
          #endif
        }
        else { // Success
          #ifdef DEBUG
          fprintf(stdout,"\n%s: Success store configuratiom settings.\n", g_get_prgname() )  ;
          #endif
        }

      }

      break ;

    case GTK_RESPONSE_CLOSE :
      // Do nothing.
      break ;
  }

  gtk_widget_destroy(configure_dialog) ;

  return ;

}
