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

#include "shuffle.h"

bool is_end_of_shuffle_playlist() { return (music_song_counter == -1) ; }

void shuffle_playlist() {

  /** Shuffle the playlist indexes to get a precomputed shuffle playlist. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  if ( playlist_shuffle_indexes.empty() ) { return ; }

  random_device rd;

  mt19937 gen(rd());

  #ifdef INFO
  #if (INFO >= 2)
  fprintf(stdout,"\n%s: Mixing playlist %d times...\n", prgname.c_str(), RAND_ITERATIONS) ; fflush(stdout) ;
  #endif
  #endif

  for (int c=0 ; c < RAND_ITERATIONS ; c++) {

    // Mix shuffle list RAND_ITERATIONS times.

    shuffle(playlist_shuffle_indexes.begin(), playlist_shuffle_indexes.end(), gen) ;

  }

  // New order output...
  #ifdef INFO
  #if (INFO >= 3)
  for (int c=0 ; c < (int) playlist_shuffle_indexes.size() ; c++) {

    fprintf(stdout,"\n%s: Shuffle Playlist song N° %03d\n -> %s\n", prgname.c_str(), c+1, g_path_get_basename(folder_music_playlist_container.at(playlist_shuffle_indexes.at(c)).c_str()) ) ;

  }
  fprintf(stdout,"\n") ; fflush(stdout) ;
  #endif
  #endif

}

const int shuffle_get_song_index() {

  /** Return a new index to play and remove it from shuffle playlist. **/

  if ( playlist_shuffle_indexes.empty() ) { if (is_repeat_all) { playlist_shuffle_indexes = playlist_shuffle_back_up ; shuffle_playlist() ; } else { return -1 ; } }

  int ret = playlist_shuffle_indexes.back() ;

  playlist_shuffle_indexes.pop_back() ;

  playlist_shuffle_indexes.shrink_to_fit() ;

  return ret ;

}