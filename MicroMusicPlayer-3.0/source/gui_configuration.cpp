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

#include "gui_configuration.h"


static void reset_image_widget(GtkWidget *image, const char *filepath) {

  /** Reset a image file. **/

  gtk_image_clear(GTK_IMAGE(image)) ;

  gtk_image_set_from_file(GTK_IMAGE(image), filepath ) ;

}

static void reconfigure_icon(GtkWidget *image, string filename, const bool is_button) {

  gtk_image_clear(GTK_IMAGE(image)) ;

  if (is_button) {

    gtk_image_set_from_file(GTK_IMAGE(image), (settings.path_to_button_icons + filename).c_str() ) ;
  }
  else {

    gtk_image_set_from_file(GTK_IMAGE(image), (settings.path_to_menu_icons   + filename).c_str() ) ;

  }

}

static void reconfigure_interface_icons(void) {

  /** Buttons **/

  // Controls:
  reconfigure_icon(gui->button_prev_image,    "media-skip-backward.png",    true) ;
  reconfigure_icon(gui->button_play_image,    "media-playback-start.png",   true) ;
  reconfigure_icon(gui->button_pause_image,   "media-playback-pause.png",   true) ;
  reconfigure_icon(gui->button_next_image,    "media-skip-forward.png",     true) ;
  reconfigure_icon(gui->button_stop_image,    "media-playback-stop.png",    true) ;
  // Play modes:
  reconfigure_icon(gui->button_repeat_image,  (is_repeat_all == 0) ?  "user-offline.png" : (is_repeat_all == 1) ? "media-playlist-repeat.png" : "media-playlist-repeat-song.png" ,  true) ;
  reconfigure_icon(gui->button_shuffle_image, (is_shuffle) ? "media-playlist-shuffle.png" : "user-offline.png",  true) ;
  // Settings:
  reconfigure_icon(gui->button_volume_image,   "audio-volume-medium.png",   true) ;



  /** Menu **/

  // Menubutton:
  reconfigure_icon(gui->menu->menubutton_actions->image,  "multimedia-player.png",      false) ;
  reconfigure_icon(gui->menu->menubutton_files->image,    "system-file-manager.png",    false) ;
  reconfigure_icon(gui->menu->menubutton_config->image,   "main-configuration.png",     false) ;
  reconfigure_icon(gui->menu->menubutton_config->image,   "main-configuration.png",     false) ;
  reconfigure_icon(gui->menu->menubutton_info->image,     "user-info.png",              false) ;

  // Menu items:

  // Controls:
  reconfigure_icon(gui->menu->button_play->image,         "media-playback-start.png",    false) ;
  reconfigure_icon(gui->menu->button_stop->image,         "media-playback-stop.png",     false) ;
  reconfigure_icon(gui->menu->button_next->image,         "media-skip-forward.png",      false) ;
  reconfigure_icon(gui->menu->button_prev->image,         "media-skip-backward.png",     false) ;

  // Volume:
  reconfigure_icon(gui->menu->button_incr_vol->image,     "audio-volume-high.png",       false) ;
  reconfigure_icon(gui->menu->button_decr_vol->image,     "audio-volume-low.png",        false) ;

  // Play Modes:
  reconfigure_icon(gui->menu->button_repeat_all->image,     "media-playlist-repeat.png",        false) ;
  reconfigure_icon(gui->menu->button_repeat_one->image,     "media-playlist-repeat-song.png" ,  false) ;
  reconfigure_icon(gui->menu->button_repeat_off->image,     "user-offline.png",                 false) ;
  reconfigure_icon(gui->menu->button_shuffle->image,        (is_shuffle) ? "media-playlist-shuffle.png" : "user-offline.png",  false) ;

  // Play a file:
  reconfigure_icon(gui->menu->button_file->image,           "folder-music.png",             false) ;

  #ifdef G_OS_UNIX
  // Play a folder:
  reconfigure_icon(gui->menu->button_folder->image,         "folder-sound.png",             false) ;
  #endif

  // Recent folders:
  reconfigure_icon(gui->menu->button_recent->image,         "document-open-recent.png",     false) ;

  // Settings:
  reconfigure_icon(gui->menu->button_config->image,         "preferences-system.png",       false) ;

  reconfigure_icon(gui->menu->button_theme_light->image,   "preferences-desktop-display.png",  false) ;
  reconfigure_icon(gui->menu->button_theme_dark->image,    "preferences-desktop-display.png",  false) ;

  // Minimal interface:
  reconfigure_icon(gui->menu->button_min_interface->image,  "window-minimize.png",          false) ;

  // Volume button icons:
  reconfigure_icon(gui->button_volume_plus_image,         "audio-volume-high.png",          false) ;
  reconfigure_icon(gui->button_volume_minus_image,        "audio-volume-low.png",           false) ;

  //Show playlist:
  reconfigure_icon(gui->menu->show_playlist->image,       "applications-multimedia.png",    false) ;

  // info menu:
  reconfigure_icon(gui->menu->button_readme->image,      "document-readme.png",             false) ;
  reconfigure_icon(gui->menu->button_about->image,       "dialog-about.png",                false) ;

  // Quit application:
  reconfigure_icon(gui->menu->button_quit->image,        "system-shutdown.png",             false) ;

  return ;

}

