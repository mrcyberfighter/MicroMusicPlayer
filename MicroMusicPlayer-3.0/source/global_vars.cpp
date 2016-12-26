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

#include "global_vars.h"

// Music playing controls and features, controls variables.
bool is_playing  ;
bool is_stopped  ;
bool is_paused   ;

bool start_app = true ;

int  is_repeat_all  ;
bool is_shuffle     ;

bool play_order     ;

int playlist_before_selection_idx ;

bool is_show_playlist = false ;  // Determine if playlist displying window is currently displayed.


int music_song_counter = -1 ;  // Music container index.
int total_song_counter =  0 ;  // Music container size.



vector<int> playlist_shuffle_indexes ; // Music container for shuffle mode playing.
vector<int> playlist_shuffle_back_up ; // Needed for restoring, case of repeat all enable too, after all members from container above have been shifted away from pop_back().




vector<string> folder_music_playlist_container ;  // Global music songs filepath container.

vector<string> imaging_cover_container  ;
vector<string> title_author_container   ;
vector<string> album_names_container    ;
#ifdef INTELLIGENT_RECENT_DISPLAY_NAME
vector<string> simple_author_container  ;
#endif

double factor ;  // Computing duration factor.

string current_folder ;  // Current folder name (selected from user).


string cover_image ; // Current cover image filepath.


libvlc_instance_t     *vlc_inst     = NULL ;
libvlc_media_player_t *media_player = NULL ;
libvlc_media_t        *media        = NULL ;

bool timeout_action = false ;
bool at_start       = true  ;

int64_t duration_min ;
int64_t duration_sec ;

GUI pgui       ;  // Defintion because my GUI structure crach on some system if dynamic allocated .
GUI *gui=&pgui ;  // GUI pointer ;


Settings settings ; // User settings structure.

// Compatible music files extensions list.
vector<string> extension_list = { "*.3ga", "*.669", "*.a52", "*.aac", "*.ac3", "*.adt", "*.adts", "*.aif", "*.aifc", "*.aiff", "*.amb", "*.amr", "*.aob", "*.ape", "*.au", "*.awb", "*.caf", "*.dts",
                                  "*.flac", "*.it", "*.kar", "*.m4a", "*.m4b", "*.m4p", "*.m5p", "*.mid","*.mka", "*.mlp", "*.mod", "*.mpa", "*.mp1", "*.mp2", "*.mp3", "*.mpc", "*.mpga", "*.mus",
                                  "*.oga","*.ogg", "*.oma","*.opus", "*.qcp", "*.ra","*.rmi", "*.s3m", "*.sid", "*.spx", "*.tak", "*.thd", "*.tta", "*.voc", "*.vqf", "*.w64", "*.wav", "*.wma",
                                  "*.wv", "*.xa","*.xm" } ;

vector<const char *> mimetype_list = {
                                        "audio/aac",
                                        "audio/ac3",
                                        "audio/amr",            // amr
                                        "audio/amr-wb",         // awb
                                        "audio/basic",          // au snd
                                        "audio/flac",           // flac
                                        "audio/midi",           // midi
                                        "audio/mpeg",           // mpga mpega mp2 mp3 m4a
                                        "audio/mp2",
                                        "audio/mp4",
                                        "audio/ogg",            // oga ogg opus spx
                                        "audio/x-aifc"
                                        "audio/x-aiff",
                                        "audio/x-ape",
                                        "audio/x-flac+ogg",
                                        "audio/x-it",
                                        "audio/x-m4b",
                                        "audio/x-mod",
                                        "audio/x-ms-wma",       // wma
                                        "audio/x-opus+ogg",
                                        "audio/x-s3m",
                                        "audio/x-voc",
                                        "audio/x-vorbis+ogg",
                                        "audio/x-wav",
                                        "audio/x-aiff",         // aif aiff aifc
                                        "audio/x-realaudio",    // ra
                                        "audio/x-wav",          // wma
                                        "audio/x-flac"
                                         } ;      // And more but mimetype not found.


static vector<string> init_img_ext_list(void) {

  vector<string> ret ;

  GSList *gdk_formats = gdk_pixbuf_get_formats() ;

  gdk_formats = g_slist_nth(gdk_formats, 0) ;

  while (gdk_formats != NULL) {

    if (gdk_formats->data != NULL) {

      char **ext_list = gdk_pixbuf_format_get_extensions( (GdkPixbufFormat*) gdk_formats->data) ;

      int c = 0 ;

      while (ext_list[c] != NULL) {

        ret.push_back( (string(".") + string(ext_list[c])) ) ;

        ++c ;
      }

      g_strfreev(ext_list) ;

      if (gdk_formats->next != NULL) {

        gdk_formats = gdk_formats->next ;
      }
      else {

        break ;
      }

    }
  }

  g_slist_free(gdk_formats) ;

  return ret ;
}


