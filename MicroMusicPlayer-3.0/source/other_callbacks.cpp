#include "other_callbacks.h"

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

#ifdef G_OS_UNIX
#ifndef MAC_INTEGRATION
// Not supported yet nor for Windows nor for Mac.
void set_as_default_music_player(GtkWidget *widget, gpointer user_data) {

  GError *error = NULL ;

  GAppInfo *appinfo_mmp = g_app_info_create_from_commandline(g_get_prgname(), g_get_prgname(), G_APP_INFO_CREATE_NONE, &error) ;

  if (error != NULL) {

    fprintf(stderr,"Error creating AppInfo: %s\n", error->message) ;

    g_error_free(error) ;

    return ;

  }


  #ifdef G_OS_WIN32  // This does not work anyway, maybe in the future !
  for (auto val : extension_list) {

    const char *type = val.replace(0, 2,"").c_str() ;

    // g_app_info_set_as_default_for_extension not supported yet.
    if (! g_app_info_set_as_default_for_extension(appinfo_mmp, type, &error)) {

      fprintf(stderr,"Cannot set extension: %s as default !\n%s\n", type, error->message) ;

      g_error_free(error) ;

      error = NULL ;
    }

  }
  #endif

  #ifdef G_OS_UNIX
  for (auto val : mimetype_list) {

    if (! g_app_info_set_as_default_for_type(appinfo_mmp, val, &error)) {

      fprintf(stderr,"Cannot set extension: %s as default !\n%s\n", val, error->message) ;

      g_error_free(error) ;

      error = NULL ;
    }

  }
  #endif


  g_object_unref(appinfo_mmp) ;

  display_message_dialog("Operation success !", "mmp set as default music player.\nThe right choice, yes !", GTK_MESSAGE_INFO, GTK_BUTTONS_OK) ;

  return ;

}

void reset_associations(GtkWidget *widget, gpointer user_data) {

  DEBUG_FUNC_MARK

  GError *error = NULL ;

  GAppInfo *appinfo_mmp = g_app_info_create_from_commandline(g_get_prgname(), g_get_prgname(), G_APP_INFO_CREATE_NONE, &error) ;

  if (error != NULL) {

    fprintf(stderr,"Error creating AppInfo: %s\n", error->message) ;

    g_error_free(error) ;

    return ;

  }

  const char **content_types = g_app_info_get_supported_types(appinfo_mmp) ;



  int c = 0 ;

  if (content_types != NULL) {

    while (content_types[c] != NULL) {

      g_app_info_reset_type_associations(g_content_type_get_mime_type(content_types[c])) ;

      ++c ;
    }

  }

  #ifdef G_OS_WIN32
  for (auto val : extension_list) {

    const char *type = val.replace(0, 2,"").c_str() ;

    g_app_info_reset_type_associations(type) ;

  }
  #endif

  #ifdef G_OS_UNIX
  for (auto val : mimetype_list) {

      g_app_info_reset_type_associations(val) ;


  }
  #endif

  g_object_unref(appinfo_mmp) ;

  display_message_dialog("Operation success !", "Types associations reset to default.\nThe wrong choice !", GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE) ;

  return ;
}
#endif
#endif

#ifdef INTELLIGENT_RECENT_DISPLAY_NAME

/** @NOTE: A try for better displaying the name in the recent folder list:
    *
    *        * Because normally you display the folder basename into it.
    *
    *        I have try to auto-detect and so differenciate
    *
    *          - music compilations
    *           from
    *          - music albums.
    *
    *        But my try doesn't respond exactly to what I want,
    *        maybe it's simply impossible in an absolute way.
    *
    *        So I finally decide to let this piece of code, not included into the program
    *        And to display either the foldername or the metadata album name in the
    *        recent folder list.
    **************************************************************************************/

static const bool is_album_eq_to_folder_name(const char *folderpath) ;

