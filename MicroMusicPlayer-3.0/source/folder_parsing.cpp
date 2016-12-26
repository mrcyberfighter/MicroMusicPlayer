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

// Declaration of static functions:
static const bool filtering_image(const char *file) ;

static const bool filtering_music(const char *file) ;

static const bool sort_image_from_folder(const char *path) ;

static const bool sort_music_from_folder(const char *folderpath) ;

static inline void wait_for_metadatas(libvlc_media_t *media) ;

static void get_metadata(const string filepath) ;



// A local variable.
static vector<string>  folder_imaging_cover_container  ;  // Global images files container.




static const bool filtering_image(const char *file) {

  /** @return false or true, if the given file has an accepted extension. **/

  if (! g_file_test(file, G_FILE_TEST_IS_REGULAR) ) {

    return false ;
  }

  if (g_file_test(file, G_FILE_TEST_IS_DIR) ) {
    //  Reject directories.
    return false ;
  }

  char *file_basename = g_path_get_basename(file) ;

  string filepath(file_basename) ;

  g_free(file_basename) ;


  string to_cmp ;

  // Convert to lowercase for string comparison.
  transform(filepath.begin(), filepath.end(), back_inserter(to_cmp), [](char ch) { return tolower(ch) ; } ) ;


  // checking if filepath has a suffix which is a supported extension.
  for (auto &val : img_ext_list) {

    if ( g_str_has_suffix(to_cmp.c_str(), val.c_str())  ) {

      return true ;
    }
  }

  return false ;

}



static const bool filtering_music(const char *file) {

  /** Function used for testing if a file is a  valid music file.

      @return false or true, if the given file has an accepted extension.

  **/

  if (! g_file_test(file, G_FILE_TEST_IS_REGULAR) ) {
    // Reject non-regular files.
    return false ;
  }

  if (g_file_test(file, G_FILE_TEST_IS_DIR) ) {
    // Reject directories.
    return false ;
  }

  char *file_basename = g_path_get_basename(file) ;

  string filepath(file_basename) ;

  g_free(file_basename) ;

  string to_cmp ;

  // Convert to lowercase for string comparison.
  transform(filepath.begin(), filepath.end(), back_inserter(to_cmp), [](char ch) { return tolower(ch) ; } ) ;

  // Accept following files extension:
  for (auto val : extension_list) {

    if (g_str_has_suffix(to_cmp.c_str(), val.replace(0, 1,"").c_str()) ) {

      return true ;
    }


  }

  return false ;
}

static const bool sort_image_from_folder(const char *path) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  string dirpath = path ;

  // Scan the given directory in search of compatible images files. For cover image displaying.

  GError *error = NULL ;

  GDir *dir =  g_dir_open(dirpath.c_str(), 0, &error);

  if (error != NULL) {

    fprintf(stderr, "%s\n", error->message) ;
    g_error_free(error) ;

    return false ;

  }

  vector<string> namelist_song ;

  char *entry_name = NULL ;

  while ( (entry_name= (char *) g_dir_read_name(dir)) != NULL ) {

     char *filepath = g_strconcat(dirpath.c_str(), G_DIR_SEPARATOR_S, entry_name, NULL) ;

     if (filtering_image(filepath)) {

        folder_imaging_cover_container.push_back(string(filepath)) ;
     }

     g_free(filepath) ;
  }

  g_dir_close(dir) ;

  if (namelist_song.size() == 0) {

    return false ;

  }


  namelist_song.clear() ;
  return true ;

}



