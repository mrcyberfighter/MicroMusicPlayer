#ifndef MICRO_MUSIC_PLAYER_HOOKS_HH
#define MICRO_MUSIC_PLAYER_HOOKS_HH

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

#include "includes.h"

#include "global_vars.h"

#include "playing_controls_callback.h"

#include "shuffle.h"

#include "view_playlist.h"

// Update current song per selection in playlist.
extern void selected_song(const int song_index) ;

// timeout callback to play next song (outside from the event callback !).
extern bool timeout_update_media(void *user_data) ;

// timeout callback for the play a song timeline (duration progressbar).
extern bool timeout_timeline(void *user_data)  ;

// Song finished hook.
extern void music_finished_hook(const struct libvlc_event_t *event, void *data) ;

#endif