static inline const bool is_album_eq_to_folder_name(const char *folderpath) {

  if (not album_names_container.empty() and equal(album_names_container.begin(), album_names_container.end(), album_names_container.rbegin(), std::equal_to<string>())) {

      // All album names from every title are the same !

      gchar *dirname = g_path_get_basename(folderpath) ;

      string string_dirname = dirname ;

      g_free(dirname) ;

      string cmp_dirname ;

      transform(string_dirname.begin(), string_dirname.end(), back_inserter(cmp_dirname), [](char ch) { return tolower(ch) ; } ) ;  // Convert to lowercase for string comparison.

      return album_names_container.at(0) == cmp_dirname ; // Return if the metadata album name is different from the foldername.
  }

  return true ; // Because in this case the album names aren't the same and so the foldername predomine.

}
#endif

void add_folder_to_recent_folder_list(const char *folderpath) {

  /** Registering folder into Recent folders manager: **/

  GError *error = NULL ;

  GFile *gfile_from_folderpath = g_file_new_for_path(folderpath) ;

  if (gfile_from_folderpath == NULL) {

    fprintf(stderr,"failed to get GFile from current_folder variable !\n") ;

    return ;
  }


  char *gfile_folder_uri  = g_file_get_uri(gfile_from_folderpath) ;

  char *gfile_folder_path = g_file_get_path(gfile_from_folderpath) ;




  GFileInfo *gfile_info =  g_file_query_info(gfile_from_folderpath, G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME, G_FILE_QUERY_INFO_NONE, NULL, &error);

  if (error != NULL) {

    #ifdef DEBUG
    fprintf(stderr,"Failed to get GFileInfo:  %s\n", error->message) ;
    #endif

    g_error_free(error) ;

    error = NULL ;

  }

  GtkRecentData *recent_data  =  (GtkRecentData *) g_malloc(sizeof(GtkRecentData)) ;


  #ifdef INTELLIGENT_RECENT_DISPLAY_NAME

  // NOT USED sea above for explanations.

  if (simple_author_container.empty()) {

    goto recent_data_display_name_folderpath ;

  }

  if (not simple_author_container.empty() and equal(simple_author_container.begin(), simple_author_container.end(), simple_author_container.rbegin(), std::equal_to<std::string>()) )  {

    fprintf(stdout,"Auhtors the same !\n") ;

    // Always the same author: surely not a compilation.
    // Can set the author into the recent folders "display_name".

    if (equal(album_names_container.begin(), album_names_container.end(), album_names_container.rbegin(), std::equal_to<string>() ))  {

      // We get the author name - (maybe metadatas) album name.

      fprintf(stdout,"-) author name - (maybe metadatas) album name\n") ;

      recent_data->display_name = g_strdup_printf("%s - %s",  g_locale_to_utf8(simple_author_container.at(0).c_str(), strlen(simple_author_container.at(0).c_str()), NULL, NULL, NULL),
                                                              g_locale_to_utf8(album_names_container.at(0).c_str(), strlen(album_names_container.at(0).c_str()), NULL, NULL, NULL) ) ;

    }
    else {

      // We are sure to set the "author name - dirname" as display name.

      fprintf(stdout,"-) author name - dirname\n") ;

      recent_data->display_name = g_strdup_printf("%s - %s",  g_locale_to_utf8(simple_author_container.at(0).c_str(), strlen(simple_author_container.at(0).c_str()), NULL, NULL, NULL),
                                                              g_locale_to_utf8(g_file_info_get_display_name(gfile_info), strlen(g_file_info_get_display_name(gfile_info)), NULL, NULL, NULL) ) ;

    }

  }
  else {

    fprintf(stdout,"Auhtors not the same !\n") ;

    // It's surely a compilation from differents authors...

    // So we test if the album name is the same as the foldername.

    if (is_album_eq_to_folder_name(folderpath)) {

      // This simply mean that the metadata album name is equal to the foldername.

      recent_data_display_name_folderpath :

      if ( equal(album_names_container.begin(), album_names_container.end(), album_names_container.rbegin(), std::equal_to<string>() ) )  {

        // We simply display the name of the album coming from the metadatas:

        fprintf(stdout,"-) (maybe metadata) album name\n") ;

        recent_data->display_name     =   g_locale_to_utf8(album_names_container.at(0).c_str(), strlen(album_names_container.at(0).c_str()), NULL, NULL, NULL) ;

      }
      else  {

        // We display the foldername as display_name. That's all.

        fprintf(stdout,"-) dirname 1\n") ;

        recent_data->display_name   = g_locale_to_utf8(g_file_info_get_display_name(gfile_info), strlen(g_file_info_get_display_name(gfile_info)), NULL, NULL, NULL) ;

      }

    }
    else {

      // The album name is not the same as the folder name...

      // Surely something like a compilation named "100% Rock" and the foldername is someting like "cd1", we precess a format "album name - foldername".

      gchar *display_name_metadata    = g_locale_to_utf8(album_names_container.at(0).c_str(), strlen(album_names_container.at(0).c_str()), NULL, NULL, NULL) ;

      gchar *display_name_foldername  = g_locale_to_utf8(g_file_info_get_display_name(gfile_info), strlen(g_file_info_get_display_name(gfile_info)), NULL, NULL, NULL) ;

      if (display_name_metadata != NULL and display_name_foldername != NULL and not is_album_eq_to_folder_name(folderpath) ) {

        gchar *display_name = g_strdup_printf("%s - %s", display_name_metadata, display_name_foldername)  ;

        recent_data->display_name = g_locale_to_utf8(display_name, strlen(display_name), NULL, NULL, NULL) ;

        g_free(display_name_metadata) ;

        g_free(display_name_foldername) ;

      }
      else if (display_name_metadata != NULL) {

        recent_data->display_name = g_strdup(display_name_metadata) ;

        g_free(display_name_metadata) ;

      }
      else if (display_name_foldername != NULL) {

        recent_data->display_name = g_strdup(display_name_foldername) ;

        g_free(display_name_foldername) ;

      }
      else {

        recent_data->display_name   = g_locale_to_utf8(g_file_info_get_display_name(gfile_info), strlen(g_file_info_get_display_name(gfile_info)), NULL, NULL, NULL) ;

      }

    }

  }
  #else

  if (equal(album_names_container.begin(), album_names_container.end(), album_names_container.rbegin(), std::equal_to<string>()) ) {
    // Display the metadata album name (if metadata available, and always the same for the entire music files selection) else display the foldername.

    recent_data->display_name   = g_locale_to_utf8(album_names_container.at(0).c_str(), strlen(album_names_container.at(0).c_str()), NULL, NULL, NULL) ;
  }
  else {
    // Fallback on the folder name.
    recent_data->display_name   = g_locale_to_utf8(g_file_info_get_display_name(gfile_info), strlen(g_file_info_get_display_name(gfile_info)), NULL, NULL, NULL) ;
  }
  #endif

  recent_data->description    = NULL ;

  recent_data->mime_type      = g_strdup(DIRECTORY_MIMETYPE) ;

  recent_data->app_name       = g_strdup(g_get_prgname()) ;

  GFile *gfile_prg_rel_path   = g_file_new_for_path(g_get_prgname());

  GFile *gfile_prg_abspath    = g_file_resolve_relative_path(gfile_prg_rel_path, g_get_prgname()) ;

  char *prg_abspath           = g_file_get_path(gfile_prg_abspath) ;

  recent_data->app_exec       = g_strdup_printf("%s %s", prg_abspath, gfile_folder_path) ;

  recent_data->groups         = { NULL } ;

  recent_data->is_private     = FALSE ;


  g_object_unref(gfile_info) ;


  if ( gtk_recent_manager_add_full(gtk_recent_manager_get_default(), gfile_folder_uri, recent_data) ) {

    #ifdef DEBUG
    fprintf(stdout,"Folder: %s\nSuccessfull register into Recent folders manager.\n", gfile_folder_path) ;
    #endif
  }
  else {

    #ifdef DEBUG
    fprintf(stdout,"Failed to register folder: %s\n", gfile_folder_path) ;
    #endif
  }


  free(recent_data) ;

  g_object_unref(gfile_from_folderpath) ;

  g_object_unref(gfile_prg_abspath) ;

  g_object_unref(gfile_prg_rel_path) ;

  g_free(gfile_folder_uri) ;

  g_free(gfile_folder_path) ;

  g_free(prg_abspath) ;

  return ;

}