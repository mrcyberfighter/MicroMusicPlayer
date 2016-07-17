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

#include "folder_parsing.h"

vector<string>  folder_imaging_cover_container  ;  // Global images files container.

static void get_metadata(const char *folderpath, struct dirent **namelist, int number_of_entries) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif


  /** Retrieve all needed metadata and store them into vectors. **/

  // The paradox is the question to split this function into 3 (littler) but the call of
  // libvlc_media_parse_async justified so that isn't the case.

  uint16_t c = 0 ;

  while (c < number_of_entries) {

    string filepath(folderpath) ;

    filepath += "/" + string(namelist[c]->d_name) ;
  
    libvlc_media_t *media = libvlc_media_new_path(vlc_inst, filepath.c_str()) ;

    libvlc_media_get_user_data(media) ;

    // libvlc_media_parse(media) ;
    // We use the asynchrone function in synchrone manner
    // Because of being sure tro fetch local ressource not network ressource.
    libvlc_media_parse_async(media) ;

    while (not libvlc_media_is_parsed(media)) { /** Waiting the asynchrone call is done. **/ }


    // Get the URL from the **file** located in ~/.cache/vlc/art/... (cache).
    char *media_url = libvlc_media_get_meta(media, libvlc_meta_ArtworkURL) ;

    while (not libvlc_media_is_parsed(media)) { /** Waiting the asynchrone call is done. **/ }


    if (media_url != NULL) {

      // Cover found: we contruct a filepath from the URI...

      gchar *hostname ;

      gchar *filename_from_uri = g_filename_from_uri(media_url, &hostname, NULL) ;

      free(media_url) ;

      if (hostname != NULL) {
 
        g_free(hostname) ;
      }
    
      string cover_image_filepath ;

      if (filename_from_uri != NULL) {
       
        cover_image_filepath = filename_from_uri ;
       
        g_free(filename_from_uri) ;
      
        // Adding filepath to the container.
        imaging_cover_container.push_back(cover_image_filepath) ;

      }

    

    }
    else {

      // Cover not found in metadata: if their any in container we add this one again.

      if (! imaging_cover_container.empty()) {
     
        imaging_cover_container.push_back(imaging_cover_container.back()) ;

      }

    }


    // Getting song title.
    char *media_title = libvlc_media_get_meta(media, libvlc_meta_Title) ;

    while (not libvlc_media_is_parsed(media)) { /** Waiting the asynchrone call is done. **/ }

    // Getting song author.
    char *media_author = libvlc_media_get_meta(media, libvlc_meta_Artist) ;

    while (not libvlc_media_is_parsed(media)) { /** Waiting the asynchrone call is done. **/ }

    // We construct a string to resent to the user...
    string media_author_title ;

    if (media_author != NULL) {

      media_author_title = string(media_author) + " - " ;
    }

    if (media_title != NULL) {

      if (g_strcmp0(media_author, media_title) != 0) {

        media_author_title += string(media_title) ;
      }

      free(media_title) ;

    }

    if (media_author != NULL) {

      free(media_author) ;
    }

    if (! media_author_title.empty()) {

      title_author_container.push_back(media_author_title) ;

    }
    else {

      // Else if no author and title found we set the file basename to present to the user.

      gchar *file_basename = g_path_get_basename(filepath.c_str()) ;
    
      title_author_container.push_back(string(file_basename)) ;

      g_free(file_basename) ;
    }


    // Getting the Album name
    char *media_album = libvlc_media_get_meta(media, libvlc_meta_Album) ;

    while (not libvlc_media_is_parsed(media)) { /** Waiting the asynchrone call is done. **/ }

    if (media_album != NULL) {

      // We present the album name instead of the folder basename.
      //album_name = media_album  ;
      album_names_container.push_back(string(media_album)) ;

      free(media_album) ;

    }
    else {

      // Else we present the folder basename to the user.

      gchar *filepath_dirname = g_path_get_dirname(filepath.c_str()) ;

      gchar *filepath_basename = g_path_get_basename(filepath_dirname) ;

      album_names_container.push_back(string(filepath_basename)) ;

      g_free(filepath_dirname) ;

      g_free(filepath_basename) ;

    }



    libvlc_media_release(media) ;

    ++c ;

  }

  return ;

}

