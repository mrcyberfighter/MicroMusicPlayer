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

int filtering_image(const struct dirent *dir_entry) {

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

const bool sort_image_from_folder(const char *path) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  string dirpath ;

  if (! g_file_test(path, G_FILE_TEST_IS_DIR) ) {
    /** This is because the get_file_to_play() function give a filepath as argument. So not a @folderpath.    */
    dirpath = g_path_get_dirname(path) ;
  }
  else {
    /** This is because the get_folder_to_play() function give a folderpath as argument. And not a @filepath. */
    dirpath = path ;
  }

  DIR *directory = opendir(dirpath.c_str()) ;

  if (directory == NULL) {
    #ifdef DEBUG
    perror("Open dir error: ") ; // Silent error because it can display the default image if it fail no need to alarm the user.
    #endif
    return false ;
  }

  char *directory_path ;

  if ((directory_path = realpath(dirpath.c_str(), NULL) ) == NULL ) {

    #ifdef DEBUG
    perror("directory resolving error: ") ;
    #endif
    return false ;
  }

  struct dirent **namelist ;

  // Scan the given directory in search of compatible images files, sort it with alphasort(). For cover image displaying.
  int number_of_entries = scandir(directory_path, &namelist, filtering_image, alphasort) ;

  if (number_of_entries == 0) {

    #ifdef DEBUG
    fprintf(stdout,"\n%s: No image file found\n", prgname.c_str()) ;
    #endif

    free(directory_path) ;
    free(namelist) ;

    return false ;  // Stop processing and signal failure to find any image file.
  }

  int c ;

  for (c=0 ; c < number_of_entries ; c++) {

    // Construct filepath as string object:
    string filepath(directory_path)       ;
    filepath += "/"                       ;
    filepath +=  namelist[c]->d_name      ;

    // Pack into container:
    folder_imaging_cover_container.push_back(filepath)  ;

  }

  free(directory_path) ;
  free(namelist) ;
  return true ;

}