// Accept following files extension: they supported by <gdk-pixbuf>.
vector<string> img_ext_list = init_img_ext_list() ;

GtkApplication *app=NULL ;

GRecMutex mainloop_ctrl_rec_mutex  ;

Resizer resizer ;

#ifdef G_OS_WIN32

#define PRGNAME "MicroMusicPlayer"

char *PREFIX_PRG = g_win32_get_package_installation_directory_of_module(NULL) ;

char *PATH_TO_MENU_UI_FILE = g_build_path(G_DIR_SEPARATOR_S, PREFIX_PRG, "share\\" PRGNAME "\\" "Configuration\\", NULL)  ;

char *PATH_TO_ICONS = g_build_path(G_DIR_SEPARATOR_S, PREFIX_PRG, "share\\" PRGNAME "\\" "images\\icons\\", NULL)  ;

char *PATH_TO_IMAGE = g_build_path(G_DIR_SEPARATOR_S, PREFIX_PRG, "share\\" PRGNAME "\\" "images\\images\\", NULL) ;

char *PATH_TO_HIGH_CONTRAST_BUTTON_ICONS = g_build_path(G_DIR_SEPARATOR_S, PREFIX_PRG, "share\\" PRGNAME "\\" "images\\icons\\" "high-contrast\\" "22x22\\", NULL)  ;
char *PATH_TO_HIGH_CONTRAST_MENU_ICONS   = g_build_path(G_DIR_SEPARATOR_S, PREFIX_PRG, "share\\" PRGNAME "\\" "images\\icons\\" "high-contrast\\" "16x16\\", NULL)  ;


char *PATH_TO_OXYGEN_BUTTON_ICONS = g_build_path(G_DIR_SEPARATOR_S, PREFIX_PRG, "share\\" PRGNAME "\\" "images\\icons\\" "oxygen\\" "22x22\\", NULL)  ;

char *PATH_TO_OXYGEN_MENU_ICONS   = g_build_path(G_DIR_SEPARATOR_S, PREFIX_PRG, "share\\" PRGNAME "\\" "images\\icons\\" "oxygen\\" "16x16\\", NULL)  ;

char *PATH_TO_GPLV3 = g_build_path(G_DIR_SEPARATOR_S, PREFIX_PRG, "share\\" PRGNAME "\\" "License\\GPLv3.txt", NULL) ;

char *PATH_TO_README = g_build_path(G_DIR_SEPARATOR_S, PREFIX_PRG, "share", PRGNAME, "README", "README", "README.html", NULL) ;

char *PATH_TO_PRG_IMAGE_LITTLE = g_build_path(G_DIR_SEPARATOR_S, PREFIX_PRG, "share\\" PRGNAME "\\"  "images\\images\\" "Micro_Music_Player_256.png", NULL) ;
char *PATH_TO_PRG_IMAGE_MIDDLE = g_build_path(G_DIR_SEPARATOR_S, PREFIX_PRG, "share\\" PRGNAME "\\"  "images\\images\\" "Micro_Music_Player_288.png", NULL) ;
char *PATH_TO_PRG_IMAGE_BIG    = g_build_path(G_DIR_SEPARATOR_S, PREFIX_PRG, "share\\" PRGNAME "\\"  "images\\images\\" "Micro_Music_Player_320.png", NULL) ;

char *PATH_TO_PRG_ICON = g_build_path(G_DIR_SEPARATOR_S, PREFIX_PRG, "share\\" PRGNAME "\\"  "images\\images\\" "Micro_Music_Player_256.png", NULL) ;

char *PATH_TO_PRG_WIN_ICON = g_build_path(G_DIR_SEPARATOR_S, PREFIX_PRG, "share\\" PRGNAME "\\"  "images\\images\\" "preferences-desktop-sound.png", NULL) ;

char *PATH_TO_CONF_FILE = g_build_path(G_DIR_SEPARATOR_S, g_get_home_dir(), "AppData", "Roaming", "mmp", "micro-music-player.conf", NULL)  ;

#endif
