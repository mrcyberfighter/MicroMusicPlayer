#ifndef MICRO_MUSIC_PLAYER_GLOBAL_VARS_HH
#define MICRO_MUSIC_PLAYER_GLOBAL_VARS_HH

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


#include "structures.h"

#include "Resizer.h"

// Music playing controls and features, controls variables.
extern bool is_playing  ;
extern bool is_stopped  ;
extern bool is_paused   ;

extern int  is_repeat_all  ;
extern bool is_shuffle     ;

extern bool play_order   ;

#define set_playing(x) ((is_playing)=x)
#define set_stop(x)    ((is_stopped)=(x))
#define set_pause(x)   ((is_paused)=x)

#define set_repeat(x)  ((is_repeat_all)=(x))
#define set_shuffle(x) ((is_shuffle)=(x))

#define set_order(x)   ((play_order)=(x))



extern int playlist_before_selection_idx ;

extern bool is_show_playlist ;  // Determine if playlist displying window is currently displayed.

extern bool start_app ;

extern int music_song_counter ;  // Music container index.
extern int total_song_counter ;  // Music container size.



extern vector<int> playlist_shuffle_indexes ; // Music container for shuffle mode playing.
extern vector<int> playlist_shuffle_back_up ; // Needed for restoring, case of repeat all enable too, after all members from container above have been shifted away from pop_back().




extern vector<string>  folder_music_playlist_container ;  // Global music songs filepath container.



extern vector<string> imaging_cover_container  ;  
extern vector<string> title_author_container   ;
extern vector<string> album_names_container    ;  
#ifdef INTELLIGENT_RECENT_DISPLAY_NAME
extern vector<string> simple_author_container  ;
#endif

extern double factor ;  // Computing duration factor.

extern string current_folder ;  // Current folder name (selected from user).


extern string cover_image ; // Current cover image filepath.


extern libvlc_instance_t     *vlc_inst     ;
extern libvlc_media_player_t *media_player ;
extern libvlc_media_t        *media        ;

extern bool timeout_action ;
extern bool at_start       ;

extern int64_t duration_min ;
extern int64_t duration_sec ;

extern GUI *gui ;  // GUI pointer ;


extern Settings settings ; // User settings structure.


extern vector<string> extension_list ;

extern vector<const char *> mimetype_list ;

//#ifdef G_OS_UNIX
extern vector<string> img_ext_list ;  // Accept following files extension: they supported by <gdk-pixbuf>.
//#endif

extern GtkApplication *app ;

extern GRecMutex mainloop_ctrl_rec_mutex ;

extern Resizer resizer ;

#ifdef G_OS_WIN32

extern char *PATH_TO_CONF_FILE ;

extern char *PATH_TO_MENU_UI_FILE ;

extern char *PATH_TO_ICONS ;

extern char *PATH_TO_IMAGE ;

extern char *PATH_TO_PRG_IMAGE_LITTLE ;
extern char *PATH_TO_PRG_IMAGE_MIDDLE ;
extern char *PATH_TO_PRG_IMAGE_BIG    ;

extern char *PATH_TO_HIGH_CONTRAST_BUTTON_ICONS ;
extern char *PATH_TO_HIGH_CONTRAST_MENU_ICONS ;

extern char *PATH_TO_OXYGEN_BUTTON_ICONS ;
extern char *PATH_TO_OXYGEN_MENU_ICONS ;

extern char *PATH_TO_GPLV3 ;

extern char *PATH_TO_README ;

extern char *PATH_TO_PRG_ICON ;

extern char *PATH_TO_PRG_WIN_ICON ;

#endif



#endif