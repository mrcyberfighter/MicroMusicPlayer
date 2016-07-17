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
          
            g_error_free(error) ;
          
            goto default_image ;
          
          }
        
          GdkPixbuf *pixbuf_scaled = gdk_pixbuf_scale_simple(pixbuf,
                                                           new_size.first,
                                                           new_size.second,
                                                           GDK_INTERP_HYPER);
   
          g_object_unref(pixbuf) ;
   
          gtk_image_set_from_pixbuf(GTK_IMAGE(gui->image_widget), pixbuf_scaled) ;
   
          g_object_unref(pixbuf_scaled) ;
   
          gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, (settings.display_size-new_size.first)/2 ,  (settings.display_size-new_size.second) /2 ) ;

        }
        else {
        
          default_image :
        
          // We set the default image.

          gtk_image_set_from_file(GTK_IMAGE(gui->image_widget), cover_image.c_str() ) ;

          gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, (settings.display_size - settings.image_resized_size) / 2, (settings.display_size - settings.image_resized_size)  / 2 ) ;

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

  if (music_song_counter == 0) {

    // The current song was the first song in playlist before pushing the previous button.

    if (is_repeat_all) { // repeat all feature enabled.

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


  if ( music_song_counter == total_song_counter) {

    if (is_repeat_all) { // repeat all feature enabled.

      music_song_counter = 0 ;

      // This define the song playing order.
      set_order(true) ;

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
  fprintf(stdout,"\n%s: Stop playing music.\n", prgname.c_str() ) ; fflush(stdout) ;
  #endif
  #endif





  if ( cover_image != settings.path_to_default_image ) { // Cover image not equal to default image.

    // We reset default image has cover by stopping.

    if (gui->image_widget != NULL) {

      g_object_ref(gui->image_widget) ;

      gtk_container_remove(GTK_CONTAINER(gui->image_container), gui->image_widget) ;

      gtk_image_clear(GTK_IMAGE(gui->image_widget)) ;

      gtk_image_set_from_file(GTK_IMAGE(gui->image_widget), settings.path_to_default_image.c_str() ) ;
   
      gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, (settings.display_size - settings.image_resized_size) / 2, (settings.display_size - settings.image_resized_size)  / 2 ) ;
   
    }
 
   
  }

  gtk_scale_clear_marks(GTK_SCALE(gui->timeline_scale)) ;

  gtk_range_set_value(GTK_RANGE(gui->timeline_scale), 0.0) ;

  gtk_scale_add_mark(GTK_SCALE(gui->timeline_scale), 0.0, GTK_POS_TOP, NULL);
 

  // Reset controls variables.
  set_pause(true)      ;
  set_playing(false)   ;
  set_stop(true)       ;

  gtk_entry_set_text(GTK_ENTRY(gui->song_name_entry), "") ;

  gtk_button_set_label(GTK_BUTTON(gui->folder_chooser_button), "Select a folder to play content") ;

  music_song_counter = 0 ;

  at_start = true ;

  gtk_widget_hide(gui->button_pause) ;
  gtk_widget_show(gui->button_play)  ;

  if (libvlc_media_player_is_playing(media_player)) {
    libvlc_media_player_stop(media_player) ;
  }

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
    fprintf(stdout,"\n%s: Resume music.\n", prgname.c_str()) ; fflush(stdout) ;
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
    fprintf(stdout,"\n%s: Pausing music.\n", prgname.c_str()) ; fflush(stdout) ;
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

void repeat_all_music(GtkToggleButton *togglebutton, gpointer user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  /** NOTE: repeat all is good but maybe add a repeat one feature were better. **/

  set_repeat(gtk_toggle_button_get_active(togglebutton)) ;

  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: Repeat all function %s\n", prgname.c_str(),  ((is_repeat_all) ? "on" : "off") ) ; fflush(stdout) ;
  #endif
  #endif

  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_repeat->menuitem), is_repeat_all) ;



}

void menu_repeat_all_music(GtkCheckMenuItem *menuitem, gpointer user_data) {

  set_repeat( gtk_check_menu_item_get_active(menuitem) ) ;

  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: Repeat all function %s\n", prgname.c_str(), ((is_repeat_all) ? "on" : "off") ) ; fflush(stdout) ;
  #endif
  #endif

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->button_repeat), is_repeat_all) ;

}



void shuffle_music(GtkToggleButton *togglebutton, gpointer user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  set_shuffle(gtk_toggle_button_get_active(togglebutton)) ;

  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: Shuffle function %s\n", prgname.c_str(),  (is_shuffle) ? "on" : "off" ) ; fflush(stdout) ;
  #endif
  #endif

  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_shuffle->menuitem), is_shuffle) ;

}

void menu_shuffle_music(GtkCheckMenuItem *menuitem, gpointer user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  set_shuffle( gtk_check_menu_item_get_active(menuitem)) ;

  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: Shuffle function %s\n", prgname.c_str(), ((is_shuffle) ? "on" : "off") ) ; fflush(stdout) ;
  #endif
  #endif

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gui->button_shuffle), is_shuffle) ;

}

void change_volume(GtkScaleButton *button, gdouble value, gpointer user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif



  #ifdef INFO
  #if (INFO >= 3)
  fprintf(stdout,"\n%s: Change volume to %.0lf\n", prgname.c_str(), value * 100.0) ; fflush(stdout) ;
  #endif
  #endif

  libvlc_audio_set_volume(media_player, static_cast<int>(value * 100.0)) ;



  return ;

}