#ifndef MICRO_MUSIC_PLAYER_OTHER_CALLBACKS_HH
#define MICRO_MUSIC_PLAYER_OTHER_CALLBACKS_HH

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

#ifdef G_OS_UNIX
#ifndef MAC_INTEGRATION
// NOTE: In fact the possiblities offers by the GAppInfo API from Gio is not yet supported for Windows, we hope for progress.
extern void set_as_default_music_player(GtkWidget *widget, gpointer user_data) ;

extern void reset_associations(GtkWidget *widget, gpointer user_data) ;
#endif
#endif

extern void add_folder_to_recent_folder_list(const char *folderpath) ;

#endif