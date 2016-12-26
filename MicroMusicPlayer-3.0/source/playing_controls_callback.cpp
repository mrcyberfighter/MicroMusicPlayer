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

#include "playing_controls_callback.h"

static bool trigger_volume_change = true ;

static void reset_volume_timer_settings(gpointer data) {
 
  trigger_volume_change = true ;
 
  return ;
}   


static gboolean hide_volume_pop_over_if_needed(gpointer data) {
 
  GtkWidget *pop_up = gtk_scale_button_get_popup( GTK_SCALE_BUTTON(gui->button_volume) ) ;

  if (gtk_widget_get_visible(pop_up)) {
   
    gtk_widget_hide(pop_up) ;
  }
 
  return FALSE ;

}   

void increment_volume(GtkWidget *widget, gpointer user_data) {

  /** Increment volume callback (menuitem and shortcut). **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  int volume = libvlc_audio_get_volume(media_player) ;

  if (volume < 100) {

    ++volume ;
  }

  libvlc_audio_set_volume(media_player, volume) ;

  gtk_scale_button_set_value( GTK_SCALE_BUTTON(gui->button_volume), static_cast<double>(volume/100.0));

  settings.volume = static_cast<double>(volume/100.0) ;

  #ifdef INFO
  #if (INFO >= 3)
  fprintf(stdout,"\n%s: Change volume to %.2lf\n", g_get_prgname(), settings.volume) ; fflush(stdout) ;
  #endif
  #endif

  GtkWidget *pop_up = gtk_scale_button_get_popup( GTK_SCALE_BUTTON(gui->button_volume) ) ;

  if (not gtk_widget_get_visible(pop_up)) {
  
    // The problem is that you can't detect the end of dragging a slider and
    // so their no way to hide the pop_up after the user has finished to use the menu item or shortcut as consequence.
  
    gtk_widget_show(pop_up) ;

  }
 
  if (trigger_volume_change) {
   
    g_timeout_add_seconds_full(G_PRIORITY_DEFAULT, 5, (GSourceFunc) hide_volume_pop_over_if_needed, NULL, &reset_volume_timer_settings) ;
   
    trigger_volume_change = false ;
 
  }
 
  return ;

}

void decrement_volume(GtkWidget *widget, gpointer user_data) {

  /** Decrement volume callback (menuitem and shortcut). **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  int volume = libvlc_audio_get_volume(media_player) ;

  if (volume > 0) {

    --volume ;
  }

  libvlc_audio_set_volume(media_player, volume) ;

  gtk_scale_button_set_value( GTK_SCALE_BUTTON(gui->button_volume), static_cast<double>(volume)/100.0);

  settings.volume = static_cast<double>(volume/100.0) ;

  #ifdef INFO
  #if (INFO >= 3)
  fprintf(stdout,"\n%s: Change volume to %.2lf\n", g_get_prgname(), settings.volume) ; fflush(stdout) ;
  #endif
  #endif

  GtkWidget *pop_up = gtk_scale_button_get_popup( GTK_SCALE_BUTTON(gui->button_volume) ) ;

  if (not gtk_widget_get_visible(pop_up)) {
  
    // The problem is that you can't detect the end of dragging a slider and
    // so their no way to hide the pop_up after the user has finished to use the menu item or shortcut as consequence.
  
    gtk_widget_show(pop_up) ;
  }
 
  if (trigger_volume_change) {
   
    g_timeout_add_seconds_full(G_PRIORITY_DEFAULT, 5, (GSourceFunc) hide_volume_pop_over_if_needed, NULL, &reset_volume_timer_settings) ;
   
    trigger_volume_change = false ;
 
  }
 
  return ;

}

void play_music(GtkWidget *widget, gpointer user_data) {

  /** User press the play button callback. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  if (! is_paused && is_playing) {

    // Toggle to paused status.

    pausing :

    pause_music(NULL, NULL) ;


    return ;
  }


  if (! is_playing ) {

    if (folder_music_playlist_container.empty()) {

      return ;
    }

    // If shuffle feature enable if yes: getting the index of next song and
    // so pop the index from the playlist_shuffle_indexes vector.
    if (is_shuffle) { music_song_counter = shuffle_get_song_index() ; }

    if( ! libvlc_media_player_is_playing(media_player) ) {

      // Music player is not playing !

      if (is_stopped) {


        // We set the cover image if needed.
        if (gui->image_widget != NULL) {

          g_object_ref(gui->image_widget) ;

          gtk_container_remove(GTK_CONTAINER(gui->image_container), gui->image_widget) ;

          gtk_image_clear(GTK_IMAGE(gui->image_widget)) ;

        }

        if ( cover_image != settings.path_to_default_image ) {  // Cover image not equal to default image.

          // The music soon have a cover image which isn't the default image we set it has image.
      
          auto new_size = resizer.resizer(cover_image, settings.image_resized_size, settings.image_resized_size, false) ;
      
          GError *error =  NULL ;

          GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(cover_image.c_str(), &error);

          if (error != NULL) {
        
            fprintf(stderr,"Error loading image file:\n%s\n", error->message) ;
        
            g_error_free(error) ;
        
            error = NULL ;
        
            goto default_image ;

          }
       
      
          #if 0
          // Reserve for future usages !
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

          gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, (settings.image_resized_size-new_size.first)/2 ,  (settings.image_resized_size-new_size.second) /2 ) ;

          #if 0
          // Reserved for future usages !
          gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, 0 ,  0 ) ; // No ratio keeping this is for future usages...
          #endif

        }
        else {

          default_image :

          // We set the default image.

          gtk_image_set_from_file(GTK_IMAGE(gui->image_widget), cover_image.c_str() ) ;

          gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, 0, 0 ) ;

        }



      }


      gtk_entry_set_text(GTK_ENTRY(gui->song_name_entry), title_author_container.at(music_song_counter).c_str()) ;


      // Reset controls variables.
      set_pause(false)    ;
      set_playing(true)   ;
      set_stop(false)     ;

      // Hide the pause button which is at the same position as the play button which we show if needed.
      gtk_widget_hide(gui->button_pause) ;
      gtk_widget_show(gui->button_play)  ;


      if (at_start) {

        timeout_action = true ;

        at_start = false ;

      }
      else {

        libvlc_media_player_pause(media_player) ;
      }

    }

  }

  else {

    // Jump to the pause treatment label.
    goto pausing ;

  }

  gtk_entry_set_text(GTK_ENTRY(gui->song_name_entry), title_author_container.at(music_song_counter).c_str() ) ;

  return ;

}

void prev_music(GtkWidget *widget, gpointer user_data)  {

  /** User press previous song button callback **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  playlist_before_selection_idx = music_song_counter ;

  if (music_song_counter == 0) {

    // The current song was the first song in playlist before pushing the previous button.

    if (is_repeat_all == 1) { // repeat all feature enabled.

      music_song_counter = total_song_counter ;

      // This define the song playing order.
      set_order(true) ;

    }

  }
  else {

    // Isn't the first song.

    // This define the song playing order.
    set_order(true) ;

  }

  music_finished_hook(NULL, NULL) ;

  // Hide the pause button which is at the same position as the play button which we show if needed.
  gtk_widget_hide(gui->button_pause) ;
  gtk_widget_show(gui->button_play)  ;

  return ;
}

void next_music(GtkWidget *widget, gpointer user_data)  {

  /** User press next song button callback **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif


  playlist_before_selection_idx = music_song_counter ;

  if ( music_song_counter == total_song_counter) {

    if (is_repeat_all) { // repeat all feature enabled.

      music_song_counter = 0 ;

    }

  }
  else {

    // This define the song playing order.
    set_order(false) ;

  }

  music_finished_hook(NULL, NULL) ;

  // Hide the pause button which is at the same position as the play button which we show if needed.
  gtk_widget_hide(gui->button_pause) ;
  gtk_widget_show(gui->button_play)  ;

  return ;
}

void stop_music(GtkWidget *widget, gpointer user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif


  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: Stop playing music.\n", g_get_prgname() ) ; fflush(stdout) ;
  #endif
  #endif





  if ( cover_image != settings.path_to_default_image ) { // Cover image not equal to default image.

    // We reset default image has cover by stopping.

    if (gui->image_widget != NULL) {

      g_object_ref(gui->image_widget) ;

      gtk_container_remove(GTK_CONTAINER(gui->image_container), gui->image_widget) ;

      gtk_image_clear(GTK_IMAGE(gui->image_widget)) ;

      gtk_image_set_from_file(GTK_IMAGE(gui->image_widget), settings.path_to_default_image.c_str() ) ;

      gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, 0, 0 ) ;

    }


  }

  gtk_range_set_value(GTK_RANGE(gui->timeline_scale), 0.0) ;


  // Reset controls variables.
  set_pause(true)      ;
  set_playing(false)   ;
  set_stop(true)       ;

  gtk_entry_set_text(GTK_ENTRY(gui->song_name_entry), "") ;

  #ifdef G_OS_UNIX
  gtk_button_set_label(GTK_BUTTON(gui->folder_chooser_button),  "Select a folder to play content") ;
  gtk_widget_set_tooltip_text(gui->folder_chooser_button,       "Select the folder to play music files from.") ;
  #endif



  #ifdef G_OS_WIN32
  gtk_button_set_label(GTK_BUTTON(gui->folder_chooser_button), "Select music files to play") ;
  gtk_widget_set_tooltip_markup(gui->folder_chooser_button,  "Select music files to play:\n"
                                                             "<big><b>Use multiples selection:</b></big> <b>hold</b> <big><b><i>Ctrl</i></b></big> <b>or</b> <big><b><i>Shift</i></b></big> <b>by using the mouse</b>.\n"
                                                             "<big><b>For composing your playlist</b></big> and <b>enjoy !!!</b>.")      ;
  #endif

  music_song_counter = 0 ;

  at_start = true ;

  gtk_widget_hide(gui->button_pause) ;
  gtk_widget_show(gui->button_play)  ;

  if (libvlc_media_player_is_playing(media_player)) {
    libvlc_media_player_stop(media_player) ;
  }

  duration_min = 0 ;

  duration_sec = 0 ;

  return ;
}

void pause_music(GtkWidget *widget, gpointer user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif


  if (! libvlc_media_player_is_playing(media_player)) {
    /** Resume the music. **/


    #ifdef INFO
    #if (INFO >= 1)
    fprintf(stdout,"\n%s: Resume music.\n", g_get_prgname()) ; fflush(stdout) ;
    #endif
    #endif

    gtk_widget_hide(gui->button_pause) ;
    gtk_widget_show(gui->button_play)  ;

    set_pause(false)    ;
  }
  else {

    /** Pause the music.  **/


    #ifdef INFO
    #if (INFO >= 1)
    fprintf(stdout,"\n%s: Pausing music.\n", g_get_prgname()) ; fflush(stdout) ;
    #endif
    #endif

    gtk_widget_hide(gui->button_play) ;
    gtk_widget_show(gui->button_pause)  ;

    set_pause(true)    ;
  }

  // Toggle pause and resume music.
  libvlc_media_player_pause(media_player) ;

  return ;

}