void switch_minimal_normal_interface(GtkWidget *widget, gpointer user_data) {

  if ( gtk_widget_is_visible(gui->image_container_hbox) ) {

    settings.minimal_interface = true ;

    gtk_widget_hide(gui->image_container_hbox) ;

  }
  else {

    settings.minimal_interface = false ;

    gtk_widget_show(gui->image_container_hbox) ;

  }

  return ;
}

void configure_high_contrast_radiobutton(GtkWidget *widget, Radio_Config *user_data) {

  if (user_data != NULL) {

    // This mean that the call comes from the configuration window.

    if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON(user_data->button) ) ) {

      gtk_image_clear( GTK_IMAGE(user_data->image) ) ;


      #ifdef G_OS_WIN32
      gchar *image_smile = g_strdup_printf("%s%s", PATH_TO_HIGH_CONTRAST_BUTTON_ICONS, "face-smile-big.png" ) ;

      gchar *image_volume_medium = g_strdup_printf("%s%s", PATH_TO_HIGH_CONTRAST_BUTTON_ICONS, "audio-volume-medium.png" ) ;
      gchar *image_volume_ok = g_strdup_printf("%s%s", PATH_TO_HIGH_CONTRAST_BUTTON_ICONS, "dialog-ok.png" ) ;
      gchar *image_volume_close = g_strdup_printf("%s%s", PATH_TO_HIGH_CONTRAST_BUTTON_ICONS, "dialog-close.png" ) ;

      gchar *image_interface_little = g_strdup_printf("%s%s", PATH_TO_HIGH_CONTRAST_BUTTON_ICONS, "interface-little.png" ) ;
      gchar *image_interface_middle = g_strdup_printf("%s%s", PATH_TO_HIGH_CONTRAST_BUTTON_ICONS, "interface-middle.png" ) ;
      gchar *image_interface_big    = g_strdup_printf("%s%s", PATH_TO_HIGH_CONTRAST_BUTTON_ICONS, "interface-big.png" ) ;

      gchar *image_minimal_interface  = g_strdup_printf("%s%s", PATH_TO_HIGH_CONTRAST_BUTTON_ICONS, "window-minimize.png" ) ;

      gchar *image_theme_light  = g_strdup_printf("%s%s", PATH_TO_HIGH_CONTRAST_BUTTON_ICONS, "weather-clear.png"       ) ;
      gchar *image_theme_dark   = g_strdup_printf("%s%s", PATH_TO_HIGH_CONTRAST_BUTTON_ICONS, "weather-clear-night.png" ) ;

      gtk_image_set_from_file(GTK_IMAGE(user_data->image), image_smile) ;

      reset_image_widget(user_data->volume, image_volume_medium ) ;
      reset_image_widget(user_data->apply,  image_volume_ok           ) ;
      reset_image_widget(user_data->cancel, image_volume_close        ) ;

      reset_image_widget(user_data->little, image_interface_little    ) ;
      reset_image_widget(user_data->middle, image_interface_middle    ) ;
      reset_image_widget(user_data->big,    image_interface_big       ) ;

      reset_image_widget(user_data->min,    image_minimal_interface   ) ;

      reset_image_widget(user_data->theme_light,   image_theme_light) ;
      reset_image_widget(user_data->theme_dark,    image_theme_dark)  ;

      #endif

      #ifdef G_OS_UNIX
      gtk_image_set_from_file(GTK_IMAGE(user_data->image), PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "face-smile-big.png" ) ;

      reset_image_widget(user_data->volume, PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "audio-volume-medium.png" ) ;
      reset_image_widget(user_data->apply,  PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "dialog-ok.png"           ) ;
      reset_image_widget(user_data->cancel, PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "dialog-close.png"        ) ;

      reset_image_widget(user_data->little, PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "interface-little.png"    ) ;
      reset_image_widget(user_data->middle, PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "interface-middle.png"    ) ;
      reset_image_widget(user_data->big,    PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "interface-big.png"       ) ;

      reset_image_widget(user_data->min,    PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "window-minimize.png"     ) ;

      reset_image_widget(user_data->set_as_default,       PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "face-angel.png"   )   ;
      reset_image_widget(user_data->reset_association,    PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "face-devilish.png")   ;

      reset_image_widget(user_data->theme_light,   PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "weather-clear.png")          ;
      reset_image_widget(user_data->theme_dark,    PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "weather-clear-night.png")    ;
      #endif

      settings.icon_set_oxygen = false ;

      settings.path_to_button_icons =  PATH_TO_HIGH_CONTRAST_BUTTON_ICONS ;
      settings.path_to_menu_icons   =  PATH_TO_HIGH_CONTRAST_MENU_ICONS   ;


      #ifdef G_OS_WIN32
      g_free(image_smile) ;

      g_free(image_volume_medium) ;
      g_free(image_volume_ok) ;
      g_free(image_volume_close) ;

      g_free(image_interface_little) ;
      g_free(image_interface_middle) ;
      g_free(image_interface_big)    ;

      g_free(image_minimal_interface) ;

      g_free(image_theme_light)   ;
      g_free(image_theme_dark)    ;


      #endif

      gtk_menu_item_activate(GTK_MENU_ITEM(gui->menu->button_icons_high_contrast->menuitem)) ;

    }
    else {

      gtk_image_clear( GTK_IMAGE(user_data->image) ) ;



      #ifdef G_OS_WIN32
      gchar *image_angry =  g_strdup_printf("%s%s", PATH_TO_HIGH_CONTRAST_BUTTON_ICONS, "face-angry.png" ) ;

      gtk_image_set_from_file(GTK_IMAGE(user_data->image), image_angry ) ;

      g_free(image_angry) ;

      #endif

      #ifdef G_OS_UNIX
      gtk_image_set_from_file(GTK_IMAGE(user_data->image), PATH_TO_HIGH_CONTRAST_BUTTON_ICONS "face-angry.png" ) ;
      #endif

      settings.icon_set_oxygen = true ;

    }

  }
  else {

    // This mean the call comes from the menu item.

    settings.icon_set_oxygen = false ;

    settings.path_to_button_icons =  PATH_TO_HIGH_CONTRAST_BUTTON_ICONS ;
    settings.path_to_menu_icons   =  PATH_TO_HIGH_CONTRAST_MENU_ICONS   ;

    #ifdef G_OS_UNIX
    reset_image_widget(gui->menu->button_icons_high_contrast->image,  PATH_TO_HIGH_CONTRAST_MENU_ICONS "face-raspberry.png") ;

    reset_image_widget(gui->menu->button_icons_oxygen->image,         PATH_TO_HIGH_CONTRAST_MENU_ICONS "face-sad.png") ;
    #endif


    #ifdef G_OS_WIN32

    gchar *image_icon_theme_high_contrast = g_strdup_printf("%s%s", PATH_TO_HIGH_CONTRAST_MENU_ICONS, "face-raspberry.png") ;

    gchar *image_icon_theme_oxygen = g_strdup_printf("%s%s", PATH_TO_HIGH_CONTRAST_MENU_ICONS, "face-sad.png") ;

    reset_image_widget(gui->menu->button_icons_high_contrast->image, image_icon_theme_high_contrast) ;
    reset_image_widget(gui->menu->button_icons_oxygen->image, image_icon_theme_oxygen) ;

    g_free(image_icon_theme_high_contrast) ;
    g_free(image_icon_theme_oxygen) ;

    #endif
    
   
    reconfigure_interface_icons() ;

  }

  return ;

}

