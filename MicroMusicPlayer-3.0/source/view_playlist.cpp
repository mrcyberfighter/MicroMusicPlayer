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

static void destroy_playlist_window(GtkWidget *widget, gpointer pointer) ;

static gboolean delete_event_window_playlist(GtkWidget *widget,GdkEvent *event,gpointer pointer) ;


static void playlist_select_song(GtkListBox *listbox, GtkListBoxRow *row, gpointer user_data) {

  set_order(false) ;

  selected_song(gtk_list_box_row_get_index(row)) ;

}


void change_playlist(void) {

  if  (is_show_playlist) {

    gtk_widget_destroy(gui->playlist->playlist_displaying_dialog) ;

    build_playlist(NULL, NULL) ;

    return ;

  }

  return ;
}

void update_playlist(void) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  /** Update the playlist by every current song playing event if the play lits is displayed. **/

  if  (! is_show_playlist) {
    // Playlist is not actually displayed.
    return ;
  }


  // Else the playlist is actually displayed we process...


  // Remove the icon image from the playlist at position before the change.
  GtkListBoxRow *listbox_row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(gui->playlist->playlist_listbox), playlist_before_selection_idx) ;

  if (listbox_row != NULL) {

    GList *glist_of_listbox_row_childrens = gtk_container_get_children(GTK_CONTAINER(listbox_row)) ;

    if (glist_of_listbox_row_childrens != NULL) {

      if (glist_of_listbox_row_childrens->data != NULL) {
 
        GList *glist_of_listbox_row_sub_childrens = gtk_container_get_children(GTK_CONTAINER(glist_of_listbox_row_childrens->data)) ;
 
        GtkWidget *image_widget = (GtkWidget *) g_list_nth_data(glist_of_listbox_row_sub_childrens, 0) ;
 
        gchar *filepath = NULL ;
       
        g_object_get(G_OBJECT(image_widget), "file", &filepath, NULL) ;
   
        if (filepath != NULL) {
     
            gtk_image_clear(GTK_IMAGE(image_widget)) ;
     
            g_free(filepath) ;
     
          }
        }

    }
   
    g_list_free(glist_of_listbox_row_childrens) ;

  }  
 

  // Set the icon image from the playlist into the right row.
  listbox_row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(gui->playlist->playlist_listbox), music_song_counter) ;

  playlist_before_selection_idx = music_song_counter ;

  if (listbox_row != NULL) {

    gtk_list_box_select_row(GTK_LIST_BOX(gui->playlist->playlist_listbox), GTK_LIST_BOX_ROW(listbox_row)) ;

    GList *glist_of_listbox_row_childrens = gtk_container_get_children(GTK_CONTAINER(listbox_row)) ;

    if (glist_of_listbox_row_childrens != NULL) {

      if (glist_of_listbox_row_childrens->data != NULL) {
 
        GList *glist_of_listbox_row_sub_childrens = gtk_container_get_children(GTK_CONTAINER(glist_of_listbox_row_childrens->data)) ;
 
        GtkWidget *image_widget = (GtkWidget *) g_list_nth_data(glist_of_listbox_row_sub_childrens, 0) ;
 
        gtk_image_set_from_file(GTK_IMAGE(image_widget), (settings.path_to_menu_icons + "media-optical-audio.png" ).c_str() ) ;
      
      
      }

    }
   
    g_list_free(glist_of_listbox_row_childrens) ;

  }

  return ;

}



