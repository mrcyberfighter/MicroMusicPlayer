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

  /** Display a message dialog for informing the user with a message. **/

  GtkWidget *message_dialog = gtk_message_dialog_new(GTK_WINDOW(gui->window), GTK_DIALOG_MODAL, type, button_type, msg, NULL ) ;

  gtk_window_set_icon_from_file(GTK_WINDOW(message_dialog), PATH_TO_PRG_WIN_ICON, NULL) ;
  gtk_window_set_title(GTK_WINDOW(message_dialog), title) ;
  gtk_window_set_position(GTK_WINDOW(message_dialog), GTK_WIN_POS_CENTER_ALWAYS) ;
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

  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog), prgname.c_str()) ;

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


  gtk_window_set_icon_from_file(GTK_WINDOW(about_dialog), PATH_TO_PRG_WIN_ICON, NULL) ;
  gtk_window_set_position(GTK_WINDOW(about_dialog), GTK_WIN_POS_CENTER_ALWAYS) ;
  gtk_window_set_resizable(GTK_WINDOW(about_dialog), FALSE);
  gtk_widget_set_size_request(about_dialog, -1, -1) ;
  gtk_window_set_destroy_with_parent(GTK_WINDOW(about_dialog), TRUE) ;

  gtk_window_set_transient_for(GTK_WINDOW(about_dialog), GTK_WINDOW(gui->window)) ;

  g_signal_connect_swapped(G_OBJECT(about_dialog), "response", G_CALLBACK (gtk_widget_destroy), about_dialog) ;

  gtk_dialog_run(GTK_DIALOG(about_dialog) ) ;

}

void launch_readme_html(GtkWidget *widget, gpointer user_data) {

  /** Launch the README file to display it to the user through the GUI. **/

  GError *error = NULL ;

  char *readme_realpath = realpath(PATH_TO_README, NULL) ;

  gchar *readme_uri = g_filename_to_uri(readme_realpath, NULL, NULL);

  gtk_show_uri(NULL, readme_uri, GDK_CURRENT_TIME, &error);

  g_free(readme_uri) ;
  free(readme_realpath) ;

  #ifdef DEBUG
  // This call make crash the application, i don't know why. Not really needed, so we process only if DEBUG define.
  if (error != NULL) {

    string msg =  "Cannot display README:\n\n" ;

    msg += error->message ;

    display_message_dialog("Error README displaying !", msg.c_str() ) ;

  }
  #endif


  return ;

}