void configure_oxygen_radiobutton(GtkWidget *widget, Radio_Config *user_data) {

  if (user_data != NULL) {

    // This mean that the call comes from the configuration window.

    if ( gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON(user_data->button) ) ) {

      gtk_image_clear( GTK_IMAGE(user_data->image) ) ;


      #ifdef G_OS_WIN32
      gchar *image_smile = g_strdup_printf("%s%s", PATH_TO_OXYGEN_BUTTON_ICONS, "face-smile-big.png" ) ;

      gchar *image_volume_medium = g_strdup_printf("%s%s", PATH_TO_OXYGEN_BUTTON_ICONS, "audio-volume-medium.png" ) ;
      gchar *image_volume_ok = g_strdup_printf("%s%s", PATH_TO_OXYGEN_BUTTON_ICONS, "dialog-ok.png" ) ;
      gchar *image_volume_close = g_strdup_printf("%s%s", PATH_TO_OXYGEN_BUTTON_ICONS, "dialog-close.png" ) ;

      gchar *image_interface_little = g_strdup_printf("%s%s", PATH_TO_OXYGEN_BUTTON_ICONS, "interface-little.png" ) ;
      gchar *image_interface_middle = g_strdup_printf("%s%s", PATH_TO_OXYGEN_BUTTON_ICONS, "interface-middle.png" ) ;
      gchar *image_interface_big    = g_strdup_printf("%s%s", PATH_TO_OXYGEN_BUTTON_ICONS, "interface-big.png" ) ;

      gchar *image_minimal_interface  = g_strdup_printf("%s%s", PATH_TO_OXYGEN_BUTTON_ICONS, "window-minimize.png" ) ;

      gchar *image_theme_light  = g_strdup_printf("%s%s", PATH_TO_OXYGEN_BUTTON_ICONS, "weather-clear.png"       ) ;
      gchar *image_theme_dark   = g_strdup_printf("%s%s", PATH_TO_OXYGEN_BUTTON_ICONS, "weather-clear-night.png" ) ;

      gtk_image_set_from_file(GTK_IMAGE(user_data->image), image_smile) ;

      reset_image_widget(user_data->volume, image_volume_medium ) ;
      reset_image_widget(user_data->apply,  image_volume_ok           ) ;
      reset_image_widget(user_data->cancel, image_volume_close        ) ;

      reset_image_widget(user_data->little, image_interface_little    ) ;
      reset_image_widget(user_data->middle, image_interface_middle    ) ;
      reset_image_widget(user_data->big,    image_interface_big       ) ;

      reset_image_widget(user_data->min,    image_minimal_interface   ) ;

      reset_image_widget(user_data->theme_light,   image_theme_light) ;
      reset_image_widget(user_data->theme_dark,    image_theme_dark)  ;
      #endif

      #ifdef G_OS_UNIX
      gtk_image_set_from_file(GTK_IMAGE(user_data->image), PATH_TO_OXYGEN_BUTTON_ICONS "face-smile-big.png" ) ;

      reset_image_widget(user_data->volume, PATH_TO_OXYGEN_BUTTON_ICONS "audio-volume-medium.png" ) ;
      reset_image_widget(user_data->apply,  PATH_TO_OXYGEN_BUTTON_ICONS "dialog-ok.png"           ) ;
      reset_image_widget(user_data->cancel, PATH_TO_OXYGEN_BUTTON_ICONS "dialog-close.png"        ) ;

      reset_image_widget(user_data->little, PATH_TO_OXYGEN_BUTTON_ICONS "interface-little.png"    ) ;
      reset_image_widget(user_data->middle, PATH_TO_OXYGEN_BUTTON_ICONS "interface-middle.png"    ) ;
      reset_image_widget(user_data->big,    PATH_TO_OXYGEN_BUTTON_ICONS "interface-big.png"       ) ;

      reset_image_widget(user_data->min,    PATH_TO_OXYGEN_BUTTON_ICONS "window-minimize.png"     ) ;

      reset_image_widget(user_data->set_as_default,       PATH_TO_OXYGEN_BUTTON_ICONS "face-angel.png"   )   ;
      reset_image_widget(user_data->reset_association,    PATH_TO_OXYGEN_BUTTON_ICONS "face-devilish.png")   ;

      reset_image_widget(user_data->theme_light,   PATH_TO_OXYGEN_BUTTON_ICONS "weather-clear.png")          ;
      reset_image_widget(user_data->theme_dark,    PATH_TO_OXYGEN_BUTTON_ICONS "weather-clear-night.png")    ;
      #endif

      settings.icon_set_oxygen = true ;

      settings.path_to_button_icons =  PATH_TO_OXYGEN_BUTTON_ICONS  ;
      settings.path_to_menu_icons   =  PATH_TO_OXYGEN_MENU_ICONS    ;

      #ifdef G_OS_WIN32
      g_free(image_smile) ;

      g_free(image_volume_medium) ;
      g_free(image_volume_ok) ;
      g_free(image_volume_close) ;

      g_free(image_interface_little) ;
      g_free(image_interface_middle) ;
      g_free(image_interface_big)    ;

      g_free(image_minimal_interface) ;

      g_free(image_theme_light)   ;
      g_free(image_theme_dark)    ;
      #endif

      gtk_menu_item_activate(GTK_MENU_ITEM(gui->menu->button_icons_oxygen->menuitem)) ;

    }
    else {

      gtk_image_clear( GTK_IMAGE(user_data->image) ) ;



      #ifdef G_OS_WIN32
      gchar *image_angry =  g_strdup_printf("%s%s", PATH_TO_OXYGEN_BUTTON_ICONS, "face-angry.png" ) ;

      gtk_image_set_from_file(GTK_IMAGE(user_data->image), image_angry ) ;

      g_free(image_angry) ;

      #endif

      #ifdef G_OS_UNIX
      gtk_image_set_from_file(GTK_IMAGE(user_data->image), PATH_TO_OXYGEN_BUTTON_ICONS "face-angry.png" ) ;
      #endif

      settings.icon_set_oxygen = true ;

    }
  }
  else {

    // This mean the call comes from the menu item.

    settings.icon_set_oxygen = true ;

    settings.path_to_button_icons =  PATH_TO_OXYGEN_BUTTON_ICONS  ;
    settings.path_to_menu_icons   =  PATH_TO_OXYGEN_MENU_ICONS    ;

    #ifdef G_OS_UNIX
    reset_image_widget(gui->menu->button_icons_high_contrast->image,  PATH_TO_OXYGEN_MENU_ICONS "face-sad.png") ;

    reset_image_widget(gui->menu->button_icons_oxygen->image,         PATH_TO_OXYGEN_MENU_ICONS "face-raspberry.png") ;
    #endif


    #ifdef G_OS_WIN32

    gchar *image_icon_theme_high_contrast = g_strdup_printf("%s%s", PATH_TO_OXYGEN_MENU_ICONS, "face-sad.png") ;

    gchar *image_icon_theme_oxygen = g_strdup_printf("%s%s", PATH_TO_OXYGEN_MENU_ICONS, "face-raspberry.png") ;

    reset_image_widget(gui->menu->button_icons_high_contrast->image, image_icon_theme_high_contrast) ;
    reset_image_widget(gui->menu->button_icons_oxygen->image, image_icon_theme_oxygen) ;

    g_free(image_icon_theme_high_contrast) ;
    g_free(image_icon_theme_oxygen) ;

    #endif
     
    reconfigure_interface_icons() ;

  }

  return ;

}

