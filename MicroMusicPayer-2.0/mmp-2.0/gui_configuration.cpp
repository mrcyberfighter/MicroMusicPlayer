/** ***********************************************************************************
  *                                                                                   *    
  * Micro Music Player a very simple play a folder or a file music player.            *
  * Copyright (C) 2015  Brüggemann Eddie.                                             *
  *                                                                                   *
  * This file is part of Micro Music Player.                                          *
  * Micro Music Player is free software: you can redistribute it and/or modify        *
  * it under the terms of the GNU General Public License as published by              *
  * the Free Software Foundation, either version 3 of the License, or                 *
  * (at your option) any later version.                                               *
  *                                                                                   *
  * Micro Music Player is distributed in the hope that it will be useful,             *
  * but WITHOUT ANY WARRANTY; without even the implied warranty of                    *
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                      *
  * GNU General Public License for more details.                                      *
  *                                                                                   *
  * You should have received a copy of the GNU General Public License                 *
  * along with Micro Music Player. If not, see <http://www.gnu.org/licenses/>         *
  *                                                                                   *
  ************************************************************************************/

void reset_image_widget(GtkWidget *image, const char *filepath) {

  /** Reset a image file. **/

  gtk_image_clear(GTK_IMAGE(image)) ;

  gtk_image_set_from_file(GTK_IMAGE(image), filepath ) ;

}

void reconfigure_icon(GtkWidget *image, string filename, const bool is_button) {

  gtk_image_clear(GTK_IMAGE(image)) ;

  if (is_button) {
    gtk_image_set_from_file(GTK_IMAGE(image), (settings.path_to_button_icons + filename).c_str() ) ;
  }
  else {
    gtk_image_set_from_file(GTK_IMAGE(image), (settings.path_to_menu_icons   + filename).c_str() ) ;
  }

}

void reconfigure_interface_icons() {

  /** Buttons **/

  // Controls:
  reconfigure_icon(gui->button_prev_image,    "media-skip-backward.png",    true) ;
  reconfigure_icon(gui->button_play_image,    "media-playback-start.png",   true) ;
  reconfigure_icon(gui->button_pause_image,   "media-playback-pause.png",   true) ;
  reconfigure_icon(gui->button_next_image,    "media-skip-forward.png",     true) ;
  reconfigure_icon(gui->button_stop_image,    "media-playback-stop.png",    true) ;
  // Play modes:
  reconfigure_icon(gui->button_repeat_image,  "media-playlist-repeat.png",  true) ;
  reconfigure_icon(gui->button_shuffle_image, "media-playlist-shuffle.png", true) ;
  // Settings:
  reconfigure_icon(gui->button_volume_image,   "audio-volume-medium.png",   true) ;
  // Volume button icons:
  reconfigure_icon(gui->button_volume_plus_image,        "audio-volume-high.png",       false) ;
  reconfigure_icon(gui->button_volume_minus_image,       "audio-volume-low.png",        false) ;


  /** Menu **/

  // Menubutton:
  reconfigure_icon(gui->menu->menubutton_actions->image, "multimedia-player.png",       false) ;
  // Menu items:
  // Controls:
  reconfigure_icon(gui->menu->button_play->image,        "media-playback-start.png",    false) ;
  reconfigure_icon(gui->menu->button_stop->image,        "media-playback-stop.png",     false) ;
  reconfigure_icon(gui->menu->button_next->image,        "media-skip-forward.png",      false) ;
  reconfigure_icon(gui->menu->button_prev->image,        "media-skip-backward.png",     false) ;
  // Play Modes:
  reconfigure_icon(gui->menu->button_repeat->image,      "media-playlist-repeat.png",   false) ;
  reconfigure_icon(gui->menu->button_shuffle->image,     "media-playlist-shuffle.png",  false) ;
  // Settings:
  reconfigure_icon(gui->menu->button_config->image,      "preferences-system.png",      false) ;
  // Play a file:
  reconfigure_icon(gui->menu->button_file->image,        "folder-music.png",            false) ;
  //Show playlist:
  reconfigure_icon(gui->menu->show_playlist->image,      "applications-multimedia.png", false) ;

  // info menu:
  reconfigure_icon(gui->menu->menubutton_info->image,    "user-info.png",               false) ;
  reconfigure_icon(gui->menu->button_readme->image,      "document-readme.png",         false) ;
  reconfigure_icon(gui->menu->button_about->image,       "dialog-about.png",            false) ;

  // Quit application:
  reconfigure_icon(gui->menu->button_quit->image,        "system-shutdown.png",         false) ;

  return ;    

}