static void get_metadata(const string filepath) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif


  /** Retrieve all needed metadata and store them into vectors. **/

  // The paradox is the question to split this function into 3 (littler) but the call of
  // libvlc_media_parse_async justified so that isn't the case.

  libvlc_media_t *media = libvlc_media_new_path(vlc_inst, filepath.c_str()) ;

  //libvlc_media_parse(media) ;
  // We use the asynchrone function in synchrone manner
  // Because of being sure using local ressource not network.
  libvlc_media_parse_async(media) ;

  while (not libvlc_media_is_parsed(media)) { /** Waiting the asynchrone call is done. **/ }


  // Get the URL from the **file** located in ~/.cache/vlc/art/... (cache).
  char *media_url = libvlc_media_get_meta(media, libvlc_meta_ArtworkURL) ;

  while (not libvlc_media_is_parsed(media)) { /** Waiting the asynchrone call is done. **/ }


  if (media_url != NULL) {

    // Cover found: we contruct a filepath from the URI...

    gchar *hostname ;

    gchar *filename_from_uri = g_filename_from_uri(media_url, &hostname, NULL) ;

    free(media_url) ;

    if (hostname != NULL) {

      g_free(hostname) ;
    }

    string cover_image_filepath ;

    if (filename_from_uri != NULL) {

      cover_image_filepath = filename_from_uri ;
       
      g_free(filename_from_uri) ;
    
      // Adding filepath to the container.
      imaging_cover_container.push_back(cover_image_filepath) ;

    }

  }
  else {

    // Cover not found in metadata: if their any in container we add this one again.

    #ifdef DEBUG // TODO: removing
    fprintf(stdout,"Don't get the Artwork !!!\n") ;
    #endif

    if (! imaging_cover_container.empty()) {

      imaging_cover_container.push_back(imaging_cover_container.back()) ;

    }

  }


  // Getting song title.
  char *media_title = libvlc_media_get_meta(media, libvlc_meta_Title) ;

  while (not libvlc_media_is_parsed(media)) { /** Waiting the asynchrone call is done. **/ }

  // Getting song author.
  char *media_author = libvlc_media_get_meta(media, libvlc_meta_Artist) ;

  while (not libvlc_media_is_parsed(media)) { /** Waiting the asynchrone call is done. **/ }

  // We construct a string to resent to the user...
  string media_author_title ;

  if (media_author != NULL) {

    media_author_title += string(media_author) + " - " ;
  }

  if (media_title != NULL) {

    if (g_strcmp0(media_author, media_title) != 0) {

      media_author_title += string(media_title) ;
    }

    free(media_title) ;

  }

  if (media_author != NULL) {

    free(media_author) ;
  }

  if (! media_author_title.empty()) {

    title_author_container.push_back(media_author_title) ;

  }
  else {

    // Else if no author and title found we set the file basename to present to the user.

    char *file_basename = g_path_get_basename(filepath.c_str()) ;

    title_author_container.push_back(string(file_basename)) ;

    g_free(file_basename) ;
  }


  // Getting the Album name
  char *media_album = libvlc_media_get_meta(media, libvlc_meta_Album) ;

  while (not libvlc_media_is_parsed(media)) { /** Waiting the asynchrone call is done. **/ }

  if (media_album != NULL) {

    // We present the album name instead of the folder basename.
    //album_name = media_album  ;
    album_names_container.push_back(string(media_album)) ;

    free(media_album) ;

  }
  else {

    // Else we present the folder basename to the user.

    gchar *filepath_dirname = g_path_get_dirname(filepath.c_str()) ;

    gchar *filepath_basename = g_path_get_basename(filepath_dirname) ;

    album_names_container.push_back(string(filepath_basename)) ;

    g_free(filepath_dirname) ;

    g_free(filepath_basename) ;

  }



  libvlc_media_release(media) ;

  return ;

}

static int filtering_image(const struct dirent *dir_entry) {

  /** scandir callback for filtering directory.
    * @return 0 for not keeping folder entry.
    * @return 1 for keeping folder entry.
    *******************************************/

  if (g_file_test(dir_entry->d_name, G_FILE_TEST_IS_DIR) ) {
    /**  Reject directories. **/
    return 0 ;
  }

  string filepath(g_path_get_basename(dir_entry->d_name)) ;

  string filetype_check ;

  auto point_rpos =  filepath.rfind('.') ;

  if (point_rpos == string::npos) { return 0 ; }  /** No extension point "." found. **/

  const string extension = filepath.substr(point_rpos) ;

  string to_cmp ;

  for (auto val : extension) { to_cmp += tolower(val) ; }  /** Convert to lowercase for string comparison. **/

  if (to_cmp == ".") { return 0 ; }  /**  Find only the filename ending point. **/

  // Accept follwing files extension:
  else if (to_cmp == ".jpeg" || to_cmp == ".jpg" || to_cmp == ".jpe" || to_cmp == ".bmp" || to_cmp == ".dib" || to_cmp == ".png" || to_cmp == ".tif" || to_cmp == ".tiff") { return 1 ; }

  return 0 ;

}