#ifdef TOGGLE_BUTTONS_INTERFACE
void repeat_all_music(GtkToggleButton *togglebutton, gpointer user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

}
#else

static inline void update_repeat_image(void) ;

static inline void update_repeat_image(void) {

  switch (is_repeat_all) {

    case 0 :

      gtk_image_clear(GTK_IMAGE(gui->button_repeat_image)) ;

      gtk_image_set_from_file(GTK_IMAGE(gui->button_repeat_image), (settings.path_to_button_icons +  "user-offline.png").c_str()) ;

      gtk_widget_set_tooltip_markup(gui->button_repeat,  "(Enable | Disable) <b>Repeat</b> (<i>All</i> | <i>One</i>) playlist [ <b>Ctrl (+ Maj) + R</b> ]") ;

      break ;

    case 1 :

      gtk_image_clear(GTK_IMAGE(gui->button_repeat_image)) ;

      gtk_image_set_from_file(GTK_IMAGE(gui->button_repeat_image), (settings.path_to_button_icons +  "media-playlist-repeat.png").c_str() ) ;

      gtk_widget_set_tooltip_markup(gui->button_repeat,  "<b>Repeat</b>-<b>All</b> playlist <b>Enabled</b>") ;

      break ;

    case 2 :

      gtk_image_clear(GTK_IMAGE(gui->button_repeat_image)) ;

      gtk_image_set_from_file(GTK_IMAGE(gui->button_repeat_image), (settings.path_to_button_icons +  "media-playlist-repeat-song.png").c_str() ) ;

      gtk_widget_set_tooltip_markup(gui->button_repeat,  "<b>Repeat</b>-<b>One</b> playlist <b>Enabled</b>") ;

      break ;

  }

  return ;

}