void configure_high_contrast_radiobutton(GtkWidget *widget, Radio_Config *user_data) {

  if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON(user_data->button) ) ) {

    gtk_image_clear( GTK_IMAGE(user_data->image) ) ;

    gtk_image_set_from_file(GTK_IMAGE(user_data->image), PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "face-smile-big.png" ) ;

    reset_image_widget(user_data->volume, PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "audio-volume-medium.png" ) ;
    reset_image_widget(user_data->apply,  PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "dialog-ok.png"           ) ;
    reset_image_widget(user_data->cancel, PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "dialog-close.png"        ) ;

    reset_image_widget(user_data->little, PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "interface-little.png"    ) ;
    reset_image_widget(user_data->middle, PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "interface-middle.png"    ) ;
    reset_image_widget(user_data->big,    PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "interface-big.png"       ) ;

    settings.icon_set_oxygen = false ;

    settings.path_to_button_icons =  PATH_TO_HIGH_CONTRAST_BUTTON_ICONS ;
    settings.path_to_menu_icons   =  PATH_TO_HIGH_CONTRAST_MENU_ICONS  ;

    reconfigure_interface_icons() ;

  }
  else {

    gtk_image_clear( GTK_IMAGE(user_data->image) ) ;

    gtk_image_set_from_file(GTK_IMAGE(user_data->image), PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "face-angry.png" ) ;

    settings.icon_set_oxygen = true ;

  }

}

void configure_oxygen_radiobutton(GtkWidget *widget, Radio_Config *user_data) {

  if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON(user_data->button) ) ) {

    gtk_image_clear( GTK_IMAGE(user_data->image) ) ;

    gtk_image_set_from_file(GTK_IMAGE(user_data->image), PATH_TO_OXYGEN_BUTTON_ICONS "face-smile-big.png" ) ;

    reset_image_widget(user_data->volume, PATH_TO_OXYGEN_BUTTON_ICONS "audio-volume-medium.png" ) ;
    reset_image_widget(user_data->apply,  PATH_TO_OXYGEN_BUTTON_ICONS "dialog-ok.png"           ) ;
    reset_image_widget(user_data->cancel, PATH_TO_OXYGEN_BUTTON_ICONS "dialog-close.png"        ) ;

    reset_image_widget(user_data->little, PATH_TO_OXYGEN_BUTTON_ICONS "interface-little.png"    ) ;
    reset_image_widget(user_data->middle, PATH_TO_OXYGEN_BUTTON_ICONS "interface-middle.png"    ) ;
    reset_image_widget(user_data->big,    PATH_TO_OXYGEN_BUTTON_ICONS "interface-big.png"       ) ;

    settings.icon_set_oxygen = true ;

    settings.path_to_button_icons =  PATH_TO_OXYGEN_BUTTON_ICONS ;
    settings.path_to_menu_icons   =  PATH_TO_OXYGEN_MENU_ICONS  ;

    reconfigure_interface_icons() ;


  }
  else {

    gtk_image_clear( GTK_IMAGE(user_data->image) ) ;

    gtk_image_set_from_file(GTK_IMAGE(user_data->image), PATH_TO_OXYGEN_BUTTON_ICONS "face-angry.png" ) ;

    settings.icon_set_oxygen = false ;

  }

}

void repeat_all_feature_set(GtkToggleButton *togglebutton, gpointer user_data) {

  settings.is_repeat_all = gtk_toggle_button_get_active(togglebutton) ;

  set_repeat(gtk_toggle_button_get_active(togglebutton)) ;

  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: Repeat all function %s\n", prgname.c_str(),  ((is_repeat_all) ? "on" : "off") ) ; fflush(stdout) ;
  #endif
  #endif

  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_repeat->menuitem), is_repeat_all) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->button_repeat), is_repeat_all) ;

}

void shuffle_feature_set(GtkToggleButton *togglebutton, gpointer user_data) {

  settings.is_repeat_all = gtk_toggle_button_get_active(togglebutton) ;

  set_shuffle(gtk_toggle_button_get_active(togglebutton)) ;

  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: Shuffle function %s\n", prgname.c_str(),  (is_shuffle) ? "on" : "off" ) ; fflush(stdout) ;
  #endif
  #endif

  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_shuffle->menuitem), is_shuffle) ;
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->button_shuffle), is_shuffle) ;

}