void get_folder_to_play(GtkWidget *widget, gpointer user_data) {

  /** User folder selection. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  GtkWidget *folder_chooser_dialog = gtk_file_chooser_dialog_new("Choose a folder contains music files to listen.", NULL, GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(folder_chooser_dialog),  current_folder.c_str() ) ;
  gtk_file_chooser_set_show_hidden(GTK_FILE_CHOOSER(folder_chooser_dialog), FALSE) ;
  gtk_file_chooser_set_create_folders(GTK_FILE_CHOOSER(folder_chooser_dialog), FALSE) ;
  gtk_file_chooser_set_use_preview_label(GTK_FILE_CHOOSER(folder_chooser_dialog), TRUE) ;
  gtk_file_chooser_set_local_only(GTK_FILE_CHOOSER(folder_chooser_dialog), TRUE) ;

  gtk_window_set_position(GTK_WINDOW(folder_chooser_dialog), GTK_WIN_POS_CENTER_ALWAYS) ;
  gtk_widget_set_size_request(folder_chooser_dialog,-1,-1) ;
  gtk_window_set_modal(GTK_WINDOW(folder_chooser_dialog), TRUE) ;
  gtk_window_set_destroy_with_parent(GTK_WINDOW(folder_chooser_dialog), TRUE) ;
  gtk_window_set_type_hint(GTK_WINDOW(folder_chooser_dialog), GDK_WINDOW_TYPE_HINT_DIALOG) ;
  gtk_window_set_transient_for(GTK_WINDOW(folder_chooser_dialog), GTK_WINDOW(gui->window)) ;


  gchar *folderpath = NULL ;  // Selected folder.

  gint result = gtk_dialog_run (GTK_DIALOG (folder_chooser_dialog));

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

  parse_folder(folderpath) ;

  gchar *dirname = g_path_get_dirname(folderpath) ;

  current_folder = dirname  ;

  g_free(dirname) ;

  #ifdef DEBUG
  fprintf(stdout,"%s current_folder: %s\n", __func__, current_folder.c_str() ) ;
  #endif

  g_free(folderpath) ;

}


void get_files_to_play(GtkWidget *widget, gpointer user_data) {

  /** User single file selection. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  GtkWidget *file_chooser_dialog = gtk_file_chooser_dialog_new("Choose music files to listen.", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser_dialog),  current_folder.c_str() ) ;
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



  gtk_window_set_position(GTK_WINDOW(file_chooser_dialog), GTK_WIN_POS_CENTER_ALWAYS) ;
  gtk_widget_set_size_request(file_chooser_dialog,-1,-1) ;
  gtk_window_set_modal(GTK_WINDOW(file_chooser_dialog), TRUE) ;
  gtk_window_set_destroy_with_parent(GTK_WINDOW(file_chooser_dialog), TRUE) ;
  gtk_window_set_type_hint(GTK_WINDOW(file_chooser_dialog), GDK_WINDOW_TYPE_HINT_DIALOG) ;
  gtk_window_set_transient_for(GTK_WINDOW(file_chooser_dialog), GTK_WINDOW(gui->window)) ;


  GSList *filepath_list = NULL ;

  gint result = gtk_dialog_run (GTK_DIALOG (file_chooser_dialog));

  switch (result) {
     
    case GTK_RESPONSE_CANCEL :
    
     gtk_widget_destroy(file_chooser_dialog);
     return ;

    case GTK_RESPONSE_ACCEPT :
  
      filepath_list = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(file_chooser_dialog)) ;
  
      gtk_widget_destroy(file_chooser_dialog) ;

      break ;
  }

  if (filepath_list != NULL) {

    gchar *file_dirname  = g_path_get_dirname((const gchar *) g_slist_nth_data(filepath_list, 0)) ;

    check_files(filepath_list) ;

    current_folder = file_dirname ;

    g_free(file_dirname) ;

    #ifdef DEBUG
    fprintf(stdout,"%s current_folder: %s\n", __func__, current_folder.c_str() ) ;
    #endif

    g_slist_free(filepath_list) ;

  }

}

void configure_program_dialog(GtkWidget *widget, gpointer user_data) {

  /** Program configuration dailog window. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  GtkWidget *configure_dialog = gtk_dialog_new() ;



  gtk_window_set_icon_from_file(GTK_WINDOW(configure_dialog), PATH_TO_PRG_WIN_ICON, NULL) ;
  gtk_window_set_title(GTK_WINDOW(configure_dialog), "Configure program") ;
  gtk_window_set_position(GTK_WINDOW(configure_dialog), GTK_WIN_POS_CENTER_ALWAYS) ;
  gtk_window_set_resizable(GTK_WINDOW(configure_dialog), FALSE);
  gtk_widget_set_size_request(configure_dialog,-1,-1) ;
  gtk_window_set_modal(GTK_WINDOW(configure_dialog), FALSE) ;
  gtk_window_set_destroy_with_parent(GTK_WINDOW(configure_dialog), TRUE) ;
  gtk_window_set_decorated(GTK_WINDOW(configure_dialog), TRUE) ;

  gtk_window_set_type_hint(GTK_WINDOW(configure_dialog), GDK_WINDOW_TYPE_HINT_NORMAL) ;
  gtk_window_set_transient_for(GTK_WINDOW(configure_dialog), GTK_WINDOW(gui->window)) ;

  gtk_container_set_border_width(GTK_CONTAINER(configure_dialog), 12) ;


  #define DIALOG_DEFAULT_SPACE 12


  /** ***** [START] Icon set choice [START] ***** **/

  GtkWidget *icon_set_choice_frame = gtk_frame_new(" Icon set ") ;


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

    image_icons_high_contrast = gtk_image_new_from_file( PATH_TO_HIGH_CONTRAST_BUTTON_ICONS  "face-angry.png")     ;

    image_icons_oxygen        = gtk_image_new_from_file( PATH_TO_OXYGEN_BUTTON_ICONS         "face-smile-big.png") ;

  }
  else {

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton_icons_high_contrast), TRUE) ;

    image_icons_high_contrast = gtk_image_new_from_file( PATH_TO_HIGH_CONTRAST_BUTTON_ICONS  "face-smile-big.png") ;

    image_icons_oxygen        = gtk_image_new_from_file( PATH_TO_OXYGEN_BUTTON_ICONS         "face-angry.png")     ;

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


  GtkWidget *playing_settings_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(playing_settings_vbox), DIALOG_DEFAULT_SPACE) ;



  GtkWidget *playing_settings_repeat_all = gtk_check_button_new_with_label(" Repeat all mode. ") ;

  gtk_widget_set_tooltip_markup(playing_settings_repeat_all, "Enable the <b>repeat all</b> feature.\nThis will update the player settings.\nBut you must press the <b>Apply</b> button to store your configuration.") ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(playing_settings_repeat_all), is_repeat_all) ;



  GtkWidget *playing_settings_shuffle = gtk_check_button_new_with_label(" Shuffle mode. ") ;

  gtk_widget_set_tooltip_markup(playing_settings_shuffle, "Enable the <b>shuffle</b> feature.\nThis will update the player settings.\nBut you must press the <b>Apply</b> button to store your configuration.") ;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(playing_settings_shuffle), is_shuffle ) ;

  GtkWidget *playing_settings_volume_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;



  GtkWidget *playing_settings_volume_label_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  GtkWidget *playing_settings_volume_image      = gtk_image_new_from_file( (settings.path_to_button_icons + "audio-volume-medium.png").c_str() ) ;

  GtkWidget *playing_settings_volume_label      = gtk_label_new(" Default Volume:") ;

  gtk_box_pack_start(GTK_BOX(playing_settings_volume_label_hbox), playing_settings_volume_image, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(playing_settings_volume_label_hbox), playing_settings_volume_label, FALSE, FALSE, 0) ;


  GtkWidget *playing_settings_volume_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 100.0, 1.0) ;



  gtk_widget_set_tooltip_markup(playing_settings_volume_scale, "Set the <b>default player volume</b> at start.\nThis will <b>not</b> update the player settings.\nYou must press the <b>Apply</b> button to store your configuration.") ;

  gtk_range_set_value(GTK_RANGE(playing_settings_volume_scale), settings.volume) ;

  gtk_scale_set_draw_value(GTK_SCALE(playing_settings_volume_scale), TRUE) ;
  gtk_scale_set_has_origin(GTK_SCALE(playing_settings_volume_scale), TRUE) ;

  gtk_scale_set_value_pos(GTK_SCALE(playing_settings_volume_scale), GTK_POS_TOP) ;

  gtk_scale_add_mark(GTK_SCALE(playing_settings_volume_scale), 50.0, GTK_POS_TOP, NULL) ;



  gtk_box_pack_start(GTK_BOX(playing_settings_volume_hbox), playing_settings_volume_label_hbox, FALSE,  FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(playing_settings_volume_hbox), playing_settings_volume_scale,      TRUE,   TRUE,  0) ;



  gtk_box_pack_start(GTK_BOX(playing_settings_vbox), playing_settings_repeat_all,               FALSE, FALSE, 0)   ;
  gtk_box_pack_start(GTK_BOX(playing_settings_vbox), playing_settings_shuffle,                  FALSE, FALSE, 0)   ;
  gtk_box_pack_start(GTK_BOX(playing_settings_vbox), playing_settings_volume_hbox,              FALSE, FALSE, 0)   ;

  gtk_container_add(GTK_CONTAINER(playing_settings_frame), playing_settings_vbox) ;

  /** ***** [END] Playing settings [END] ***** **/



  /** ***** [START] Interface size setting [START] ***** **/

  GtkWidget *interface_size_frame = gtk_frame_new(" Interface size ") ;

  GtkWidget *interface_size_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(interface_size_hbox), DIALOG_DEFAULT_SPACE) ;

  GtkWidget *interface_size_radiobutton_little = gtk_radio_button_new_with_label(NULL, " Little") ;
  GtkWidget *interface_size_radiobutton_middle = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(interface_size_radiobutton_little)), " Medium") ;
  GtkWidget *interface_size_radiobutton_big    = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(interface_size_radiobutton_little)), "  Big  ") ;

  GtkWidget *interface_size_little_image       = gtk_image_new_from_file((settings.path_to_button_icons + "interface-little.png").c_str() ) ;
  GtkWidget *interface_size_middle_image       = gtk_image_new_from_file((settings.path_to_button_icons + "interface-middle.png").c_str() ) ;
  GtkWidget *interface_size_big_image          = gtk_image_new_from_file((settings.path_to_button_icons + "interface-big.png").c_str()    ) ;

  gtk_widget_set_tooltip_markup(interface_size_radiobutton_little, "Set the <b>interface size</b> on <b>little</b>.\nThis will update the interface.\nBut you must press the <b>Apply</b> button to store your configuration.") ;
  gtk_widget_set_tooltip_markup(interface_size_radiobutton_middle, "Set the <b>interface size</b> on <b>middle</b>.\nThis will update the interface.\nBut you must press the <b>Apply</b> button to store your configuration.") ;
  gtk_widget_set_tooltip_markup(interface_size_radiobutton_big,    "Set the <b>interface size</b> on <b>big</b>.\nThis will update the interface.\nBut you must press the <b>Apply</b> button to store your configuration.")    ;

  gtk_button_set_image(GTK_BUTTON(interface_size_radiobutton_little), interface_size_little_image) ;
  gtk_button_set_image(GTK_BUTTON(interface_size_radiobutton_middle), interface_size_middle_image) ;
  gtk_button_set_image(GTK_BUTTON(interface_size_radiobutton_big),    interface_size_big_image   ) ;

  gtk_button_set_always_show_image(GTK_BUTTON(interface_size_radiobutton_little), TRUE) ;
  gtk_button_set_always_show_image(GTK_BUTTON(interface_size_radiobutton_middle), TRUE) ;
  gtk_button_set_always_show_image(GTK_BUTTON(interface_size_radiobutton_big),    TRUE) ;

  gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(interface_size_radiobutton_little), FALSE) ;
  gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(interface_size_radiobutton_middle), FALSE) ;
  gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(interface_size_radiobutton_big),    FALSE) ;


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


  gtk_box_pack_start(GTK_BOX(interface_size_hbox), interface_size_radiobutton_little, TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(interface_size_hbox), interface_size_radiobutton_middle, TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(interface_size_hbox), interface_size_radiobutton_big,    TRUE, TRUE, 0) ;

  gtk_box_set_homogeneous(GTK_BOX(interface_size_hbox), TRUE) ;

  gtk_box_set_spacing(GTK_BOX(interface_size_hbox), DIALOG_DEFAULT_SPACE) ;

  gtk_container_add(GTK_CONTAINER(interface_size_frame), interface_size_hbox) ;

  /** ***** [END] Interface size setting [END] ***** **/



  /** ***** [START] Music folder setting [START] ***** **/

  GtkWidget *folder_selecting_frame = gtk_frame_new(" Music folder ") ;

  GtkWidget *folder_selecting_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gtk_container_set_border_width(GTK_CONTAINER(folder_selecting_box), DIALOG_DEFAULT_SPACE) ;


  GtkWidget *folder_selecting_button = gtk_file_chooser_button_new("Set the Music folder to open per default.", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER) ;

  gtk_widget_set_tooltip_markup(folder_selecting_button, "Set the folder to open per default: your <b>default music folder</b>.\n<i>The default folder from the folder selector</i>.\nSet it simply to your <b>Music folder</b>.\nChanges are immediatly applied.\nBut you must press the <b>Apply</b> button to store your configuration.") ;

  gtk_file_chooser_button_set_title(GTK_FILE_CHOOSER_BUTTON(folder_selecting_button), "Set the Music folder to open per default.") ;

  const char *user_music_folder = g_get_user_special_dir(G_USER_DIRECTORY_MUSIC) ;

  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(folder_selecting_button), (g_file_test(settings.path_to_music_folder.c_str(), G_FILE_TEST_IS_DIR)) ? settings.path_to_music_folder.c_str() : (user_music_folder != NULL) ? user_music_folder : g_get_home_dir()  ) ;


  gtk_box_pack_start(GTK_BOX(folder_selecting_box), folder_selecting_button,  TRUE, TRUE, 0)   ;

  gtk_container_add(GTK_CONTAINER(folder_selecting_frame), folder_selecting_box) ;

  /** ***** [END] Music folder setting [END] ***** **/



  /** ***** [START] Dialog main content box [START] ***** **/

  GtkWidget *content_area = gtk_dialog_get_content_area( GTK_DIALOG(configure_dialog) ) ;

  gtk_box_pack_start(GTK_BOX(content_area), icon_set_choice_frame,  FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(content_area), playing_settings_frame, FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(content_area), interface_size_frame,   FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(content_area), folder_selecting_frame, FALSE, FALSE, 0) ;

  gtk_box_set_spacing(GTK_BOX(content_area), DIALOG_DEFAULT_SPACE) ;

  /** ***** [END] Dialog main content box [END] ***** **/



  /** ***** [START] Dialog action buttons [START] ***** **/

  GtkWidget *button_close = gtk_button_new_with_label("Close") ; // gtk_dialog_add_button(GTK_DIALOG(configure_dialog), "Cancel", GTK_RESPONSE_CANCEL) ;

  GtkWidget *image_close  = gtk_image_new_from_file((settings.path_to_button_icons + "dialog-close.png").c_str()) ;

  gtk_widget_set_tooltip_markup(button_close, "<b>Close</b> the configuration window and don't store any setting.") ;

  gtk_button_set_image(GTK_BUTTON(button_close), image_close) ;

  gtk_button_set_always_show_image(GTK_BUTTON(button_close), TRUE) ;


  GtkWidget *button_ok = gtk_button_new_with_label("Apply") ; // gtk_dialog_add_button(GTK_DIALOG(configure_dialog), "Apply", GTK_RESPONSE_APPLY) ;

  GtkWidget *image_ok  = gtk_image_new_from_file((settings.path_to_button_icons + "dialog-ok.png").c_str()) ;

  gtk_widget_set_tooltip_markup(button_ok, "<b>Register</b> all the settings as <i>your default configuration</i> at start.") ;

  gtk_button_set_image(GTK_BUTTON(button_ok), image_ok) ;

  gtk_button_set_always_show_image(GTK_BUTTON(button_ok), TRUE) ;


  gtk_dialog_add_action_widget(GTK_DIALOG(configure_dialog), button_close, GTK_RESPONSE_CLOSE) ;

  gtk_dialog_add_action_widget(GTK_DIALOG(configure_dialog), button_ok,     GTK_RESPONSE_APPLY)  ;

  GtkWidget *action_area = gtk_dialog_get_action_area(GTK_DIALOG(configure_dialog)) ;

  gtk_container_set_border_width(GTK_CONTAINER(action_area), 0) ;

  gtk_button_box_set_layout(GTK_BUTTON_BOX(action_area), GTK_BUTTONBOX_EDGE) ;

  /** ***** [END] Dialog action buttons [END] ***** **/



  Radio_Config high_contrast_radiobutton ;

  high_contrast_radiobutton.button  = radiobutton_icons_high_contrast ;
  high_contrast_radiobutton.image   = image_icons_high_contrast       ;

  high_contrast_radiobutton.volume  = playing_settings_volume_image       ;
  high_contrast_radiobutton.cancel  = image_close    ;
  high_contrast_radiobutton.apply   = image_ok       ;

  high_contrast_radiobutton.little  = interface_size_little_image ;
  high_contrast_radiobutton.middle  = interface_size_middle_image ;
  high_contrast_radiobutton.big     = interface_size_big_image    ;


  Radio_Config oxygen_radiobutton ;

  oxygen_radiobutton.button  = radiobutton_icons_oxygen ;
  oxygen_radiobutton.image   = image_icons_oxygen       ;

  oxygen_radiobutton.volume  = playing_settings_volume_image       ;
  oxygen_radiobutton.cancel  = image_close    ;
  oxygen_radiobutton.apply   = image_ok       ;

  oxygen_radiobutton.little  = interface_size_little_image ;
  oxygen_radiobutton.middle  = interface_size_middle_image ;
  oxygen_radiobutton.big     = interface_size_big_image    ;

  g_signal_connect(G_OBJECT(radiobutton_icons_high_contrast), "clicked", G_CALLBACK(configure_high_contrast_radiobutton), &high_contrast_radiobutton) ;
  g_signal_connect(G_OBJECT(radiobutton_icons_oxygen),        "clicked", G_CALLBACK(configure_oxygen_radiobutton),        &oxygen_radiobutton       ) ;


  int little = -1 ;
  int middle =  0 ;
  int big    =  1 ;

  g_signal_connect(G_OBJECT(interface_size_radiobutton_little), "clicked",       G_CALLBACK(reconfigure_interface_size), &little) ;
  g_signal_connect(G_OBJECT(interface_size_radiobutton_middle), "clicked",       G_CALLBACK(reconfigure_interface_size), &middle) ;
  g_signal_connect(G_OBJECT(interface_size_radiobutton_big),    "clicked",       G_CALLBACK(reconfigure_interface_size), &big)    ;


  g_signal_connect(G_OBJECT(playing_settings_repeat_all),       "toggled",       G_CALLBACK(repeat_all_feature_set),     NULL)    ;
  g_signal_connect(G_OBJECT(playing_settings_shuffle),          "toggled",       G_CALLBACK(shuffle_feature_set),        NULL)    ;
  g_signal_connect(G_OBJECT(playing_settings_volume_scale),     "value-changed", G_CALLBACK(get_volume),                 NULL)    ;
  g_signal_connect(G_OBJECT(folder_selecting_button),           "file-set",      G_CALLBACK(set_default_folder),         NULL)    ;


  gtk_widget_show_all(configure_dialog) ;



  int response = gtk_dialog_run(GTK_DIALOG(configure_dialog))  ;

  switch (response) {

    case GTK_RESPONSE_APPLY :

      {

        GKeyFile *conf_file = g_key_file_new() ;

        GError *error = NULL ;

        settings.is_repeat_all = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(playing_settings_repeat_all)) ;

        settings.is_shuffle       = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(playing_settings_shuffle))    ;



        // Set configuration settings to configuration file buffer.
        g_key_file_set_string(conf_file,   "Config",  "Buttons_Icons_Path",   settings.path_to_button_icons.c_str()) ;

        g_key_file_set_string(conf_file,   "Config",  "Menu_Icons_Path",      settings.path_to_menu_icons.c_str())   ;

        g_key_file_set_string(conf_file,   "Config",  "Music_Folder",         settings.path_to_music_folder.c_str())   ;

        g_key_file_set_boolean(conf_file,  "Config",  "Is_Oxygen",            settings.icon_set_oxygen) ;
        g_key_file_set_boolean(conf_file,  "Config",  "Repeat_all",           settings.is_repeat_all)  ;
        g_key_file_set_boolean(conf_file,  "Config",  "Shuffle",              settings.is_shuffle) ;

        g_key_file_set_double(conf_file,   "Config",  "Volume",               settings.volume) ;

        g_key_file_set_uint64(conf_file,   "Config",  "Buttons_space",        settings.space_buttons) ;

        g_key_file_set_uint64(conf_file,   "Config",  "Display_Size",         settings.display_size) ;

        g_key_file_set_uint64(conf_file,   "Config",  "Image_Resizing",       settings.image_resized_size) ;

        g_key_file_set_string(conf_file,   "Config",  "Sized_Default_Image",  settings.path_to_default_image.c_str())   ;

        // Write to configuration file
        g_key_file_save_to_file(conf_file, PATH_TO_CONF_FILE, &error);

        // Setting global variables.
        cover_image    = settings.path_to_default_image ;
        current_folder = settings.path_to_music_folder ;

        if ( error != NULL ) {

          display_message_dialog("Error store configuration !", "Cannot store the configuration.") ;

          #ifdef DEBUG
          fprintf(stdout,"\n%s: Error store configuratiom settings.\n", prgname.c_str() )    ; fflush(stdout) ;
          #endif
        }
        else { // Success
          #ifdef DEBUG
          fprintf(stdout,"\n%s: Success store configuratiom settings.\n", prgname.c_str() )  ;
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