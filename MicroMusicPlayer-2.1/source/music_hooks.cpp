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

#include "music_hooks.h"

void selected_song(const int song_index) {

  /** Play a song from playlist selection. **/


  set_stop(false) ;

  // Clear current song string.
  //current_song_name.clear() ;
  //current_song_name.shrink_to_fit() ;

  // Set playlist selected song index.
  music_song_counter = song_index ;

  //current_song_name = folder_music_playlist_container.at( music_song_counter ) ;

  // Update the displayed playlist window if currently displayed.
  update_playlist() ;

  timeout_action = true ;

}



static void following_song_hook(void) {

  /** Play next song hook function **/

  if ( music_song_counter < (total_song_counter-1) && ! play_order) {
    music_song_counter++ ;
  }
  else if ( music_song_counter > 0                 &&   play_order) {
    music_song_counter-- ;
  }
  else if (music_song_counter == (total_song_counter-1) ) {

    /** End of playlist reached. **/

    if (is_repeat_all) { // Repeat all feature enabled.

      music_song_counter = 0 ;

    }
    else {  // Repeat all feature disabled.

      if (! is_shuffle) { // Shuffle feature disabled.



        // We stop playing song as set from the user.
        stop_music(NULL, NULL) ;

        // Update the displayed playlist window if currently displayed.
        update_playlist() ;

        return ;
      }

    }

  }

  if (is_shuffle) { music_song_counter = shuffle_get_song_index() ; if (is_end_of_shuffle_playlist()) { stop_music(NULL, NULL) ; return ; } ;  }

  // Update the displayed playlist window if currently displayed.
  update_playlist() ;

  timeout_action = true ;

}


void music_finished_hook(const struct libvlc_event_t *event, void *data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  //current_song_name.clear() ;
  //current_song_name.shrink_to_fit() ;


  if (is_stopped) { return ; }

  following_song_hook() ;


  return ;

}

static void set_cover_image(const string filepath) {

  cover_image = filepath ;

  if (gui->image_widget != NULL) {

    g_object_ref(gui->image_widget) ;

    gtk_container_remove(GTK_CONTAINER(gui->image_container), gui->image_widget) ;

    gtk_image_clear(GTK_IMAGE(gui->image_widget)) ;

  }


  GError *error = NULL ;

  auto new_size = resizer.resizer(filepath, settings.image_resized_size, settings.image_resized_size, false) ;

  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filepath.c_str(), &error);



  if (error != NULL) {
   
    cover_image = settings.path_to_default_image ;

    gtk_image_set_from_file(GTK_IMAGE(gui->image_widget), settings.path_to_default_image.c_str() ) ;

    gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, (settings.display_size - settings.image_resized_size) / 2, (settings.display_size - settings.image_resized_size)  / 2 ) ;

    g_error_free(error) ;

    return ;

  }


  GdkPixbuf *pixbuf_scaled = gdk_pixbuf_scale_simple(pixbuf,
                                                     new_size.first,
                                                     new_size.second,
                                                     GDK_INTERP_HYPER);





  g_object_unref(pixbuf) ;

  gtk_image_set_from_pixbuf(GTK_IMAGE(gui->image_widget), pixbuf_scaled) ;

  g_object_unref(pixbuf_scaled) ;

  gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, (settings.display_size-new_size.first)/2 ,  (settings.display_size-new_size.second) /2 ) ;



  return ;

}

bool timeout_timeline(void *user_data) {



  if (libvlc_media_player_is_playing(media_player)) {

    gtk_scale_clear_marks(GTK_SCALE(gui->timeline_scale)) ;

    float delay = libvlc_media_player_get_position(media_player) ;

    gtk_range_set_value(GTK_RANGE(gui->timeline_scale), static_cast<double>(delay)) ;

    gtk_scale_add_mark(GTK_SCALE(gui->timeline_scale), static_cast<double>(delay), GTK_POS_TOP, NULL);

  }



  return TRUE ;

}


bool timeout_update(void *user_data) {



  if (! timeout_action) { return TRUE ; }

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  libvlc_media_t *media ;

  media = libvlc_media_new_path(vlc_inst, folder_music_playlist_container.at( music_song_counter ).c_str() );

  if (media == NULL) {

    return TRUE ;
  }

  libvlc_media_player_set_media(media_player, media);

  libvlc_media_player_play(media_player) ;

  while (! libvlc_media_player_is_playing(media_player)) { }

  if (! imaging_cover_container.empty()) {

    set_cover_image(imaging_cover_container.at(music_song_counter)) ;

  }

  int64_t duration_min = (libvlc_media_get_duration(media) / 1000.0) / 60 ;

  int64_t duration_sec = (libvlc_media_get_duration(media) / 1000)  % 60 ;

  double value = (static_cast<double>(duration_min) * 60.0) + (static_cast<double>(duration_sec)) ;

  gchar *media_duration = g_strdup_printf("%02li:%02li", duration_min, duration_sec) ;

  factor = value ;

  if ((duration_min <= 0.0) && (duration_sec == 0.0)) {

    factor = 1.0 ;

    g_object_set(G_OBJECT(gui->timeline_scale), "draw-value", FALSE, NULL) ;

  }
  else {

    bool is_draw_value ;

    g_object_get(G_OBJECT(gui->timeline_scale), "draw-value", &is_draw_value, NULL) ;

    if (! is_draw_value) {
      g_object_set(G_OBJECT(gui->timeline_scale), "draw-value", TRUE, NULL) ;
    }

  }

  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: playing song\n -> %s\n", prgname.c_str(), (to_string(music_song_counter+1)+" "+title_author_container.at(music_song_counter)+" "+string(media_duration)).c_str() ) ; fflush(stdout) ;
  #endif
  #endif

  libvlc_media_release(media);

  gtk_entry_set_text(GTK_ENTRY(gui->song_name_entry), (to_string(music_song_counter+1)+" "+title_author_container.at(music_song_counter)+" "+string(media_duration)).c_str()) ;

  g_free(media_duration) ;

  // Set album name.
  gtk_button_set_label(GTK_BUTTON(gui->folder_chooser_button), album_names_container.at(music_song_counter).c_str() ) ;

  timeout_action = false ;

  return TRUE ;

}