static const bool sort_image_from_folder(const char *path) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  string dirpath ;

  if (! g_file_test(path, G_FILE_TEST_IS_DIR) ) {
    /** This is because the get_file_to_play() function give a filepath as argument. So not a @folderpath.    */

    char *dir_basename = g_path_get_dirname(path) ;

    dirpath = dir_basename ;

    g_free(dir_basename) ;

  }
  else {
    /** This is because the get_folder_to_play() function give a folderpath as argument. And not a @filepath. */
    dirpath = path ;
  }


  struct dirent **namelist ;

  // Scan the given directory in search of compatible images files, sort it with alphasort(). For cover image displaying.
  int number_of_entries = scandir(dirpath.c_str(), &namelist, filtering_image, alphasort) ;

  if (number_of_entries == 0) {

    #ifdef DEBUG
    fprintf(stdout,"\n%s: No image file found\n", prgname.c_str()) ;
    #endif

    free(namelist) ;

    return false ;  // Stop processing and signal failure to find any image file.
  }

  int c ;

  folder_imaging_cover_container.clear() ;

  for (c=0 ; c < number_of_entries ; c++) {

    // Construct filepath as string object:
    string filepath(dirpath.c_str())       ;
    filepath += "/"                       ;
    filepath +=  namelist[c]->d_name      ;

    // Pack into container:
    folder_imaging_cover_container.push_back(filepath)  ;

  }

  //free(directory_path) ;
  free(namelist) ;
  return true ;

}

static int filtering_music(const struct dirent *dir_entry) {

  /** scandir callback for filtering directory.
    * @return 0 for not keeping folder entry.
    * @return 1 for keeping folder entry.
    *******************************************/

  if (g_file_test(dir_entry->d_name, G_FILE_TEST_IS_DIR) ) {
    /**  Reject directories. **/
    return 0 ;
  }

  gchar *dir_basename = g_path_get_basename(dir_entry->d_name) ;

  string filepath(dir_basename) ;

  g_free(dir_basename) ;

  auto point_rpos =  filepath.rfind('.') ;

  if (point_rpos == string::npos) { return 0 ; } /** No extension point "." found. **/

  const string extension = filepath.substr(point_rpos) ;

  string to_cmp ;

  for (auto val : extension) { to_cmp += tolower(val) ; } /** Convert to lowercase for string comparison. **/

  if (to_cmp == ".") { return 0 ; } /**  Find only the filename ending point. **/

  // Accept follwing files extension:
  for (int c=0 ; c < static_cast<int>(extension_list.size()) ; c++) {

    string ext = extension_list.at(c) ;

    if ( to_cmp == ext.replace(0, 1,"")  ) {

      return 1 ;
    }


  }

  return 0 ;
}

static int filtering_music(const char *file) {

  /** scandir callback for filtering directory.
    * @return 0 for not keeping folder entry.
    * @return 1 for keeping folder entry.
    *******************************************/

  if (g_file_test(file, G_FILE_TEST_IS_DIR) ) {
    /**  Reject directories. **/
    return 0 ;
  }

  gchar *dir_basename = g_path_get_basename(file) ;

  string filepath(dir_basename) ;

  g_free(dir_basename) ;

  auto point_rpos =  filepath.rfind('.') ;

  if (point_rpos == string::npos) { return 0 ; } /** No extension point "." found. **/

  const string extension = filepath.substr(point_rpos) ;

  string to_cmp ;

  for (auto val : extension) { to_cmp += tolower(val) ; } /** Convert to lowercase for string comparison. **/

  if (to_cmp == ".") { return 0 ; } /**  Find only the filename ending point. **/

  // Accept follwing files extension:
  for (int c=0 ; c < static_cast<int>(extension_list.size()) ; c++) {

    string ext = extension_list.at(c) ;

    if ( to_cmp == ext.replace(0, 1,"")  ) {

      return 1 ;
    }


  }

  return 0 ;
}