static const bool sort_music_from_folder(const char *folderpath) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  // Scan the given directory in search of compatible music files. Sort it with the C++ std::sort(...) alogorithm.

  GError *error = NULL ;

  GDir *dir =  g_dir_open(folderpath, 0, &error);

  if (error != NULL) {

    string msg = "Failed to open directory:\n" ;

    msg += error->message ;

    display_message_dialog("Error !", msg.c_str()) ;
    
    #ifdef DEBUG
    fprintf(stderr, "%s\n", error->message) ;
    #endif
      
    g_error_free(error) ;

    return false ;

  }

  vector<string> namelist_song ;

  char *entry_name = NULL ;


  // Record the (music or not) files into the directory by simply looping on the files, we gone check it out after...
  while ( (entry_name = (char *) g_dir_read_name(dir)) != NULL ) {

     gchar *filepath = g_strconcat(folderpath, G_DIR_SEPARATOR_S, entry_name, NULL) ;

     namelist_song.push_back(string(filepath)) ;

     g_free(filepath) ;
  }

  g_dir_close(dir) ;

  sort(namelist_song.begin(), namelist_song.end()) ;

  folder_imaging_cover_container.clear() ;


  // Clearing containers.
  playlist_shuffle_indexes.clear() ;
  playlist_shuffle_back_up.clear() ;
  folder_music_playlist_container.clear() ;

  imaging_cover_container.clear() ;
  title_author_container.clear()  ;
  album_names_container.clear()   ;
 
  #ifdef INTELLIGENT_RECENT_DISPLAY_NAME
  simple_author_container.clear() ;
  #endif

  if (not cover_image.empty()) {

    cover_image.clear() ;

  }

  /** From here we proces the files we find... **/

  for (unsigned int c=0 ; c < namelist_song.size() ; c++) {

    // Fill containers with filtering all the directory entries for compatible music files.

     if ( filtering_music(namelist_song.at(c).c_str()) ) {

        // Pack into containers:
        folder_music_playlist_container.push_back(namelist_song.at(c)) ;

        // Try to get the metadatas.
        get_metadata(namelist_song.at(c)) ;

        // Add shuffle index.
        playlist_shuffle_indexes.push_back(c) ;

     }



  }


  if (folder_music_playlist_container.empty()) {

    return false ;

  }

  string cover_found ;

  if ((folder_music_playlist_container.size() != imaging_cover_container.size()) && (imaging_cover_container.size() > 0)) {

    cover_found = imaging_cover_container.at(0) ;

  }

  if (! cover_found.empty()) {

    imaging_cover_container.clear() ;

    imaging_cover_container.resize( folder_music_playlist_container.size() ) ;

    fill(imaging_cover_container.begin(), imaging_cover_container.end(), cover_found) ;
  }

  playlist_shuffle_indexes.shrink_to_fit() ;
  playlist_shuffle_back_up.shrink_to_fit() ;
  folder_music_playlist_container.shrink_to_fit() ;

  imaging_cover_container.shrink_to_fit() ;
  title_author_container.shrink_to_fit()  ;
  album_names_container.shrink_to_fit()   ;

  if ( imaging_cover_container.size() > 0 ) {

    cover_image = imaging_cover_container.at(0) ;

  }

  #ifdef INFO
  #if (INFO >= 1)
  fflush(stdout) ;
  #endif
  #endif

  // Shuffle feature support.
  shuffle_playlist() ;

  reverse(playlist_shuffle_indexes.begin(), playlist_shuffle_indexes.end()) ;

  playlist_shuffle_back_up = playlist_shuffle_indexes ;

  // Reset controls variables:
  music_song_counter = 0 ;
  total_song_counter = folder_music_playlist_container.size() ;

  namelist_song.clear() ;

  return true ; // Signal success folder parsing about music files.
}

static inline void wait_for_metadatas(libvlc_media_t *media) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  // Synchronous call to get metadatas.
  libvlc_media_parse(media) ;

  while (not libvlc_media_is_parsed(media)) {

    /** Waiting... surely for nothing, because the condition seems to be wrong. But we never now. **/

  }

  return ;

}



