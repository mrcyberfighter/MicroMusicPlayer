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


  MenuItem     *button_mode    ;

  MenuItem     *button_repeat_all  ;

  MenuItem     *button_repeat_one ;

  MenuItem     *button_repeat_off ;

  MenuItem     *button_shuffle ;



  MenuItem     *button_incr_vol ;

  MenuItem     *button_decr_vol ;


  // Menu files:
  GtkWidget    *menu_files   ;

  MenuItem     *menubutton_files ;

  MenuItem     *button_file    ;

  MenuItem     *button_folder    ;

  MenuItem     *button_recent    ;

  GtkWidget    *menu_recent   ;

  MenuItem     *show_playlist  ;



  // Menu configuration:
  GtkWidget    *menu_config   ;

  MenuItem     *menubutton_config ;

  MenuItem     *button_min_interface ;

  MenuItem     *button_theme_light ;

  MenuItem     *button_theme_dark  ;

  MenuItem     *button_icons_oxygen ;

  MenuItem     *button_icons_high_contrast ;

  MenuItem     *button_config  ;




  // Menu informations:
  GtkWidget    *menu_info      ;

  MenuItem     *menubutton_info ;

  MenuItem     *button_readme  ;

  MenuItem     *button_about   ;

  MenuItem     *button_quit    ;

} Menu ;




typedef struct {

  /** Playlist displaying structure. **/

  GtkWidget *playlist_displaying_dialog = NULL ;

  GtkWidget *playlist_listbox = NULL           ;

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

  GtkWidget *timeline_scale ;


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

  GtkWidget *min    ;

  #ifdef G_OS_UNIX
  GtkWidget *set_as_default     ;
  GtkWidget *reset_association  ;
  #endif

  GtkWidget *theme_light  ;
  GtkWidget *theme_dark   ;

} Radio_Config ;

typedef struct {

  /** Configure program settings structure. **/

  string path_to_button_icons   ;
  string path_to_menu_icons     ;

  string path_to_music_folder   ;

  string path_to_default_image  ;

  bool icon_set_oxygen          ;

  bool theme_light  ;


  int   is_repeat_all    ;

  bool is_shuffle       ;

  double volume         ;

  int    interface      ;

  int  image_resized_size ;

  int  space_buttons ;

  bool minimal_interface ;

  bool send_notification ;

} Settings ;



#endif