void build_playlist(GtkWidget *widget, gpointer user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  /** Generate playlist window by pressing menu item. **/

  if ( folder_music_playlist_container.empty() ) {

    // No current folder or file selection.
    #ifdef G_OS_UNIX
    display_message_dialog("No playlist found !", "No playlist found:\n\nYou must first select a folder or file(s) to play before to sea the playlist content.") ;
    #endif

    #ifdef G_OS_WIN32
    display_message_dialog("No playlist found !", "No playlist found:\n\nYou must first select music files to play\nbefore to sea the current playlist content.") ;
    #endif

    return ;
  }

  // Create Dialog window.
  gui->playlist->playlist_displaying_dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;

  gtk_window_set_icon_from_file(GTK_WINDOW(gui->playlist->playlist_displaying_dialog), PATH_TO_PRG_WIN_ICON, NULL) ;
  gtk_window_set_title(GTK_WINDOW(gui->playlist->playlist_displaying_dialog), "Playlist viewer and song selection:") ;
  gtk_window_set_position(GTK_WINDOW(gui->playlist->playlist_displaying_dialog), GTK_WIN_POS_CENTER_ALWAYS) ;
  gtk_window_set_resizable(GTK_WINDOW(gui->playlist->playlist_displaying_dialog), FALSE);
  gtk_widget_set_size_request(gui->playlist->playlist_displaying_dialog, -1, -1) ;
  gtk_window_set_decorated(GTK_WINDOW(gui->playlist->playlist_displaying_dialog), TRUE) ;
  gtk_window_set_type_hint(GTK_WINDOW(gui->playlist->playlist_displaying_dialog), GDK_WINDOW_TYPE_HINT_NORMAL) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui->playlist->playlist_displaying_dialog), 8) ;

  // Create ListBox widget for holding playlist datas.
  gui->playlist->playlist_listbox = gtk_list_box_new() ;
  gtk_list_box_set_selection_mode(GTK_LIST_BOX(gui->playlist->playlist_listbox), GTK_SELECTION_SINGLE) ;
  gtk_list_box_set_activate_on_single_click(GTK_LIST_BOX(gui->playlist->playlist_listbox),  FALSE);

  // Scrolled window if too much datas.
  GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL) ;

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

    gtk_widget_set_size_request(play_icon, 16, 16) ;

    g_object_set(G_OBJECT(play_icon), "margin-start", 8, NULL) ;

    // Trace the current song.
    bool is_current_song = false ;

    if ( c != music_song_counter) {

      // Not current song: need no icon only music filename

      gtk_label_set_text( GTK_LABEL(label_filename), g_path_get_basename(folder_music_playlist_container.at(c).c_str()) ) ;

    }
    else {

      // Current song: must set the icon at this row.

      is_current_song = true ; // Mark current song for later.

      gtk_image_set_from_file(GTK_IMAGE(play_icon), (settings.path_to_menu_icons + "media-optical-audio.png" ).c_str() ) ;

      gtk_label_set_text(GTK_LABEL(label_filename), g_path_get_basename(folder_music_playlist_container.at(c).c_str()) ) ;

      playlist_before_selection_idx = c ;

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

  gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrolled_window),  ((cols_space > 640) ? 640 : cols_space)  ) ;
  gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrolled_window), ((rows_space > 640) ? 640 : rows_space)  ) ;



  gtk_container_add(GTK_CONTAINER(scrolled_window), gui->playlist->playlist_listbox) ;

  gtk_container_add(GTK_CONTAINER(gui->playlist->playlist_displaying_dialog), scrolled_window) ;


  is_show_playlist = true ; // Variable for knowing if window currently displayed.

  // Connecting signals to callback.
  g_signal_connect(G_OBJECT(gui->playlist->playlist_listbox), "row-activated", G_CALLBACK(playlist_select_song), NULL) ;

  g_signal_connect(G_OBJECT(gui->playlist->playlist_displaying_dialog),"destroy",G_CALLBACK(destroy_playlist_window),NULL) ;

  g_signal_connect(G_OBJECT(gui->playlist->playlist_displaying_dialog),"delete-event",G_CALLBACK(delete_event_window_playlist),NULL) ;


  gtk_widget_show_all(gui->playlist->playlist_displaying_dialog) ;

}

static void destroy_playlist_window(GtkWidget *widget, gpointer pointer) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  is_show_playlist = false ;

  gtk_widget_destroy(gui->playlist->playlist_displaying_dialog) ;

  return ;

}

static gboolean delete_event_window_playlist(GtkWidget *widget,GdkEvent *event,gpointer pointer) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  #if 0
  if (event->type == GDK_DELETE) {


    #ifdef DEBUG
    fprintf(stdout,"%s delete_event catch\n",     __func__) ;
    #endif

    return FALSE ;
  }
  else {

    #ifdef DEBUG
    fprintf(stdout,"%s delete_event not catch\n", __func__) ;
    #endif

    return TRUE ;
  }
  #endif

  return FALSE ;

}