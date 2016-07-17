#ifndef MICRO_MUSIC_PLAYER_GUI_DIALOG_HH
#define MICRO_MUSIC_PLAYER_GUI_DIALOG_HH

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

#include "folder_parsing.h"

#include "gui_configuration.h"

// Display a message window generating function.
extern void display_message_dialog(const char *title, const char *msg, GtkMessageType type = GTK_MESSAGE_ERROR, GtkButtonsType button_type = GTK_BUTTONS_CLOSE ) ;

// Display about window.
extern void display_about_dialog(GtkWidget *widget, gpointer *user_data) ;

// Launch display README.
extern void launch_readme_html(GtkWidget *widget, gpointer user_data) ;

// File or folder selection dialogs.
extern void get_files_to_play(GtkWidget *widget, gpointer user_data)   ;
extern void get_folder_to_play(GtkWidget *widget, gpointer user_data) ;

// Configure program callback.
extern void configure_program_dialog(GtkWidget *widget, gpointer user_data) ;

#endif