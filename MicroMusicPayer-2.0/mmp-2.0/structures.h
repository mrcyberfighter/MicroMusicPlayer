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

#ifndef MICRO_MUSIC_PLAYER_GUI_HH
#define MICRO_MUSIC_PLAYER_GUI_HH

typedef struct {

    /** Structure for one menu item. **/

    GtkWidget *image ;

    GtkWidget *label ;

    GtkWidget *accel_label ;

    GtkWidget *menuitem ;

    GtkWidget *hbox ;

} MenuItem ;

typedef struct {

  /** Main menu structure **/

  GtkWidget     *menu_bar      ;

  GtkAccelGroup *accel_group   ;

  GtkWidget    *menu_actions   ;

  MenuItem     *menubutton_actions ;

  MenuItem     *button_prev    ;
  MenuItem     *button_play    ;
  MenuItem     *button_pause   ;
  MenuItem     *button_next    ;
  MenuItem     *button_stop    ;

  GtkWidget    *separator_01   ;

  MenuItem     *button_mode    ;

  MenuItem     *button_repeat  ;
  MenuItem     *button_shuffle ;

  GtkWidget    *separator_02   ;

  MenuItem     *button_file    ;

  GtkWidget    *separator_03   ;

  MenuItem     *show_playlist  ;

  GtkWidget    *separator_04   ;

  MenuItem     *button_config  ;


  GtkWidget    *menu_info      ;

  MenuItem     *menubutton_info ;

  MenuItem     *button_readme  ;

  MenuItem     *button_about   ;

  GtkWidget    *separator_05   ;

  MenuItem     *button_quit    ;

} Menu ;




typedef struct {

  /** Playlist displaying structure. **/

  GtkWidget *playlist_displaying_dialog = NULL ;

  GtkWidget *playlist_listbox = NULL           ;

  GtkWidget *scrolled_window = NULL            ;

} Playlist ;


typedef struct {

  /** Main programm structure. **/

  GtkWidget *window ;

  GtkWidget *main_vbox ;

  GtkWidget *controls_buttonbox ;

  GtkWidget *button_prev    ;
  GtkWidget *button_play    ;
  GtkWidget *button_pause   ;
  GtkWidget *button_next    ;
  GtkWidget *button_stop    ;
  GtkWidget *button_repeat  ;
  GtkWidget *button_shuffle ;
  GtkWidget *button_volume  ;

  GtkWidget *button_prev_image    ;
  GtkWidget *button_play_image    ;
  GtkWidget *button_pause_image   ;
  GtkWidget *button_next_image    ;
  GtkWidget *button_stop_image    ;
  GtkWidget *button_repeat_image  ;
  GtkWidget *button_shuffle_image ;
  GtkWidget *button_volume_image  ;

  GtkWidget *button_volume_plus   ;
  GtkWidget *button_volume_minus  ;

  GtkWidget *button_volume_plus_image   ;
  GtkWidget *button_volume_minus_image  ;


  GtkWidget *image_container_hbox ;
  GtkWidget *image_container ;
  GtkWidget *image_widget ;


  GtkWidget *song_name_entry ;


  GtkWidget *folder_chooser_button ;


  GtkWidget *main_gui_notebook     ;


  GtkWidget *scrolled_window       ;

  Menu      *menu      ;

  Playlist  *playlist  ;

} GUI ;



typedef struct {

  /** Configure program structure. **/

  GtkWidget *volume ;
  GtkWidget *cancel ;
  GtkWidget *apply  ;


  GtkWidget *button ;
  GtkWidget *image  ;

  GtkWidget *little ;
  GtkWidget *middle ;
  GtkWidget *big    ;

} Radio_Config ;

typedef struct {

  /** Configure program settings structure. **/

  string path_to_button_icons   ;
  string path_to_menu_icons     ;

  string path_to_music_folder   ;

  string path_to_default_image  ;

  bool icon_set_oxygen          ;



  bool is_repeat_all    ;

  bool is_shuffle       ;

  double volume         ;

  int    interface      ;

  int  image_resized_size ;

  int  space_buttons ;

  int  display_size ;

} Settings ;



#endif