void repeat_all_music(GtkWidget *button, gpointer user_data) {

  /**   Their nothing in this function which is called when you press the button
    *   except the call to activate the menuitem,
    *   in which handler all the work is done.
    *   So no matter if you press the button or activate the menuitem.
    *****************************************************************************/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  switch (is_repeat_all) {

    case 0 :

       gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_repeat_all->menuitem), TRUE) ;
       break ;

     case 1 :

        gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_repeat_one->menuitem), TRUE) ;
        break ;

    case 2 :


        gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_repeat_off->menuitem), TRUE) ;
        break ;
  }

  return ;

}
#endif

void menu_repeat_off_music(GtkCheckMenuItem *menuitem, gpointer user_data) {

  set_repeat(0) ;

  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: Repeat %s\n", g_get_prgname(),  "disabled" ) ; fflush(stdout) ;
  #endif
  #endif

  update_repeat_image() ;

}

void menu_repeat_all_music(GtkCheckMenuItem *menuitem, gpointer user_data) {



  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: Repeat %s function enabled\n", g_get_prgname(),  "all" ) ; fflush(stdout) ;
  #endif
  #endif

  set_repeat(1) ;

  update_repeat_image() ;

}

void menu_repeat_one_music(GtkCheckMenuItem *menuitem, gpointer user_data) {



  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: Repeat %s function enabled\n", g_get_prgname(),  "one" ) ; fflush(stdout) ;
  #endif
  #endif

  set_repeat(2) ;

  update_repeat_image() ;

}

