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

#include "./view_playlist.h"

static void row_selection_avoiding(GtkListBox *listbox, GtkListBoxRow *row, gpointer user_data) {

  selected_song(gtk_list_box_row_get_index(row)) ;

}


void update_playlist() {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif
 
  setlocale(LC_ALL, "") ;
 
  /** Update the playlist by every current song playing event if the play lits is displayed. **/

  if  (! is_show_playlist) {
    // Playlist is not actually displayed.
    return ;
  }

  // Else the playlist is actually displayed we process...

  // Destroy the dialog content and regenerate it: the playlist.
  gtk_widget_destroy(gui->scrolled_window) ;

  gui->scrolled_window            = gtk_scrolled_window_new(NULL, NULL) ;

  gui->playlist->playlist_listbox = gtk_list_box_new() ;

  // Configure playlist ListBox.
  gtk_list_box_set_selection_mode(GTK_LIST_BOX(gui->playlist->playlist_listbox), GTK_SELECTION_SINGLE) ;
  gtk_list_box_set_activate_on_single_click(GTK_LIST_BOX(gui->playlist->playlist_listbox),  FALSE);


  int max_song_name_length = 0 ;  // Variable for computing the size of the playlist window width.

  for (int c = 0 ; c < (int) folder_music_playlist_container.size() ; c++) {

    #ifdef DEBUG
    fprintf(stdout,"\nGenerate playlist item N %d\n -> %s\n", c+1, g_path_get_basename( folder_music_playlist_container.at(c).c_str() ) ) ;
    #endif

    // Format the song numbering label.
    gchar *number_fmt_str = g_strdup_printf("%3d", c+1) ;
    GtkWidget *label_number   = gtk_label_new( number_fmt_str ) ;
    g_free(number_fmt_str) ;

    gtk_label_set_width_chars( GTK_LABEL(label_number), 4) ;
    gtk_label_set_justify( GTK_LABEL(label_number), GTK_JUSTIFY_RIGHT) ;

    // Icon and fiel name widgets
    GtkWidget *play_icon      = gtk_image_new()     ;
    GtkWidget *label_filename = gtk_label_new(NULL) ;

    // Trace the current song.
    bool is_current_song = false ;

    if ( c != music_song_counter ||  (c == music_song_counter && is_stopped) ) {

      // Not current song: need no icon only music filename.

      gtk_image_set_pixel_size(GTK_IMAGE(play_icon), 16) ;

      gtk_label_set_text( GTK_LABEL(label_filename), g_path_get_basename(folder_music_playlist_container.at(c).c_str()) ) ;

    }
    else {

      // Current song: must set the icon at this row.

      is_current_song = true ; // Mark current song for later.

      gtk_image_set_from_file(GTK_IMAGE(play_icon), (settings.path_to_menu_icons + "applications-multimedia.png" ).c_str() ) ;

      gtk_label_set_text(GTK_LABEL(label_filename), g_path_get_basename(folder_music_playlist_container.at(c).c_str()) ) ;

    }

    if ( max_song_name_length < (int) strlen(g_path_get_basename(folder_music_playlist_container.at(c).c_str())) ) {
      // Compute max song name string length for window width size.
      max_song_name_length = (int) strlen(g_path_get_basename(folder_music_playlist_container.at(c).c_str())) ;

    }

    gtk_label_set_justify(GTK_LABEL(label_filename), GTK_JUSTIFY_LEFT ) ;


    GtkWidget *playlist_item_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

    gtk_box_pack_start(GTK_BOX(playlist_item_hbox), play_icon,        FALSE, FALSE, 0) ;
    gtk_box_pack_start(GTK_BOX(playlist_item_hbox), label_number,     FALSE, FALSE, 0) ;
    gtk_box_pack_start(GTK_BOX(playlist_item_hbox), label_filename,   FALSE, FALSE, 0) ;

    GtkWidget *row = gtk_list_box_row_new() ;

    gtk_container_add(GTK_CONTAINER(row), playlist_item_hbox ) ;

    if (is_current_song) {
      // Set row selected.
      gtk_list_box_select_row(GTK_LIST_BOX(gui->playlist->playlist_listbox), GTK_LIST_BOX_ROW(row)) ;
    }

    gtk_list_box_insert(GTK_LIST_BOX(gui->playlist->playlist_listbox), row,    c) ;

  }

  // Compute playlist window size.
  int rows_space = total_song_counter   *  27       ;
  int cols_space = max_song_name_length *  8  +  32 ;

  gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(gui->scrolled_window),  ((cols_space > 640) ? 640 : cols_space)  ) ;
  gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(gui->scrolled_window), ((rows_space > 640) ? 640 : rows_space)  ) ;

  g_signal_connect(G_OBJECT(gui->playlist->playlist_listbox), "row-activated", G_CALLBACK(row_selection_avoiding), NULL) ;

  gtk_container_add(GTK_CONTAINER(gui->scrolled_window), gui->playlist->playlist_listbox) ;

  gtk_widget_show_all(gui->scrolled_window) ;

  if ( gtk_widget_in_destruction(gui->playlist->playlist_displaying_dialog) ) {

    gui->playlist->playlist_displaying_dialog = gtk_dialog_new() ;

  }




  GtkWidget *content_area = gtk_dialog_get_content_area( GTK_DIALOG(gui->playlist->playlist_displaying_dialog) ) ;

  gtk_box_pack_start(GTK_BOX(content_area), gui->scrolled_window,  FALSE, FALSE, 0) ;

}



