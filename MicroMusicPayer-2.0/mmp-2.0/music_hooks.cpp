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

void selected_song(const int song_index) {

  /** Play a song from playlist selection. **/


  set_stop(false) ;

  // Clear current song string.
  current_song_name.clear() ;
  current_song_name.shrink_to_fit() ;

  // Set playlist selected song index.
  music_song_counter = song_index ;

  current_song_name = folder_music_playlist_container.at( music_song_counter ) ;

  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: playing song\n -> %s\n", prgname.c_str(), g_path_get_basename(current_song_name.c_str()) ) ; fflush(stdout) ;
  #endif
  #endif

  // Update the displayed playlist window if currently displayed.
  update_playlist() ;

  //gtk_entry_set_text(GTK_ENTRY(gui->song_name_entry), g_path_get_basename(current_song_name.c_str()) ) ;

  timeout_action = true ;

}



void following_song_hook(void) {

  /** Play next song hook function **/


  if (! play_folder_content ) {
  
    // Case you play a single file.
  
    if (is_repeat_all) {
    
      timeout_action = true ;
    
      return ;
    }
    else {
    
      stop_music(NULL, NULL) ;
    
      return ;
    } 

  }    
    
    

  current_song_name.clear() ;
  current_song_name.shrink_to_fit() ;

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

  current_song_name = folder_music_playlist_container.at( music_song_counter ) ;



  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: playing song\n -> %s\n", prgname.c_str(), g_path_get_basename(current_song_name.c_str()) ) ; fflush(stdout) ;
  #endif
  #endif

  // Update the displayed playlist window if currently displayed.
  update_playlist() ;

  timeout_action = true ;

}


void music_finished_hook(const struct libvlc_event_t *event, void *data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  current_song_name.clear() ;
  current_song_name.shrink_to_fit() ;


  if (is_stopped) { return ; }

  following_song_hook() ;


  return ;

}

bool timeout_update(void *user_data) {

  #ifdef DEBUG
  //DEBUG_FUNC_MARK // Call to often every 1/10 second -> Too much output.
  #endif

  if (! timeout_action) { return TRUE ; }
 
  if (! play_folder_content ) {
   
    current_song_name = folder_music_playlist_container.at( music_song_counter ) ;
  } 
   
 
  libvlc_media_t *media ;

  media = libvlc_media_new_path(vlc_inst, current_song_name.c_str());
 
  if (media == NULL) {
   
    return TRUE ;
  }  
 
  libvlc_media_player_set_media(media_player, media);

  libvlc_media_player_play(media_player) ;

  libvlc_media_release(media);


  gtk_entry_set_text(GTK_ENTRY(gui->song_name_entry), g_path_get_basename(current_song_name.c_str()) ) ;

  if (gtk_entry_get_text(GTK_ENTRY(gui->song_name_entry)) == NULL) {
    // Sometimes it happend that surely due of timeout that the title entry stay empty: @BUGFIXED.
    gtk_entry_set_text(GTK_ENTRY(gui->song_name_entry), g_path_get_basename(current_song_name.c_str()) ) ;
  }
   

  timeout_action = false ;

  return TRUE ;

}