static const bool sort_music_from_folder(const char *folderpath) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif


  struct dirent **namelist ;

  // Scan the given directory in search of compatible music files, sort it with alphasort().
  int number_of_entries = scandir(folderpath, &namelist, filtering_music, alphasort) ;

  if (number_of_entries == 0) {

    /** Don't find any valid file entry in folder. **/

    #ifdef DEBUG
    fprintf(stdout,"%s no songs found !\n", __func__) ;
    #endif

    free(namelist) ;

    return false ;  // Stop processing and signal failure to find any music file.
  }

  // Cleaning containers.
  playlist_shuffle_indexes.clear() ;
  playlist_shuffle_back_up.clear() ;
  folder_music_playlist_container.clear() ;

  imaging_cover_container.clear() ;
  title_author_container.clear()  ;
  album_names_container.clear()   ;

  /** From here we proces the files we find... **/

  for (int16_t c=0 ; c < number_of_entries ; c++) {

    /** Fill containers. **/

    // Construct filepath as string object:
    string filepath(folderpath)       ;
    filepath += "/"                       ;
    filepath += namelist[c]->d_name       ;

    #ifdef INFO
    #if (INFO >= 2)
    fprintf(stdout,"\n%s: Register song [%03d]\n -> %s\n", prgname.c_str(), c+1, g_path_get_basename(filepath.c_str()) ) ;
    #endif
    #endif

    // Pack into containers:
    folder_music_playlist_container.push_back(filepath) ;
    playlist_shuffle_indexes.push_back(c) ;

  }

  // Try to get the cover image(s).
  get_metadata(folderpath, namelist, number_of_entries) ;

  if ((folder_music_playlist_container.size() != imaging_cover_container.size()) && (imaging_cover_container.size() > 0)) {
 
    string cover_found = imaging_cover_container.at(0) ;
 
    imaging_cover_container.clear() ;
 
    fill(imaging_cover_container.begin(), imaging_cover_container.end(), cover_found) ;

  }

  playlist_shuffle_indexes.shrink_to_fit() ;
  playlist_shuffle_back_up.shrink_to_fit() ;
  folder_music_playlist_container.shrink_to_fit() ;

  imaging_cover_container.shrink_to_fit() ;
  title_author_container.shrink_to_fit()  ;
  album_names_container.shrink_to_fit()   ;


  #ifdef INFO
  #if (INFO >= 1)
  fflush(stdout) ;
  #endif
  #endif

  /** Shuffle feature support. **/
  shuffle_playlist() ;

  reverse(playlist_shuffle_indexes.begin(), playlist_shuffle_indexes.end()) ;

  playlist_shuffle_back_up = playlist_shuffle_indexes ;

  // Reset controls variables:
  music_song_counter=0 ;
  total_song_counter = number_of_entries ;

  // If shuffle feature enable get index of next song.
  if (is_shuffle) { music_song_counter = shuffle_get_song_index() ; }

  //current_song_name = folder_music_playlist_container.at( music_song_counter ) ;

  free(namelist) ;

  return true ; // Signal success folder parsing about music files.
}


void check_file_selection(const char *filepath) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  if (! filtering_music(filepath)) {

    return ;  // Ignore filetype checking error in case of file(s) selection.

  }

  // Add a single song to playlist container.
  string song = filepath ;

  folder_music_playlist_container.push_back(song) ;
  playlist_shuffle_indexes.push_back(music_song_counter++) ;

  // Try to get cover image and other metadatas.
  get_metadata(song) ;

  if ((folder_music_playlist_container.size() != imaging_cover_container.size()) && (imaging_cover_container.size() > 0)) {
 
    string cover_found = imaging_cover_container.at(0) ;
 
    imaging_cover_container.clear() ;
 
    fill(imaging_cover_container.begin(), imaging_cover_container.end(), cover_found) ;

  }

  return ; // Signal success file setting.
}

void search_and_set_cover_image(const char *folderpath) {

  /** Fallback cover image search and setting function if the metadata of the cover image doesn't exist. **/

  string image_selection = settings.path_to_default_image ;

  if (! sort_image_from_folder(folderpath) ) {

    #ifdef DEBUG
    fprintf(stderr,"\n%s Error collecting cover images list.\n", __func__) ; fflush(stderr) ;
    #endif

  }

  int max_width,  max_height ;

  max_width = max_height = 0 ;

  // Folder is soon parsed for image files so we search for the greatest one.
  for (int c =  0; c < (int) folder_imaging_cover_container.size() ; c++ ) {

      string image_iterator = folder_imaging_cover_container.at(c) ;

      GError *error = NULL ;

      GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(image_iterator.c_str(), &error);

      if (error != NULL) {

        continue ;
      }

      int width  = gdk_pixbuf_get_width(pixbuf)  ;
      int height = gdk_pixbuf_get_height(pixbuf) ;

      if ((width >= 96) && (height >= 96)) {

        string find_front ;

        int character = '\0' ;

        uint8_t cc = 0 ;

        while ( (character = g_path_get_basename(image_iterator.c_str())[cc]) != '\0') {

          find_front += (gchar) toupper(character) ;

          ++cc ;

        }

        /** Most used name component from front cover @not the back side of the CD image ! **/
        if ( (find_front.find("FRONT") != string::npos || find_front.find("FOLDER") != string::npos || find_front.find("COVER") != string::npos) && (find_front.find("SMALL") == string::npos) ) {
 
          // Find supposed front cover image.
          image_selection = image_iterator ;

          max_width=width ;
          max_height=height ;

          g_object_unref(pixbuf) ;
  
          break ;

        }

      }


      if ((width >= max_width ) && (height >= max_height)) {
        // Greater image found.
        max_width=width ;
        max_height=height ;
        image_selection = image_iterator ;

        #ifdef INFO
        #if (INFO >= 3)
        fprintf(stdout,"\n%s Image found in folder -> %s\n", prgname.c_str(), g_path_get_basename(image_iterator.c_str()) ) ; fflush(stdout) ;
        #endif
        #endif

      }

      g_object_unref(pixbuf) ;

  }


  imaging_cover_container.clear() ;
 
  imaging_cover_container.resize(folder_music_playlist_container.size(), image_selection) ;
 
  imaging_cover_container.shrink_to_fit() ;
 




}