static void get_metadata(const string filepath) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  /** Retrieve all needed metadata and store them into vectors. **/

  libvlc_media_t *media = libvlc_media_new_path(vlc_inst, filepath.c_str()) ;

  // Synchrone call to get metadatas.
  wait_for_metadatas(media) ;

  // Get the URL from the **file** located in ~/.cache/vlc/art/... (cache).
  char *media_url = libvlc_media_get_meta(media, libvlc_meta_ArtworkURL) ;


  if (media_url != NULL) {

    // Cover found: we contruct a filepath from the URI...

    gchar *hostname ;

    gchar *filename_from_uri = g_filename_from_uri(media_url, &hostname, NULL) ;

    free(media_url) ;

    if (hostname != NULL) {

      g_free(hostname) ;
    }



    if (filename_from_uri != NULL) {

      if (filtering_image(filename_from_uri) ) {

        // Adding filepath to the container.
        imaging_cover_container.push_back(string(filename_from_uri)) ;

      }

      g_free(filename_from_uri) ;

    }




  }
  else {

    // Cover not found in metadata: if their any in container we add this one again.

    #ifdef DEBUG
    fprintf(stdout,"Don't get the Artwork by metadatas !!!\n") ;
    #endif

    if (! imaging_cover_container.empty()) {

      imaging_cover_container.push_back(imaging_cover_container.back()) ;

    }

  }


  // Synchrone call to get metadatas.
  wait_for_metadatas(media) ;

  // Getting song title.
  char *media_title = libvlc_media_get_meta(media, libvlc_meta_Title) ;

  // Synchrone call to get metadatas.
  wait_for_metadatas(media) ;

  // Getting song author.
  char *media_author = libvlc_media_get_meta(media, libvlc_meta_Artist) ;


  // We construct a string to resent to the user...
  string media_author_title ;

  if (media_author != NULL) {

    media_author_title += string(media_author) + " - " ;
  
    #ifdef INTELLIGENT_RECENT_DISPLAY_NAME
    simple_author_container.push_back(media_author) ;
    #endif
 
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

  // Synchrone call to get metadatas.
  wait_for_metadatas(media) ;

  // Getting the Album name
  char *media_album = libvlc_media_get_meta(media, libvlc_meta_Album) ;

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


void set_cover_image(const string filepath) {

  /** Simply display the cobver image resized to current interface size. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  cover_image = filepath ;

  if (gui->image_widget != NULL) {

    g_object_ref(gui->image_widget) ;

    gtk_container_remove(GTK_CONTAINER(gui->image_container), gui->image_widget) ;

    gtk_image_clear(GTK_IMAGE(gui->image_widget)) ;

  }

  auto new_size = resizer.resizer(filepath, settings.image_resized_size, settings.image_resized_size, false) ;

  GError *error = NULL ;

  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filepath.c_str(), &error);



  if (error != NULL) {

    cover_image = settings.path_to_default_image ;

    gtk_image_set_from_file(GTK_IMAGE(gui->image_widget), settings.path_to_default_image.c_str() ) ;

    gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, 0, 0 ) ;

    fprintf(stderr,"Error loading image file:\n%s\n", error->message) ;

    g_error_free(error) ;

    error = NULL ;

    return ;

  }
 
  #if 0
  // Reserve for future usages !
  // No ratio keeping because of animations.
  GdkPixbuf *pixbuf_scaled = gdk_pixbuf_scale_simple(pixbuf,
                                                     settings.image_resized_size,
                                                     settings.image_resized_size,
                                                     GDK_INTERP_HYPER);


  #endif

  // Ration keeping resizing with the best interpolation.
  GdkPixbuf *pixbuf_scaled = gdk_pixbuf_scale_simple(pixbuf,
                                                     new_size.first,
                                                     new_size.second,
                                                     GDK_INTERP_HYPER);

  g_object_unref(pixbuf) ;

  gtk_image_set_from_pixbuf(GTK_IMAGE(gui->image_widget), pixbuf_scaled) ;

  g_object_unref(pixbuf_scaled) ;

  gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, (settings.image_resized_size-new_size.first)/2 ,  (settings.image_resized_size-new_size.second) /2 ) ;
 
  #if 0
  // Reserved for future usages !
  gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, 0 ,  0 ) ; // No ratio keeping this is for future usages...
  #endif

  return ;

}

void search_and_set_cover_image(const char *folderpath) {

  /** Fallback cover image search and setting function if the metadata of the cover image doesn't exist. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  string image_selection = settings.path_to_default_image ;

  if (! sort_image_from_folder(folderpath) ) {

    #ifdef DEBUG
    fprintf(stderr,"\n%s Error collecting cover images list.\n", __func__) ; fflush(stderr) ;
    #endif

  }

  int max_width,  max_height ;

  max_width = max_height = 0 ;

  // Folder is yet parsed for image files so we search for the best match according keyworks like "cover" or "front" and the best size.
  for (int c =  0; c < (int) folder_imaging_cover_container.size() ; c++ ) {


      if (! filtering_image(folder_imaging_cover_container.at(c).c_str()) ) {
        
        #ifdef DEBUG
        fprintf(stdout,"%s Wrong format !", __func__) ;
        #endif
        
        continue ;

      }

      string image_iterator = folder_imaging_cover_container.at(c) ;

      GError *error = NULL ;

      GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(image_iterator.c_str(), &error);

      if (error != NULL) {

        fprintf(stderr,"%s\n", error->message) ;

        g_error_free(error) ;

        error = NULL ;

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

        // Most used name component from front cover @not the back side of the CD image !!!
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
        fprintf(stdout,"\n%s Image found in folder -> %s\n", g_get_prgname(), g_path_get_basename(image_iterator.c_str()) ) ; fflush(stdout) ;
        #endif
        #endif

      }

      g_object_unref(pixbuf) ;

  }


  imaging_cover_container.clear() ;

  if (not cover_image.empty()) {

    cover_image.clear() ;

  }

  imaging_cover_container.resize(folder_music_playlist_container.size(), image_selection) ;

  imaging_cover_container.shrink_to_fit() ;

  cover_image = imaging_cover_container.at(0) ;



}


void check_file_selection(const char *filepath) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  if (! filtering_music(filepath)) {

    return ;  // Ignore not matching files in case by file(s) selection.

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

  total_song_counter = music_song_counter ;

  return ;
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
  #ifdef INTELLIGENT_RECENT_DISPLAY_NAME
  simple_author_container.clear() ;
  #endif

  // Reset controls variables:
  music_song_counter = 0 ;
  total_song_counter = 1 ;

  guint list_length = g_slist_length(filepath_list) ;

  for (guint c = 0 ; c < list_length ; ++c) {


    #ifdef G_OS_WIN32
    gchar *filepath = g_locale_to_utf8( (gchar *) g_slist_nth_data(filepath_list, c), strlen((gchar *) g_slist_nth_data(filepath_list, c)), NULL, NULL, NULL ) ;
    #endif

    #ifdef G_OS_UNIX
    gchar *filepath = (gchar *) g_slist_nth_data(filepath_list, c) ;
    #endif

    check_file_selection(filepath) ;

    g_free(filepath) ;

  }


  if (imaging_cover_container.size() == 0) {

    // Fallback cover images getting function.
    search_and_set_cover_image(current_folder.c_str()) ;
  }

  if (folder_music_playlist_container.size() == 0) {

    return false ;

  }


  // Shrink containers size.
  playlist_shuffle_indexes.shrink_to_fit() ;
  playlist_shuffle_back_up.shrink_to_fit() ;
  folder_music_playlist_container.shrink_to_fit() ;

  imaging_cover_container.shrink_to_fit() ;
  title_author_container.shrink_to_fit()  ;
  album_names_container.shrink_to_fit()   ;

  folder_imaging_cover_container.clear() ;

  if ( not imaging_cover_container.empty() ) {

    cover_image = imaging_cover_container.at(0) ;
  }

  // Reset controls variables:
  total_song_counter = music_song_counter ;
  music_song_counter = 0 ;
 
  // Shuffle feature support.
  shuffle_playlist() ;

  reverse(playlist_shuffle_indexes.begin(), playlist_shuffle_indexes.end()) ;

  playlist_shuffle_back_up = playlist_shuffle_indexes ;

  // Reset some control variables.
  set_pause(false) ;
  set_playing(false) ;
  set_stop(false) ;

  // Show play button and hide pause because they take the same place in the GUI.
  gtk_widget_hide(gui->button_pause) ;
  gtk_widget_show(gui->button_play)  ;

  at_start = true ;

  #ifdef G_OS_WIN32
  sort(folder_music_playlist_container.begin(), folder_music_playlist_container.end()) ;
  reverse(title_author_container.begin(), title_author_container.end()) ;
  sort(album_names_container.begin(), album_names_container.end()) ;
  #endif

  if (! cover_image.empty()) {

    set_cover_image( cover_image ) ;

  }


  imaging_cover_container.shrink_to_fit() ;
  title_author_container.shrink_to_fit()  ;
  album_names_container.shrink_to_fit()   ;


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
    
    if (dir_basename != NULL) {
      
      msg += dir_basename  ;
    
      g_free(dir_basename) ;
    
    }
      
    msg += " \n\nDoes not found any playable compatible music file in folder !!!" ;

    display_message_dialog("Error selected folder !", msg.c_str()) ;

    #ifdef DEBUG
    fprintf(stderr,"\n%s Error collecting song list.\n", __func__) ; fflush(stderr) ;
    #endif

    return false ;
  }

  if (imaging_cover_container.size() == 0) {
    // Using a fallback cover images getting function.
    search_and_set_cover_image(folderpath) ;
  }
  else {

    #ifdef INFO
    #if (INFO >= 1)
    fprintf(stdout,"\n%s: Use image file:\n -> %s\n", g_get_prgname(), imaging_cover_container.at(0).c_str() ) ; fflush(stdout) ;
    #endif
    #endif

  }

  if (! cover_image.empty()) {

    set_cover_image( cover_image ) ;

  }

  // Reset some control variables.
  set_pause(false) ;
  set_playing(false) ;
  set_stop(false) ;

  // Show play button and hide pause because they take the same place in the GUI.
  gtk_widget_hide(gui->button_pause) ;
  gtk_widget_show(gui->button_play)  ;

  return true ;

}
