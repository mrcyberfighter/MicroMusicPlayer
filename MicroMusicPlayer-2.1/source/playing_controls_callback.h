#ifndef MICRO_MUSIC_PLAYER_CONTROPS_HH
#define MICRO_MUSIC_PLAYER_CONTROLS_HH

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

#include "music_hooks.h"

#include "shuffle.h"

// Music playing controls calllbacks.
extern void prev_music(GtkWidget *widget, gpointer user_data)  ;
extern void play_music(GtkWidget *widget, gpointer user_data)  ;
extern void pause_music(GtkWidget *widget, gpointer user_data) ;
extern void next_music(GtkWidget *widget, gpointer user_data)  ;
extern void stop_music(GtkWidget *widget, gpointer user_data)  ;

// Extra features.
extern void repeat_all_music(GtkToggleButton *togglebutton, gpointer user_data) ;
extern void shuffle_music(GtkToggleButton *togglebutton, gpointer user_data)    ;
// Menu items callback.
extern void menu_repeat_all_music(GtkCheckMenuItem *togglebutton, gpointer user_data) ;
extern void menu_shuffle_music(GtkCheckMenuItem *togglebutton, gpointer user_data) ;

// Volume changing callback.
extern void change_volume(GtkScaleButton *button, gdouble value, gpointer user_data) ;

#endif