void get_volume(GtkRange *range, gpointer user_data) {

  settings.volume = gtk_range_get_value(GTK_RANGE(range)) ;

}



void reconfigure_interface_size(GtkWidget *widget, int *user_data) {

  bool default_image = (cover_image == settings.path_to_default_image) ;

  switch ((*user_data)) {

    case -1 : // Little interface choice.

      settings.space_buttons = SPACE_BUTTONS_LITTLE ;

      settings.display_size = DISPLAY_SIZE_LITTLE ;

      settings.image_resized_size = IMAGE_RESIZED_SIZE_LITTLE ;

      settings.path_to_default_image = MAIN_PATH PATH_TO_IMAGE "Micro_Music_Player_256.png" ;

      break ;

    case 0  : // Middle interface choice.

      settings.space_buttons = SPACE_BUTTONS_MIDDLE ;

      settings.display_size = DISPLAY_SIZE_MIDDLE ;

      settings.image_resized_size = IMAGE_RESIZED_SIZE_MIDDLE ;

      settings.path_to_default_image = MAIN_PATH PATH_TO_IMAGE "Micro_Music_Player_320.png" ;  // ???

      break ;

    case 1  : // Big interface choice.

      settings.space_buttons = SPACE_BUTTONS_BIG ;

      settings.display_size = DISPLAY_SIZE_BIG ;

      settings.image_resized_size = IMAGE_RESIZED_SIZE_BIG ;

      settings.path_to_default_image = MAIN_PATH PATH_TO_IMAGE "Micro_Music_Player_384.png" ;  // ???

      break ;

   default :

     return ;

  }



  gtk_widget_set_size_request(gui->image_container, settings.display_size, settings.display_size ) ;


  // By size change we must reconfigre image if default or not !
  g_object_ref(gui->image_widget) ;

  gtk_container_remove(GTK_CONTAINER(gui->image_container), gui->image_widget) ;

  gtk_image_clear(GTK_IMAGE(gui->image_widget)) ;

  if (default_image) {

    cover_image = settings.path_to_default_image ;

    gtk_image_set_from_file(GTK_IMAGE(gui->image_widget), cover_image.c_str() ) ;

    gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, (settings.display_size - settings.image_resized_size) / 2, (settings.display_size - settings.image_resized_size)  / 2 ) ;

  }
  else {

    //cover_image stay the same.

    //if ( image_cover_frame != NULL ) {

    GError *error = NULL ;

    auto new_size = resizer.resizer(image_cover_frame, settings.image_resized_size, settings.image_resized_size, false) ;
       
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(image_cover_frame.c_str(), &error);
   
    if (error != NULL) {
      cover_image = settings.path_to_default_image ;

      gtk_image_set_from_file(GTK_IMAGE(gui->image_widget), settings.path_to_default_image.c_str() ) ;

      gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, (settings.display_size - settings.image_resized_size) / 2, (settings.display_size - settings.image_resized_size)  / 2 ) ;
   
    }
    else { 
     
      GdkPixbuf *pixbuf_scaled = gdk_pixbuf_scale_simple(pixbuf,
                                                         new_size.first,
                                                         new_size.second,
                                                         GDK_INTERP_NEAREST);
     
      gtk_image_set_from_pixbuf(GTK_IMAGE(gui->image_widget), pixbuf_scaled) ;

      gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, (settings.display_size-new_size.first)/2 ,  (settings.display_size-new_size.second) /2 ) ;
   
    }

  }

  gtk_box_set_spacing(GTK_BOX(gui->controls_buttonbox), settings.space_buttons) ;

}

void set_default_folder(GtkFileChooserButton *chooser, gpointer user_data) {

  fprintf(stdout,"%s(...) change folder to:\n%s\n", __func__, gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(chooser)) ) ;

  fflush(stdout) ;

  if (! g_file_test( gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(chooser)), G_FILE_TEST_IS_DIR) ) {

    return ;
  }


  current_folder.clear() ;
  current_folder.shrink_to_fit() ;

  current_folder = settings.path_to_music_folder = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(chooser)) ;

}

