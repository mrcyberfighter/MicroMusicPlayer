#ifndef MICRO_MUSIC_PLAYER_FOLDER_PARSING_HH
#define MICRO_MUSIC_PLAYER_FOLDER_PARSING_HH

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

#include "dialogs.h"

#include "playing_controls_callback.h"

#include "shuffle.h"

// Music comptatible filetype check.
extern void check_file_selection(const char *filepath) ;

extern const bool check_files(GSList *filepath_list) ;

// Folder selection.
extern const bool parse_folder(const char *folderpath) ;

// Search for a cover image and set it in the GUI.
extern void search_and_set_cover_image(const char *folderpath) ;

#endif