void build_playlist(GtkWidget *widget, gpointer user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  /** Generate playlist window by pressing menu item. **/

  if ( folder_music_playlist_container.empty() ) {
    // No current folder or file selection.
    display_message_dialog("No playlist found !", "No playlist found:\n\nYou must first select a folder to play before to sea the playlist content.") ;
    return ;
  }

  // Create Dialog window.
  gui->playlist->playlist_displaying_dialog = gtk_dialog_new() ;

  gtk_window_set_icon_from_file(GTK_WINDOW(gui->playlist->playlist_displaying_dialog), PATH_TO_PRG_WIN_ICON, NULL) ;
  gtk_window_set_title(GTK_WINDOW(gui->playlist->playlist_displaying_dialog), "Playlist viewer and song selection:") ;
  gtk_window_set_position(GTK_WINDOW(gui->playlist->playlist_displaying_dialog), GTK_WIN_POS_CENTER_ALWAYS) ;
  gtk_window_set_resizable(GTK_WINDOW(gui->playlist->playlist_displaying_dialog), FALSE);
  gtk_widget_set_size_request(gui->playlist->playlist_displaying_dialog, -1, -1) ;
  gtk_window_set_modal(GTK_WINDOW(gui->playlist->playlist_displaying_dialog), FALSE) ;
  gtk_window_set_destroy_with_parent(GTK_WINDOW(gui->playlist->playlist_displaying_dialog), TRUE) ;
  gtk_window_set_decorated(GTK_WINDOW(gui->playlist->playlist_displaying_dialog), TRUE) ;
  gtk_window_set_type_hint(GTK_WINDOW(gui->playlist->playlist_displaying_dialog), GDK_WINDOW_TYPE_HINT_NORMAL) ;
  gtk_window_set_transient_for(GTK_WINDOW(gui->playlist->playlist_displaying_dialog), GTK_WINDOW(gui->window)) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui->playlist->playlist_displaying_dialog), 8) ;

  // Create ListBox widget for holding playlist datas.
  gui->playlist->playlist_listbox = gtk_list_box_new() ;
  gtk_list_box_set_selection_mode(GTK_LIST_BOX(gui->playlist->playlist_listbox), GTK_SELECTION_SINGLE) ;
  gtk_list_box_set_activate_on_single_click(GTK_LIST_BOX(gui->playlist->playlist_listbox),  FALSE);
  // Scrolled window if too much datas.
  gui->scrolled_window = gtk_scrolled_window_new(NULL, NULL) ;

  int max_song_name_length = 0 ;  // Variable for computing the size of the playlist window width.

  for (int c = 0 ; c < (int) folder_music_playlist_container.size() ; c++) {

    #ifdef DEBUG
    fprintf(stdout,"\nGenerate playlist item N %d\n -> %s\n", c+1, g_path_get_basename( folder_music_playlist_container.at(c).c_str() ) ) ;
    #endif

    // Format the song numbering label.
    gchar *number_fmt_str = g_strdup_printf("%3d", c+1) ;
    GtkWidget *label_number   = gtk_label_new( number_fmt_str ) ;
    g_free(number_fmt_str) ;

    gtk_label_set_width_chars( GTK_LABEL(label_number), 4) ;
    gtk_label_set_justify( GTK_LABEL(label_number), GTK_JUSTIFY_RIGHT) ;

    // Icon and fiel name widgets
    GtkWidget *play_icon      = gtk_image_new()     ;
    GtkWidget *label_filename = gtk_label_new(NULL) ;

    // Trace the current song.
    bool is_current_song = false ;

    if ( c != music_song_counter) {

      // Not current song: need no icon only music filename.

      gtk_image_set_pixel_size(GTK_IMAGE(play_icon), 16) ;

      gtk_label_set_text( GTK_LABEL(label_filename), g_path_get_basename(folder_music_playlist_container.at(c).c_str()) ) ;

    }
    else {

      // Current song: must set the icon at this row.

      is_current_song = true ; // Mark current song for later.

      gtk_image_set_from_file(GTK_IMAGE(play_icon), (settings.path_to_menu_icons + "applications-multimedia.png" ).c_str() ) ;

      gtk_label_set_text(GTK_LABEL(label_filename), g_path_get_basename(folder_music_playlist_container.at(c).c_str()) ) ;

    }

    if ( max_song_name_length < (int) strlen(g_path_get_basename(folder_music_playlist_container.at(c).c_str())) ) {
      // Compute max song name string length for window width size.
      max_song_name_length = (int) strlen(g_path_get_basename(folder_music_playlist_container.at(c).c_str())) ;

    }


    gtk_label_set_justify( GTK_LABEL(label_filename), GTK_JUSTIFY_LEFT ) ;

    GtkWidget *playlist_item_hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

    gtk_box_pack_start(GTK_BOX(playlist_item_hbox), play_icon,        FALSE, FALSE, 0) ;
    gtk_box_pack_start(GTK_BOX(playlist_item_hbox), label_number,     FALSE, FALSE, 0) ;
    gtk_box_pack_start(GTK_BOX(playlist_item_hbox), label_filename,   FALSE, FALSE, 0) ;

    GtkWidget *row = gtk_list_box_row_new() ;

    gtk_container_add(GTK_CONTAINER(row), playlist_item_hbox ) ;

    if (is_current_song) {
      // Set row selected.
      gtk_list_box_select_row(GTK_LIST_BOX(gui->playlist->playlist_listbox), GTK_LIST_BOX_ROW(row)) ;
    }

    gtk_list_box_insert(GTK_LIST_BOX(gui->playlist->playlist_listbox), row,    c) ;

  }

  // Compute playlist window size.
  int rows_space = total_song_counter   *  27       ;
  int cols_space = max_song_name_length *  8  +  32 ;

  gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(gui->scrolled_window),  ((cols_space > 640) ? 640 : cols_space)  ) ;
  gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(gui->scrolled_window), ((rows_space > 640) ? 640 : rows_space)  ) ;

  g_signal_connect(G_OBJECT(gui->playlist->playlist_listbox), "row-activated", G_CALLBACK(row_selection_avoiding), NULL) ;

  gtk_container_add(GTK_CONTAINER(gui->scrolled_window), gui->playlist->playlist_listbox) ;

  gtk_widget_show_all(gui->scrolled_window) ;

  GtkWidget *content_area = gtk_dialog_get_content_area( GTK_DIALOG(gui->playlist->playlist_displaying_dialog) ) ;

  gtk_container_set_border_width(GTK_CONTAINER(content_area), 12) ;

  gtk_box_pack_start(GTK_BOX(content_area), gui->scrolled_window,  FALSE, FALSE, 0) ;

  gtk_widget_show_all(gui->playlist->playlist_displaying_dialog) ;

  is_show_playlist = true ; // Variable for knowing if window currently displayed.

  // Display dialog window and enter in window mainloop.
  gtk_dialog_run(GTK_DIALOG(gui->playlist->playlist_displaying_dialog) ) ;

  // After window displaying.
  gtk_widget_destroy(gui->playlist->playlist_displaying_dialog) ;

  is_show_playlist = false ; // After destoying window set on false.

}