int filtering_music(const struct dirent *dir_entry) {

  /** scandir callback for filtering directory.
    * @return 0 for not keeping folder entry.
    * @return 1 for keeping folder entry.
    *******************************************/

  if (g_file_test(dir_entry->d_name, G_FILE_TEST_IS_DIR) ) {
    /**  Reject directories. **/
    return 0 ;
  }


  string filepath(g_path_get_basename(dir_entry->d_name)) ;

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

const bool sort_music_from_folder(const char *folderpath) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  DIR *directory = opendir(folderpath) ;

  if (directory == NULL) {
    #ifdef DEBUG
    perror("Open dir error: ") ; // Silent error the program cannot open the folder, we are fucked .
    #endif
    return false ;
  }


  char *directory_path ;

  if ((directory_path = realpath(folderpath, NULL) ) == NULL ) {

    #ifdef DEBUG
    perror("directory resolving error: ") ; // Silent error the program cannot get the absolute path, we are fucked .
    #endif
    return false ;
  }



  struct dirent **namelist ;

  // Scan the given directory in search of compatible music files, sort it with alphasort().
  int number_of_entries = scandir(directory_path, &namelist, filtering_music, alphasort) ;

  if (number_of_entries == 0) {

    /** Don't find any valid file entry in folder. **/

    #ifdef DEBUG
    fprintf(stdout,"%s no songs found !\n", __func__) ;
    #endif

    free(directory_path) ;
    free(namelist) ;

    return false ;  // Stop processing and signal failure to find any music file.
  }

  /** From here we proces the files we find... **/

  // Cleaning containers.
  playlist_shuffle_indexes.clear() ;
  playlist_shuffle_indexes.shrink_to_fit() ;

  playlist_shuffle_back_up.clear() ;
  playlist_shuffle_back_up.shrink_to_fit() ;

  folder_music_playlist_container.clear() ;
  folder_music_playlist_container.shrink_to_fit() ;


  int c ;

  for (c=0 ; c < number_of_entries ; c++) {

    /** Fill containers. **/

    // Construct filepath as string object:
    string filepath(directory_path)       ;
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

  #ifdef INFO
  #if (INFO >= 2)
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

  // Clear and set current song.
  current_song_name.clear() ;
  current_song_name.shrink_to_fit() ;

  // If shuffle feature enable get index of next song.
  if (is_shuffle) { music_song_counter = shuffle_get_song_index() ; }

  current_song_name = folder_music_playlist_container.at( music_song_counter ) ;

  free(directory_path) ;
  free(namelist) ;

  return true ; // Signal success folder parsing about music files.
}


const bool check_file_selection(const char *filepath) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  if (filepath == NULL) {
    #ifdef DEBUG
    perror("Open file error: ") ; // Silent error the program cannot open the directory.
    #endif
    return false ;

  }




  /** From here we proces the files we find... **/

  // Cleaning containers.
  playlist_shuffle_indexes.clear() ;
  playlist_shuffle_indexes.shrink_to_fit() ;

  playlist_shuffle_back_up.clear() ;
  playlist_shuffle_back_up.shrink_to_fit() ;

  folder_music_playlist_container.clear() ;
  folder_music_playlist_container.shrink_to_fit() ;

  // Add a single song to playlist container.
  string song = filepath ;

  folder_music_playlist_container.push_back(song) ;
  playlist_shuffle_indexes.push_back(0) ;


  /** Shuffle feature support. Don't needed by a single file. but we must copy the signle file. **/
  playlist_shuffle_back_up = playlist_shuffle_indexes ;

  // Reset controls variables:
  music_song_counter = 0 ;
  total_song_counter = 1 ;

  // Clear and set current song.
  current_song_name.clear() ;
  current_song_name.shrink_to_fit() ;

  current_song_name = folder_music_playlist_container.at( music_song_counter ) ;

  at_start = true ;
  
  if (libvlc_media_player_is_playing(media_player)) {
    libvlc_media_player_stop(media_player) ;
  }
 
  //stop_music(NULL, NULL) ;
  // Start playing music.
  play_music(NULL, NULL) ;

  return true ; // Signal success file setting.
}

void search_and_set_cover_image(const char *folderpath) {

  string image_selection = settings.path_to_default_image ;

  if (! sort_image_from_folder(folderpath) ) {

    #ifdef DEBUG
    fprintf(stderr,"\n%s Error collecting images list.\n", __func__) ; fflush(stderr) ;
    #endif

    goto set_default_image ;

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

      if ((width >= max_width ) && (height >= max_height) ) {
        // Greater image found.
        max_width=width ;
        max_height=height ;
        image_selection = image_iterator ;
        image_cover_frame = image_iterator ;

        #ifdef INFO
        #if (INFO >= 3)
        fprintf(stdout,"\n%s Image found in folder -> %s\n", prgname.c_str(), g_path_get_basename(image_iterator.c_str()) ) ; fflush(stdout) ;
        #endif
        #endif

      }

  }


  if ( image_selection != settings.path_to_default_image ) {

    #ifdef INFO
    #if (INFO >= 1)
    fprintf(stdout,"\n%s: Use image file:\n -> %s\n", prgname.c_str(), image_selection.c_str() ) ; fflush(stdout) ;
    #endif
    #endif

    cover_image = image_selection ;

    if (gui->image_widget != NULL) {

      g_object_ref(gui->image_widget) ;

      gtk_container_remove(GTK_CONTAINER(gui->image_container), gui->image_widget) ;

      gtk_image_clear(GTK_IMAGE(gui->image_widget)) ;

    }


    GError *error = NULL ;

    auto new_size = resizer.resizer(image_cover_frame, settings.image_resized_size, settings.image_resized_size, false) ;
  
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(image_cover_frame.c_str(), &error);



    if (error != NULL) {
      cover_image = settings.path_to_default_image ;

      gtk_image_set_from_file(GTK_IMAGE(gui->image_widget), settings.path_to_default_image.c_str() ) ;

      gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, (settings.display_size - settings.image_resized_size) / 2, (settings.display_size - settings.image_resized_size)  / 2 ) ;

    }
    else {
  
      GdkPixbuf *pixbuf_scaled = gdk_pixbuf_scale_simple(pixbuf,
                                                         new_size.first,
                                                         new_size.second,
                                                         GDK_INTERP_NEAREST);
  
  
  
  
  
      gtk_image_set_from_pixbuf(GTK_IMAGE(gui->image_widget), pixbuf_scaled) ;
  
      gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, (settings.display_size-new_size.first)/2 ,  (settings.display_size-new_size.second) /2 ) ;

    }

 }
 else {

    set_default_image :

    #ifdef INFO
    #if (INFO >= 1)
    fprintf(stdout,"\n%s: No matching images found in folder -> use default image.\n", prgname.c_str() ) ; fflush(stdout) ;
    #endif
    #endif

    cover_image = image_selection ;

    if (gui->image_widget != NULL) {

      g_object_ref(gui->image_widget) ;

      gtk_container_remove(GTK_CONTAINER(gui->image_container), gui->image_widget) ;

      gtk_image_clear(GTK_IMAGE(gui->image_widget)) ;

      gtk_image_set_from_file(GTK_IMAGE(gui->image_widget), cover_image.c_str() ) ;

    }

    gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, (settings.display_size - settings.image_resized_size) / 2, (settings.display_size - settings.image_resized_size)  / 2 ) ;

  }

}

