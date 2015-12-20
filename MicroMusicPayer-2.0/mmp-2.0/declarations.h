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

#ifndef MICRO_MUSIC_PLAYER_DECLARATIONS_HH
#define MICRO_MUSIC_PLAYER_DECLARATIONS_HH


int filtering_image(const struct dirent *dir_entry) ;
const bool sort_image_from_folder(const char *folderpath) ;
int filtering_music(const struct dirent *dir_entry) ;
const bool sort_music_from_folder(const char *folderpath) ;

// Search for a cover image and set it in the GUI.
void search_and_set_cover_image(const char *folderpath) ;

// Single music file selection checks.
const bool check_file_selection(const char *filepath) ;
const bool check_file(const char *filepath) ;

// Folder selection.
const bool parse_folder(const char *folderpath) ;

// Shuffle mode.
inline void shuffle_playlist() ;
inline const int shuffle_get_song_index() ;
inline bool is_end_of_shuffle_playlist() { return (music_song_counter == -1) ; }

// Playlist.
void update_playlist() ;
void build_playlist(GtkWidget *widget, gpointer user_data) ;

// Start playing playlist on folder load.
void start_playlist(void) ;

// timeout callback to play next song (outside from the event callback !).
bool timeout_update(void *user_data) ;

// File or folder selection dialogs.
void get_file_to_play(GtkWidget *widget, gpointer user_data)   ;
void get_folder_to_play(GtkWidget *widget, gpointer user_data) ;


// Muqsic playing controls calllbacks.
void prev_music(GtkWidget *widget, gpointer user_data)  ;
void play_music(GtkWidget *widget, gpointer user_data)  ;
void pause_music(GtkWidget *widget, gpointer user_data) ;
void next_music(GtkWidget *widget, gpointer user_data)  ;
void stop_music(GtkWidget *widget, gpointer user_data)  ;

// Extra features.
void repeat_all_music(GtkToggleButton *togglebutton, gpointer user_data) ;
void shuffle_music(GtkToggleButton *togglebutton, gpointer user_data)    ;
// Menu items callback.
void menu_repeat_all_music(GtkCheckMenuItem *togglebutton, gpointer user_data) ;
void menu_shuffle_music(GtkCheckMenuItem *togglebutton, gpointer user_data) ;

// Volume changing callback.
void change_volume(GtkScaleButton *button, gdouble value, gpointer user_data) ;

// Update current song per selection in playlist.
void selected_song(const int song_index) ;

// Song finished callback.
void following_song_hook(void) ;
// Song finished hook.
void music_finished_hook(const struct libvlc_event_t *event, void *data) ;


// Menu generating
void initialize_menu(Menu *menu) ;
void setup_menu_item(MenuItem *menuitem, const char type, const char *label, const char *accel_label, const char *image, GtkAccelGroup *menu_files_accel_group,  GdkModifierType accel_modifier,  guint accel_key) ;

// Reconfigure GUI icons.
void reset_image_widget(GtkWidget *image, const char *filepath) ;
void reconfigure_icon(GtkWidget *image, string filename, const bool is_button) ;
void reset_image_widget(GtkWidget *image, const char *filepath) ;
void reconfigure_interface_icons() ;

// Program configuration callbacks.
void configure_high_contrast_radiobutton(GtkWidget *widget, Radio_Config *user_data) ;
void configure_oxygen_radiobutton(GtkWidget *widget, Radio_Config *user_data) ;
void repeat_all_feature_set(GtkToggleButton *togglebutton, gpointer user_data) ;
void shuffle_feature_set(GtkToggleButton *togglebutton, gpointer user_data) ;
void get_volume(GtkRange *range, gpointer user_data) ;
void reconfigure_interface_size(GtkWidget *widget, int *user_data) ;
void set_default_folder(GtkFileChooserButton *chooser, gpointer user_data) ;

// Change icons set callbacks.
void configure_high_contrast_radiobutton(GtkWidget *widget, Radio_Config *user_data) ;
void configure_oxygen_radiobutton(GtkWidget *widget, Radio_Config *user_data)        ;

// Configure program callback.
void configure_program_dialog(GtkWidget *widget, gpointer user_data) ;

// Display a message window generating function.
void display_message_dialog(const char *title, const char *msg, GtkMessageType type = GTK_MESSAGE_ERROR, GtkButtonsType button_type = GTK_BUTTONS_CLOSE ) ;

// Display about window.
void display_about_dialog(GtkWidget *widget, gpointer *user_data) ;

// Launch display README.
void launch_readme_html(GtkWidget *widget, gpointer user_data) ;

// Quit application.
void destroy(GtkWidget *widget ,gpointer pointer) ;
gboolean delete_event(GtkWidget *widget,GdkEvent *event,gpointer pointer) ;

#endif