static inline void update_shuffle_image(void) ;

static inline void update_shuffle_image(void) {

  if (! is_shuffle) {

    gtk_image_clear(GTK_IMAGE(gui->button_shuffle_image)) ;
    gtk_image_clear(GTK_IMAGE(gui->menu->button_shuffle->image)) ;
    gtk_image_set_from_file(GTK_IMAGE(gui->button_shuffle_image), (settings.path_to_button_icons +    "user-offline.png").c_str()) ;
    gtk_image_set_from_file(GTK_IMAGE(gui->menu->button_shuffle->image), (settings.path_to_menu_icons +      "user-offline.png").c_str()) ;
    gtk_widget_set_tooltip_markup(gui->button_shuffle, "(Enable | Disable) <b>shuffle</b> playing mode [ <b>Ctrl + Maj + S</b> ]") ;

  }
  else {

    gtk_image_clear(GTK_IMAGE(gui->button_shuffle_image)) ;
    gtk_image_clear(GTK_IMAGE(gui->menu->button_shuffle->image)) ;

    gtk_image_set_from_file(GTK_IMAGE(gui->button_shuffle_image), (settings.path_to_button_icons +  "media-playlist-shuffle.png").c_str() ) ;
    gtk_image_set_from_file(GTK_IMAGE(gui->menu->button_shuffle->image), (settings.path_to_button_icons +  "media-playlist-shuffle.png").c_str() ) ;

    gtk_widget_set_tooltip_markup(gui->button_shuffle, "<b>shuffle</b> playing mode <b>Enabled</b> [ <b>Ctrl + Maj + S</b> ]") ;

  }

  return ;

}

void shuffle_music(GtkWidget *button, gpointer user_data) {

  /**   Their nothing in this function which is called when you press the button
    *    except the call to activate the menuitem,
    *    in which handler all the work is done.
    *    So no matter if you press the button or activate the menuitem.
    ************************************************************/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: Shuffle function %s\n", g_get_prgname(),  (is_shuffle) ? "on" : "off" ) ; fflush(stdout) ;
  #endif
  #endif

  gtk_menu_item_activate(GTK_MENU_ITEM(gui->menu->button_shuffle->menuitem)) ;


}

void menu_shuffle_music(GtkCheckMenuItem *menuitem, gpointer user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  if (not start_app) {

    is_shuffle = not is_shuffle ;

    set_shuffle(is_shuffle) ;

    settings.is_shuffle = is_shuffle ;

  }



  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: Shuffle function %s\n", g_get_prgname(), ((is_shuffle) ? "on" : "off") ) ; fflush(stdout) ;
  #endif
  #endif

  update_shuffle_image() ;

}



void change_volume(GtkScaleButton *button, gdouble value, gpointer user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif



  #ifdef INFO
  #if (INFO >= 3)
  fprintf(stdout,"\n%s: Change volume to %.2lf\n", g_get_prgname(), value) ; fflush(stdout) ;
  #endif
  #endif

  libvlc_audio_set_volume(media_player, static_cast<int>(value * 100.0)) ;



  return ;

}