const bool check_files(GSList *filepath_list) {

  /** Single file playing processing function. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  // Cleaning containers.
  playlist_shuffle_indexes.clear() ;
  playlist_shuffle_back_up.clear() ;
  folder_music_playlist_container.clear() ;

  imaging_cover_container.clear() ;
  title_author_container.clear()  ;
  album_names_container.clear()   ;

  // Reset controls variables:
  music_song_counter = 0 ;
  total_song_counter = 1 ;

  guint list_length = g_slist_length(filepath_list) ;

  for (guint c = 0 ; c < list_length ; ++c) {

    gchar *filepath = (gchar *) g_slist_nth_data(filepath_list, c) ;

    check_file_selection(filepath) ;

    g_free(filepath) ;

  }


  if (imaging_cover_container.size() == 0) {
    // Fallback cover images getting function.
    search_and_set_cover_image(current_folder.c_str()) ;
  }

  // Shrink containers size.
  playlist_shuffle_indexes.shrink_to_fit() ;
  playlist_shuffle_back_up.shrink_to_fit() ;
  folder_music_playlist_container.shrink_to_fit() ;

  imaging_cover_container.shrink_to_fit() ;
  title_author_container.shrink_to_fit()  ;
  album_names_container.shrink_to_fit()   ;

  // Reset controls variables:
  total_song_counter = music_song_counter ;
  music_song_counter = 0 ;

  // Shuffle feature support.
  playlist_shuffle_back_up = playlist_shuffle_indexes ;

  // Reset some control variables.
  set_pause(false) ;
  set_playing(false) ;
  set_stop(false) ;

  // Show play button and hide pause because they take the same place in the GUI.
  gtk_widget_hide(gui->button_pause) ;
  gtk_widget_show(gui->button_play)  ;

  at_start = true ;

  stop_music(NULL, NULL) ;
  // Start playing music.
  play_music(NULL, NULL) ;

  return true ;

}

const bool parse_folder(const char *folderpath) {

  /** Parse folder by folder selections. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  if (! sort_music_from_folder(folderpath) ) {

    string msg = "Failed to parse folder: " ;

    gchar *dir_basename = g_path_get_basename(folderpath) ;

    msg += dir_basename  ;

    g_free(dir_basename) ;

    msg += " \n\nDoes not found any playable compatible music file in folder !!!\n\nUnsupported filetype !" ;

    display_message_dialog("Error selected folder !", msg.c_str()) ;

    #ifdef DEBUG
    fprintf(stderr,"\n%s Error collecting song list.\n", __func__) ; fflush(stderr) ;
    #endif

    return false ;
  }

  if (imaging_cover_container.size() == 0) {
    // Fallback cover images getting function.
    search_and_set_cover_image(folderpath) ;
  }
  else {

    #ifdef INFO
    #if (INFO >= 1)
    fprintf(stdout,"\n%s: Use image file:\n -> %s\n", prgname.c_str(), imaging_cover_container.at(0).c_str() ) ; fflush(stdout) ;
    #endif
    #endif

  }

  // Reset some control variables.
  set_pause(false) ;
  set_playing(false) ;
  set_stop(false) ;

  // Show play button and hide pause because they take the same place in the GUI.
  gtk_widget_hide(gui->button_pause) ;
  gtk_widget_show(gui->button_play)  ;

  stop_music(NULL, NULL) ;
  // Start playing music.
  play_music(NULL, NULL) ;



  return true ;

}