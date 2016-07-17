#ifndef MICRO_MUSIC_PLAYER_GUI_CONF_HH
#define MICRO_MUSIC_PLAYER_GUI_CONF_HH

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

#include "defines.h"

#include "global_vars.h"

// Program configuration callbacks.
extern void configure_high_contrast_radiobutton(GtkWidget *widget, Radio_Config *user_data) ;

extern void configure_oxygen_radiobutton(GtkWidget *widget, Radio_Config *user_data) ;

extern void repeat_all_feature_set(GtkToggleButton *togglebutton, gpointer user_data) ;

extern void shuffle_feature_set(GtkToggleButton *togglebutton, gpointer user_data) ;

extern void get_volume(GtkRange *range, gpointer user_data) ;

extern void reconfigure_interface_size(GtkWidget *widget, int *user_data) ;

extern void set_default_folder(GtkFileChooserButton *chooser, gpointer user_data) ;

extern void get_volume(GtkRange *range, gpointer user_data) ;

#endif