void repeat_all_feature_set(GtkToggleButton *togglebutton, int *is_repeating_all) {

  switch (*is_repeating_all) {

    case 0 :

     set_repeat(0) ;
     gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_repeat_off->menuitem), TRUE ) ;
     break ;

    case 1 :
     set_repeat(1) ;
     gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_repeat_all->menuitem), TRUE ) ;
     break ;

    case 2 :
     set_repeat(2) ;
     gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_repeat_one->menuitem), TRUE ) ;
     break ;

    default :

      gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_repeat_off->menuitem), TRUE ) ;
      settings.is_repeat_all=0 ;
      break ;

  }

}

void set_volume(GtkRange *range, gpointer user_data) {

  settings.volume = gtk_range_get_value(GTK_RANGE(range)) ;

  gtk_scale_button_set_value(GTK_SCALE_BUTTON(gui->button_volume), settings.volume) ;

  libvlc_audio_set_volume(media_player, static_cast<int>(settings.volume * 100.0)) ;

}

void reconfigure_interface_size(GtkWidget *widget, int *user_data) {



  bool default_image ;

  if (is_playing) {

    default_image = (cover_image == settings.path_to_default_image) ;
  }
  else {

    default_image = true ;
  }

  switch ((*user_data)) {

    case -1 : // Little interface choice.

      settings.space_buttons = SPACE_BUTTONS_LITTLE ;

      settings.image_resized_size = IMAGE_RESIZED_SIZE_LITTLE ;

      #ifdef G_OS_UNIX
      settings.path_to_default_image =  PATH_TO_IMAGE "Micro_Music_Player_256.png" ;
      #endif


      #ifdef G_OS_WIN32
      settings.path_to_default_image =  PATH_TO_PRG_IMAGE_LITTLE ;
      #endif

      break ;

    case 0  : // Middle interface choice.

      settings.space_buttons = SPACE_BUTTONS_MIDDLE ;

      settings.image_resized_size = IMAGE_RESIZED_SIZE_MIDDLE ;

      #ifdef G_OS_UNIX
      settings.path_to_default_image = PATH_TO_IMAGE "Micro_Music_Player_288.png" ;  // ???
      #endif

      #ifdef G_OS_WIN32
      settings.path_to_default_image = PATH_TO_PRG_IMAGE_MIDDLE ;
      #endif

      break ;

    case 1  : // Big interface choice.

      settings.space_buttons = SPACE_BUTTONS_BIG ;

      settings.image_resized_size = IMAGE_RESIZED_SIZE_BIG ;

      #ifdef G_OS_UNIX
      settings.path_to_default_image =  PATH_TO_IMAGE "Micro_Music_Player_320.png" ;  // ???
      #endif

      #ifdef G_OS_WIN32
      settings.path_to_default_image =  PATH_TO_PRG_IMAGE_BIG ;
      #endif

      break ;

   default :

     return ;

  }



  gtk_widget_set_size_request(gui->image_container, settings.image_resized_size, settings.image_resized_size ) ;


  // By size change we must reconfigre image if default or not !
  g_object_ref(gui->image_widget) ;

  gtk_container_remove(GTK_CONTAINER(gui->image_container), gui->image_widget) ;

  gtk_image_clear(GTK_IMAGE(gui->image_widget)) ;

  if (default_image) {

    gtk_image_set_from_file(GTK_IMAGE(gui->image_widget), settings.path_to_default_image.c_str() ) ;

    gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, 0, 0 ) ;

  }
  else {

    //cover_image stay the same.

    auto new_size = resizer.resizer(cover_image, settings.image_resized_size, settings.image_resized_size, false) ;

    GError *error = NULL ;

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(cover_image.c_str(), &error);

    if (error != NULL) {

      cover_image = settings.path_to_default_image ;

      gtk_image_set_from_file(GTK_IMAGE(gui->image_widget), settings.path_to_default_image.c_str() ) ;

      gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, 0, 0 ) ;

      fprintf(stderr,"Error loading image file:\n%s\n", error->message) ;

      g_error_free(error) ;

      error = NULL ;


    }
    else {
      
      #if 0
      // Reserved for future usages !
      // No ratio keeping because of animations.
      GdkPixbuf *pixbuf_scaled = gdk_pixbuf_scale_simple(pixbuf,
                                                         settings.image_resized_size,
                                                         settings.image_resized_size,
                                                         GDK_INTERP_HYPER);


      #endif

      // Ration keeping resizing with the best interpolation.
      GdkPixbuf *pixbuf_scaled = gdk_pixbuf_scale_simple(pixbuf,
                                                         new_size.first,
                                                         new_size.second,
                                                         GDK_INTERP_HYPER);

      g_object_unref(pixbuf) ;

      gtk_image_set_from_pixbuf(GTK_IMAGE(gui->image_widget), pixbuf_scaled) ;

      g_object_unref(pixbuf_scaled) ;

      gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, (settings.image_resized_size-new_size.first) / 2 ,  (settings.image_resized_size-new_size.second) / 2 ) ;
      
      #if 0
      // Reserved for future usages !
      gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, 0 ,  0 ) ; // No ratio keeping this is for future usages...
      #endif

    }

  }

  gtk_box_set_spacing(GTK_BOX(gui->controls_buttonbox), settings.space_buttons) ;


  return ;

}