const bool check_file(const char *filepath) {

  /** Single file playing processing function. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  if (! check_file_selection(filepath) ) {

    string msg = "Failed to get file: " ;

    msg += g_path_get_basename(filepath)  ;

    msg += " \n\nCannot play selected file !!!\n\nUnsupported filetype !" ;

    display_message_dialog("File selection error !", msg.c_str() ) ;

    #ifdef DEBUG
    fprintf(stderr,"\n%s Error file selection.\n", __func__) ; fflush(stderr) ;
    #endif

    return false ;
  }

  folder_imaging_cover_container.clear() ;
  folder_imaging_cover_container.shrink_to_fit() ;

  // Setting global variables.
  // Update type of selection.
  play_folder_content = false ;
  // Update folder basename.
  folder_basename = (char *) g_path_get_basename(filepath) ;

  search_and_set_cover_image(filepath) ;



  // Set folder name as button text.
  gtk_button_set_label(GTK_BUTTON(gui->folder_chooser_button), g_path_get_basename(filepath) ) ;

  // Reset some control variables.
  set_pause(false) ;
  set_playing(false) ;
  set_stop(false) ;

  // Show play button and hide pause because they take the same place in the GUI.
  gtk_widget_hide(gui->button_pause) ;
  gtk_widget_show(gui->button_play)  ;

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

    msg += g_path_get_basename(folderpath)  ;

    msg += " \n\nDoes not found any playable compatible music file in folder !!!\n\nUnsupported filetype !" ;

    display_message_dialog("Error selected folder !", msg.c_str() ) ;

    #ifdef DEBUG
    fprintf(stderr,"\n%s Error collecting song list.\n", __func__) ; fflush(stderr) ;
    #endif

    return false ;
  }

  folder_imaging_cover_container.clear() ;
  folder_imaging_cover_container.shrink_to_fit() ;

  search_and_set_cover_image(folderpath) ;

  // Setting global variables.
  // Update type of selection.
  play_folder_content = true ;

  // Update folder basename.
  folder_basename = (char *) g_path_get_basename(folderpath) ;

  // Set folder name as button text.
  gtk_button_set_label(GTK_BUTTON(gui->folder_chooser_button), g_path_get_basename(folderpath) ) ;

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