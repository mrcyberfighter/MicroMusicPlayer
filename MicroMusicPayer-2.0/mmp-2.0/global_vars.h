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

#ifndef MICRO_MUSIC_PLAYER_GLOBAL_VARS_HH
#define MICRO_MUSIC_PLAYER_GLOBAL_VARS_HH


#include "Resizer.h"

// Music playing controls and features, controls variables.
bool is_playing  ;
bool is_stopped  ;
bool is_paused   ;

bool is_repeat_all  ;
bool is_shuffle     ;

bool play_order   ;

#define set_playing(x) ((is_playing)=x)
#define set_stop(x)    ((is_stopped)=(x))
#define set_pause(x)   ((is_paused)=x)

#define set_repeat(x)  ((is_repeat_all)=(x))
#define set_shuffle(x) ((is_shuffle)=(x))

#define set_order(x)   ((play_order)=(x))



bool is_show_playlist = false ;  // Determine if playlist displying window is currently displayed.

const string prgname = "Micro Music Player" ;  // Program name.


int music_song_counter = -1 ;  // Music container index.
int total_song_counter =  0 ;  // Music container size.



vector<int> playlist_shuffle_indexes ; // Music container for shuffle mode playing.
vector<int> playlist_shuffle_back_up ; // Needed for restoring, case of repeat all enable too, after all members from container above have been shifted away from pop_back().




vector<string>  folder_music_playlist_container ;  // Global music songs filepath container.

vector<string>  folder_imaging_cover_container  ;  // Global images files container.



string current_song_name  ;  // Current song name.


string current_folder ;  // Current folder name (selected from user).


string cover_image ; // Current cover image filepath.

string folder_basename  ;

bool play_folder_content = true ; // Distinguish from play a single file and folder mode.


Resizer resizer ; // Resizer instance needed for processing image resizing.

string image_cover_frame ; // cover filename.

libvlc_instance_t     *vlc_inst     = NULL ;
libvlc_media_player_t *media_player = NULL ;
libvlc_media_t        *media        = NULL ;

bool timeout_action = false ;
bool at_start       = true  ;

GUI pgui       ;  // Defintion because my GUI structure crach on some system if dynamic allocated .
GUI *gui=&pgui ;  // GUI pointer ;


Settings settings ; // User settings structure.


vector <string> extension_list = { "*.3ga", "*.669", "*.a52", "*.aac", "*.ac3", "*.adt", "*.adts", "*.aif", "*.aifc", "*.aiff", "*.amb", "*.amr", "*.aob", "*.ape", "*.au", "*.awb", "*.caf", "*.dts",
                                         "*.flac", "*.it", "*.kar", "*.m4a", "*.m4b", "*.m4p", "*.m5p", "*.mid","*.mka", "*.mlp", "*.mod", "*.mpa", "*.mp1", "*.mp2", "*.mp3", "*.mpc", "*.mpga", "*.mus",
                                         "*.oga","*.ogg", "*.oma","*.opus", "*.qcp", "*.ra","*.rmi", "*.s3m", "*.sid", "*.spx", "*.tak", "*.thd", "*.tta", "*.voc", "*.vqf", "*.w64", "*.wav", "*.wma",
                                         "*.wv", "*.xa","*.xm" } ;




#endif