void switch_to_light_theme_menu(GtkWidget *widget, gpointer g_ptr) {

  /** Do all the work of changing the theme when called from anywhere from program. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  GtkSettings *gtk_settings_for_screen = gtk_settings_get_for_screen(gtk_window_get_screen(GTK_WINDOW(gui->window))) ;

  GtkCssProvider *provider = NULL ;

  char *theme_name = NULL ;

  g_object_get(G_OBJECT(gtk_settings_for_screen), "gtk-theme-name", &theme_name, NULL) ;

  if (theme_name != NULL) {

    provider = gtk_css_provider_get_named(theme_name, NULL) ;

    g_free(theme_name) ;

  }

  if (provider != NULL) {

    GdkDisplay *display = gdk_display_get_default() ;

    GdkScreen *screen = gdk_display_get_default_screen(display) ;

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION) ;

    settings.theme_light  = TRUE ;

  }
 
  return ;
}

void switch_to_dark_theme_menu(GtkWidget *widget, gpointer g_ptr) {

  /** Do all the work of changing the theme when called from anywhere from program. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  GtkSettings *gtk_settings_for_screen = gtk_settings_get_for_screen(gtk_window_get_screen(GTK_WINDOW(gui->window))) ;

  GtkCssProvider *provider = NULL ;

  char *theme_name = NULL ;

  g_object_get(G_OBJECT(gtk_settings_for_screen), "gtk-theme-name", &theme_name, NULL) ;

  if (theme_name != NULL) {

    provider = gtk_css_provider_get_named(theme_name, "dark") ;

    g_free(theme_name) ;

  }

  if (provider != NULL) {

    GdkDisplay *display = gdk_display_get_default() ;

    GdkScreen *screen = gdk_display_get_default_screen(display) ;

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION) ;

    settings.theme_light  = FALSE ;

  }
 
   
  return ;
}


void configure_theme_light(GtkWidget *widget, gpointer *user_data) {

  if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget) ) ) {

    // Simply call the menu item callback where all the work is done.
    gtk_menu_item_activate( GTK_MENU_ITEM(gui->menu->button_theme_light->menuitem) ) ;

  }
  else {

    // Simply call the menu item callback where all the work is done.
    gtk_menu_item_activate( GTK_MENU_ITEM(gui->menu->button_theme_dark->menuitem) ) ;

  }

  return ;

}

void configure_theme_dark(GtkWidget *widget, gpointer *user_data) {
 
  /** Called from the configuration window. **/
 
  if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget) ) ) {

    // Simply call the menu item callback where all the work is done.
    gtk_menu_item_activate( GTK_MENU_ITEM(gui->menu->button_theme_dark->menuitem) ) ;

  }
  else {

    // Simply call the menu item callback where all the work is done.
    gtk_menu_item_activate( GTK_MENU_ITEM(gui->menu->button_theme_light->menuitem) ) ;

  }

  return ;

}