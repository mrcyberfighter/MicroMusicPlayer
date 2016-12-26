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

/** Micro Music Player -> A very simple music player. A select folder or file(s) music player.
  *
  * The program is written in C++ but in a C-Like style (Procedural) not Object Oriented with severals global variables,
  *
  * because the program was originally written in C and extended to C++ for a better container support.
  *
  **********************************************************************************************************************/

#include "main.h"

static bool is_arg_dir = true ;

guint change_media_id = 1 ;

guint timeline_update_id = 1 ;

// GtkApplication open callback function: for cmdline file(s) or folder opening.
static void open_files(GApplication  *application, GFile **files, gint n_files, const gchar *hint) ;

// GtkApplication activate callback function.
static void activate(GApplication *application) ;

// GtkApplication startup callback function.
static void startup(GApplication *application, gpointer user_data) ;

// GtkApplication shutdown callback function.
static void shutdown_app(GApplication *application, gpointer user_data) ;

#ifdef G_OS_UNIX
// GtkApplication (application menu) Play folder callback function.
static void play_folder_activated(GSimpleAction *action, GVariant *parameter, gpointer app) ;

// GtkApplication (application menu) Play files callback function.
static void play_files_activated(GSimpleAction *action, GVariant *parameter, gpointer app) ;

// GtkApplication (application menu) preferences callback function.
static void preferences_activated(GSimpleAction *action, GVariant *parameter, gpointer app) ;

// GtkApplication (application menu) About callback function.
static void about_activated(GSimpleAction *action, GVariant *parameter, gpointer app) ;

// GtkApplication (application menu) quit callback function.
static void quit_activated(GSimpleAction *action, GVariant *parameter, gpointer app) ;
#endif

// Quit application.
static gboolean delete_event(GtkWidget *widget,GdkEvent *event,gpointer pointer) ;


// Timeline displaying callback function.
static gchar* timeline_format_value(GtkScale *scale, gdouble value, gpointer user_data) ;

// Timeline change value callback function: for bounds check.
static gboolean timeline_change_value(GtkRange *range, GtkScrollType scroll, gdouble value, gpointer user_data) ;




static void at_exit_handler(void) ;





int main(int argc, char *argv[]) {

  #ifdef MAC_INTEGRATION
  //gtkosx_application_attention_request(gtkosx_application_get(), INFO_REQUEST);
  gtkosx_application_attention_request(gtkosx_application_get(), CRITICAL_REQUEST);
  #endif

  atexit(&at_exit_handler) ;

  if (setlocale(LC_ALL, NULL) == NULL) {

    fprintf(stderr,"Cannot query the locale\n") ;

  }

  if (! g_file_test(PATH_TO_CONF_FILE, G_FILE_TEST_EXISTS)) {

    // create the configuration folder if doesn't exist.

    char *config_dirpath = g_path_get_dirname(PATH_TO_CONF_FILE) ;

    g_mkdir_with_parents(config_dirpath, 0766) ;

    free(config_dirpath) ;

  }


  GError *error = NULL ;

  if (! g_file_test(PATH_TO_CONF_FILE, G_FILE_TEST_EXISTS) ) {

    GKeyFile *conf_file = g_key_file_new() ;

    // Set configuration settings to configuration file buffer.
    g_key_file_set_string(conf_file,   "Config",  "Buttons_Icons_Path",   PATH_TO_OXYGEN_BUTTON_ICONS) ;
    g_key_file_set_string(conf_file,   "Config",  "Menu_Icons_Path",      PATH_TO_OXYGEN_MENU_ICONS)   ;

    const char *user_music_folder = g_get_user_special_dir(G_USER_DIRECTORY_MUSIC) ;

    g_key_file_set_string(conf_file,   "Config",  "Music_Folder",         (user_music_folder != NULL) ? g_strdup(user_music_folder) : g_strdup(g_get_home_dir()) )   ;

    g_key_file_set_integer(conf_file,  "Config",  "Repeat_all",           0)  ;
    g_key_file_set_boolean(conf_file,  "Config",  "Shuffle",              FALSE) ;

    g_key_file_set_double(conf_file,   "Config",  "Volume",               0.5) ;

    g_key_file_set_uint64(conf_file,   "Config",  "Buttons_space",        SPACE_BUTTONS_LITTLE) ;

    g_key_file_set_boolean(conf_file,  "Config",  "Is_Oxygen",            TRUE) ;

    g_key_file_set_boolean(conf_file,  "Config",  "Theme_light",          TRUE)  ;

    g_key_file_set_uint64(conf_file,   "Config",  "Image_Resizing",       IMAGE_RESIZED_SIZE_LITTLE) ;

    #ifdef G_OS_UNIX
    g_key_file_set_string(conf_file,   "Config",  "Sized_Default_Image",  PATH_TO_IMAGE "Micro_Music_Player_256.png")   ;
    #endif

    #ifdef G_OS_WIN32
    g_key_file_set_string(conf_file,   "Config",  "Sized_Default_Image",  PATH_TO_PRG_IMAGE_LITTLE)   ;
    #endif

    g_key_file_set_boolean(conf_file,   "Config", "Minimal_Interface",    FALSE) ;

    g_key_file_set_boolean(conf_file,   "Config", "Notifications",        TRUE) ;

    // Write to configuration file:
    g_key_file_save_to_file(conf_file, PATH_TO_CONF_FILE, NULL);

  }

  PRG_START_MSG  // Display Micro Music Player start message.


  /** ***** [START] loading settings from configuration file or default. [START] ***** **/

  bool is_config_loaded = false ;

  GKeyFile *conf_file = g_key_file_new() ;

  if (error != NULL) {

    g_error_free(error) ;

    error = NULL ;
  }

  g_key_file_load_from_file(conf_file, PATH_TO_CONF_FILE, G_KEY_FILE_NONE, &error) ;

  if (error != NULL) {

     /** Error by loading configuration file: **/

     /** Reset settings to default. **/

     g_error_free(error) ;

     error = NULL ;

     rewrite_default_to_conf_file :

     // Default icons set.
     settings.path_to_button_icons =  PATH_TO_OXYGEN_BUTTON_ICONS ;
     settings.path_to_menu_icons   =  PATH_TO_OXYGEN_MENU_ICONS  ;
     //settings.path_to_button_icons =  PATH_TO_HIGH_CONTRAST_BUTTON_ICONS ;
     //settings.path_to_menu_icons   =  PATH_TO_HIGH_CONTRAST_MENU_ICONS  ;

     const char *user_music_folder = g_get_user_special_dir(G_USER_DIRECTORY_MUSIC) ;

     // Default folder path.
     settings.path_to_music_folder =  (user_music_folder != NULL) ? g_strdup(user_music_folder) : g_strdup(g_get_home_dir()) ;


     // Boolean configuration settings.
     settings.icon_set_oxygen      = TRUE     ;
     settings.is_repeat_all        = 0        ;
     settings.is_shuffle           = FALSE    ;


     // Default volume.
     settings.volume               = 0.5     ;


     // Start configuration little.
     settings.space_buttons           = SPACE_BUTTONS_LITTLE      ;
     settings.image_resized_size      = IMAGE_RESIZED_SIZE_LITTLE ;

     settings.theme_light             = TRUE  ;

     settings.minimal_interface       = FALSE ;

     settings.send_notification       = TRUE ;

     // Start sized default image.
     #ifdef G_OS_UNIX
     settings.path_to_default_image =  PATH_TO_IMAGE "Micro_Music_Player_256.png" ;
     #endif

     #ifdef G_OS_WIN32
     settings.path_to_default_image =  PATH_TO_PRG_ICON ;
     #endif


     // Set configuration settings to configuration file buffer.
     g_key_file_set_string(conf_file,   "Config",  "Buttons_Icons_Path",    PATH_TO_OXYGEN_BUTTON_ICONS) ;
     g_key_file_set_string(conf_file,   "Config",  "Menu_Icons_Path",       PATH_TO_OXYGEN_MENU_ICONS)   ;

     g_key_file_set_string(conf_file,   "Config",  "Music_Folder",          g_get_home_dir())   ;

     g_key_file_set_integer(conf_file,  "Config",  "Repeat_all",            0)  ;
     g_key_file_set_boolean(conf_file,  "Config",  "Shuffle",               FALSE) ;

     g_key_file_set_double(conf_file,   "Config",  "Volume",                0.5) ;

     g_key_file_set_uint64(conf_file,   "Config",  "Buttons_space",         SPACE_BUTTONS_LITTLE) ;

     g_key_file_set_boolean(conf_file,  "Config",  "Is_Oxygen",             TRUE) ;

     g_key_file_set_uint64(conf_file,   "Config",  "Image_Resizing",        IMAGE_RESIZED_SIZE_LITTLE) ;

     #ifdef G_OS_UNIX
     g_key_file_set_string(conf_file,   "Config",  "Sized_Default_Image",   PATH_TO_IMAGE "Micro_Music_Player_256.png")   ;
     #endif

     #ifdef G_OS_WIN32
     g_key_file_set_string(conf_file,   "Config",  "Sized_Default_Image",   PATH_TO_PRG_IMAGE_LITTLE)   ;
     #endif

     g_key_file_set_boolean(conf_file,  "Config",  "Theme_light",           TRUE)  ;

     g_key_file_set_boolean(conf_file,   "Config", "Minimal_Interface",     FALSE) ;

     g_key_file_set_boolean(conf_file,   "Config", "Notifications",         FALSE) ;

     // Create configuration file with default settings:
     g_key_file_save_to_file(conf_file, PATH_TO_CONF_FILE, &error);

   }
   else {

     // Getting configuration settings:
     settings.path_to_button_icons  = g_key_file_get_string(conf_file,  "Config",  "Buttons_Icons_Path",   NULL) ;
     settings.path_to_menu_icons    = g_key_file_get_string(conf_file,  "Config",  "Menu_Icons_Path",      NULL) ;

     settings.path_to_music_folder  = g_key_file_get_string(conf_file,  "Config",  "Music_Folder",         NULL) ;

     settings.icon_set_oxygen       = g_key_file_get_boolean(conf_file, "Config",  "Is_Oxygen",            NULL) ;

     settings.is_repeat_all         = g_key_file_get_integer(conf_file, "Config",  "Repeat_all",           NULL) ;
     settings.is_shuffle            = g_key_file_get_boolean(conf_file, "Config",  "Shuffle",              NULL) ;

     settings.theme_light           = g_key_file_get_boolean(conf_file, "Config",  "Theme_light",          NULL) ;

     settings.volume                = g_key_file_get_double(conf_file,  "Config",   "Volume",              NULL) ;

     // Start configuration little.
     settings.space_buttons         = g_key_file_get_int64(conf_file,   "Config",   "Buttons_space",       NULL) ;
     settings.image_resized_size    = g_key_file_get_int64(conf_file,   "Config",   "Image_Resizing",      NULL) ;

     // Start sized default image.
     settings.path_to_default_image = g_key_file_get_string(conf_file,  "Config",   "Sized_Default_Image", NULL) ;


     // Minimal interface at start.
     settings.minimal_interface      = g_key_file_get_boolean(conf_file, "Config",  "Minimal_Interface",   NULL) ;

     // Experimantal feature.
     settings.send_notification      = g_key_file_get_boolean(conf_file, "Config",  "Notifications",       NULL) ;

     if ( ! g_file_test(settings.path_to_button_icons.c_str(), G_FILE_TEST_EXISTS))   { goto rewrite_default_to_conf_file ; }

     if ( ! g_file_test(settings.path_to_menu_icons .c_str(), G_FILE_TEST_EXISTS))    { goto rewrite_default_to_conf_file ; }

     if ( ! g_file_test(settings.path_to_music_folder.c_str(), G_FILE_TEST_EXISTS))   { goto rewrite_default_to_conf_file ; }

     if ( ! g_file_test(settings.path_to_default_image.c_str(), G_FILE_TEST_EXISTS))  { goto rewrite_default_to_conf_file ; }

     is_config_loaded = true ;

  }

  g_rec_mutex_init(&mainloop_ctrl_rec_mutex) ;

  /** Start settings **/
  set_pause(false)   ;
  set_playing(false) ;
  set_stop(true)     ;
  set_order(false)   ;

  set_repeat(settings.is_repeat_all)   ;
  set_shuffle(settings.is_shuffle)     ;
  /** ************** **/

  // Setting global variables.
  cover_image = settings.path_to_default_image ;

  current_folder = settings.path_to_music_folder ;

  /** ***** [END] Loading settings from configuration file or default. [END] ***** **/

  #ifdef MAC_INTEGRATION // The library gtk-mac-integration-gtk3 define this.
 
  gtkosx_application_ready(gtkosx_application_get()) ;


  gtkosx_application_set_use_quartz_accelerators(gtkosx_application_get(), TRUE) ;

  #ifdef DEBUG
  fprintf(stdout,"Mac app use quartz accels: %d\n", gtkosx_application_use_quartz_accelerators(osx_application)) ;
  #endif

  g_set_prgname("mmp") ; // Don't automatically set from the GtkApplication system like on Linux.

  #endif


  g_set_application_name("Micro Music Player") ;


  const char *app_id = "mmp.mrcyberfighter" ; // Hint: For using Gtk notification you will have create a *.desktop file named has the id (mmp.org.mrcyberfighter in this case) and getting a dbus connection. ;

  if ( ! g_application_id_is_valid(app_id) ) {

    fprintf(stderr, "Wrong app id\n") ;
    exit(EXIT_FAILURE) ;

  }

  int status;

  int app_flags = G_APPLICATION_NON_UNIQUE ;

  // Setting the applications flags
  app_flags |=  G_APPLICATION_SEND_ENVIRONMENT ;
  app_flags |=  G_APPLICATION_HANDLES_OPEN ;

  app = gtk_application_new(app_id, static_cast<GApplicationFlags>(app_flags)) ;


  g_signal_connect( G_APPLICATION(app),  "activate",              G_CALLBACK(activate),       NULL) ;
  g_signal_connect( G_APPLICATION(app),  "open",                  G_CALLBACK(open_files),     NULL) ;
  g_signal_connect( G_APPLICATION(app),  "startup",               G_CALLBACK(startup),        NULL) ;
  g_signal_connect( G_APPLICATION(app),  "shutdown",              G_CALLBACK(shutdown_app),   NULL) ;


  bool registered = g_application_register(G_APPLICATION(app), NULL, &error) ;

  if (error != NULL or not registered) {

    fprintf(stderr,"Cannot register app: %s\n", error->message) ;

    g_error_free(error) ;

    error = NULL ;

    exit(EXIT_FAILURE) ;

  }






  #ifdef G_OS_UNIX

  if (gtk_application_prefers_app_menu(app)) {

    GtkBuilder *builder;
    GMenuModel *app_menu ;

    static GActionEntry app_entries[] = {

      { "playfolder",   play_folder_activated,  NULL, NULL, NULL },
      { "playfiles",    play_files_activated,   NULL, NULL, NULL },
      { "preferences",  preferences_activated,  NULL, NULL, NULL },
      { "about",        about_activated,        NULL, NULL, NULL },
      { "quit",         quit_activated,         NULL, NULL, NULL }

    };

    g_action_map_add_action_entries(G_ACTION_MAP(app), app_entries, G_N_ELEMENTS(app_entries), app);
  
    builder = gtk_builder_new_from_file(PATH_TO_MENU_UI_FILE) ;

    app_menu = G_MENU_MODEL(gtk_builder_get_object(builder, "appmenu"));

    gtk_application_set_app_menu(GTK_APPLICATION(app), app_menu);

    g_object_unref(builder) ;

  }

  #endif


  ///setup vlc
  vlc_inst = libvlc_new(0, NULL) ;

  if (vlc_inst == NULL) {

    fprintf(stderr, "%s %s\n", __func__, libvlc_errmsg()) ;
    exit(EXIT_FAILURE) ;
  }

  media_player = libvlc_media_player_new(vlc_inst);

  if (media_player == NULL) {

    fprintf(stderr, "%s %s\n", __func__, libvlc_errmsg()) ;

    exit(EXIT_FAILURE) ;

  }

  libvlc_event_manager_t *media_event_manager = libvlc_media_player_event_manager(media_player) ;

  if (media_event_manager == NULL) {

    fprintf(stderr, "%s %s\n", __func__, libvlc_errmsg()) ;

    exit(EXIT_FAILURE) ;

  }

  // Attach events manager to a function.
  libvlc_event_attach(media_event_manager, libvlc_MediaPlayerEndReached, &music_finished_hook, NULL) ;




  /** ***** [START] Main GUI generating, configurating and connect callbacks [START] ***** **/

  gui->window= gtk_application_window_new(app)  ;


  gtk_window_set_title(GTK_WINDOW(gui->window), g_get_application_name()) ;
  gtk_window_set_position(GTK_WINDOW(gui->window), GTK_WIN_POS_CENTER_ALWAYS) ;
  gtk_window_set_resizable(GTK_WINDOW(gui->window), FALSE);
  gtk_window_set_default_icon_from_file(PATH_TO_PRG_ICON, NULL) ;

  GdkPixbuf *window_pixbuf = gdk_pixbuf_new_from_file(PATH_TO_PRG_ICON, NULL) ;

  gtk_window_set_icon(GTK_WINDOW(gui->window), window_pixbuf) ;

  #ifdef MAC_INTEGRATION
  gtkosx_application_set_dock_icon_pixbuf(gtkosx_application_get(), window_pixbuf) ;
  #endif

  g_object_unref(window_pixbuf) ;

  gtk_widget_set_size_request(GTK_WIDGET(gui->window),-1,-1) ;



  gui->main_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0) ;

  gui->controls_buttonbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gtk_box_set_homogeneous(GTK_BOX(gui->controls_buttonbox), TRUE) ;


  Menu pmenu ;

  gui->menu = &pmenu ;

  Playlist pplaylist ;

  gui->playlist = &pplaylist ;

  // Construct the menu of the program.
  initialize_menu(gui->menu) ;

  gtk_window_add_accel_group(GTK_WINDOW(gui->window), gui->menu->accel_group);


  // Controls:
  gui->button_prev    = gtk_button_new() ;
  gui->button_play    = gtk_button_new() ;
  gui->button_pause   = gtk_button_new() ;
  gui->button_next    = gtk_button_new() ;
  gui->button_stop    = gtk_button_new() ;

  // Play modes
  gui->button_repeat  = gtk_button_new() ;
  gui->button_shuffle = gtk_button_new() ;

  // Settings:
  gui->button_volume  = gtk_volume_button_new() ;

  gtk_button_set_relief(GTK_BUTTON(gui->button_volume), GTK_RELIEF_NORMAL) ;
  gtk_scale_button_set_value(GTK_SCALE_BUTTON(gui->button_volume),  settings.volume ) ;


  // Controls:
  gui->button_prev_image       = gtk_image_new_from_file((settings.path_to_button_icons +  "media-skip-backward.png").c_str())    ;
  gui->button_play_image       = gtk_image_new_from_file((settings.path_to_button_icons +  "media-playback-start.png").c_str())   ;
  gui->button_pause_image      = gtk_image_new_from_file((settings.path_to_button_icons +  "media-playback-pause.png").c_str())   ;
  gui->button_next_image       = gtk_image_new_from_file((settings.path_to_button_icons +  "media-skip-forward.png").c_str())     ;
  gui->button_stop_image       = gtk_image_new_from_file((settings.path_to_button_icons +  "media-playback-stop.png").c_str())    ;

  // Play modes:
  gui->button_repeat_image     =  (is_repeat_all == 2) ? gtk_image_new_from_file((settings.path_to_button_icons +  "media-playlist-repeat-song.png").c_str()) :
                                                      (is_repeat_all == 1) ? gtk_image_new_from_file((settings.path_to_button_icons +  "media-playlist-repeat.png").c_str())  :  \
                                                      gtk_image_new_from_file((settings.path_to_button_icons +  "user-offline.png").c_str())    ;


  gui->button_shuffle_image    = gtk_image_new_from_file((settings.is_shuffle) ? (settings.path_to_button_icons +  "media-playlist-shuffle.png").c_str() : (settings.path_to_button_icons +  "user-offline.png").c_str()) ;


  // Volume:
  gui->button_volume_image     = gtk_image_new_from_file((settings.path_to_button_icons +  "audio-volume-medium.png").c_str())    ;
  //Configure volume button plus & minus button:
  gui->button_volume_plus  = gtk_scale_button_get_plus_button(GTK_SCALE_BUTTON(gui->button_volume))  ;
  gui->button_volume_minus = gtk_scale_button_get_minus_button(GTK_SCALE_BUTTON(gui->button_volume)) ;
  gui->button_volume_plus_image  = gtk_image_new_from_file((settings.path_to_menu_icons +  "audio-volume-high.png").c_str()) ;
  gui->button_volume_minus_image = gtk_image_new_from_file((settings.path_to_menu_icons +  "audio-volume-low.png").c_str())  ;
  gtk_button_set_image(GTK_BUTTON(gui->button_volume_plus),  gui->button_volume_plus_image)   ;
  gtk_button_set_image(GTK_BUTTON(gui->button_volume_minus), gui->button_volume_minus_image)  ;

  // Set tooltips:
  gtk_widget_set_tooltip_markup(gui->button_prev,     "<b>Play</b> the <b>previous song</b> in the playlist [ <b>Ctrl + B</b> ]")          ;
  gtk_widget_set_tooltip_markup(gui->button_play,     "<b>Pause</b> the <b>current song</b> playing in the playlist [ <b>Ctrl + P</b> ]")  ;
  gtk_widget_set_tooltip_markup(gui->button_pause,    "<b>Resume</b> the <b>current song</b> playing in the playlist [ <b>Ctrl + P</b> ]") ;
  gtk_widget_set_tooltip_markup(gui->button_next,     "<b>Play</b> the <b>next song</b> in the playlist [ <b>Ctrl + N</b> ]")              ;
  gtk_widget_set_tooltip_markup(gui->button_stop,     "<b>Stop</b> the playlist playing [ <b>Ctrl + S</b> ]")                              ;
  gtk_widget_set_tooltip_markup(gui->button_repeat,   "(Enable | Disable) <b>Repeat</b> (<i>All</i> | <i>One</i>) playlist [ <b>Ctrl (+ Maj) + R</b> ]") ;
  gtk_widget_set_tooltip_markup(gui->button_shuffle,  "(Enable | Disable) <b>shuffle</b> playing mode [ <b>Ctrl + Maj + S</b> ]") ;

  // Set images on buttons:
  gtk_button_set_image(GTK_BUTTON(gui->button_prev),    gui->button_prev_image)    ;
  gtk_button_set_image(GTK_BUTTON(gui->button_play),    gui->button_play_image)    ;
  gtk_button_set_image(GTK_BUTTON(gui->button_pause),   gui->button_pause_image)   ;
  gtk_button_set_image(GTK_BUTTON(gui->button_next),    gui->button_next_image)    ;
  gtk_button_set_image(GTK_BUTTON(gui->button_stop),    gui->button_stop_image)    ;
  gtk_button_set_image(GTK_BUTTON(gui->button_repeat),  gui->button_repeat_image)  ;
  gtk_button_set_image(GTK_BUTTON(gui->button_shuffle), gui->button_shuffle_image) ;
  gtk_button_set_image(GTK_BUTTON(gui->button_volume),  gui->button_volume_image)  ;


  // Set buttons size.
  gtk_widget_set_size_request(gui->button_prev,    BUTTON_SIZE, BUTTON_SIZE) ;
  gtk_widget_set_size_request(gui->button_play,    BUTTON_SIZE, BUTTON_SIZE) ;
  gtk_widget_set_size_request(gui->button_pause,   BUTTON_SIZE, BUTTON_SIZE) ;
  gtk_widget_set_size_request(gui->button_next,    BUTTON_SIZE, BUTTON_SIZE) ;
  gtk_widget_set_size_request(gui->button_stop,    BUTTON_SIZE, BUTTON_SIZE) ;
  gtk_widget_set_size_request(gui->button_repeat,  BUTTON_SIZE, BUTTON_SIZE) ;
  gtk_widget_set_size_request(gui->button_volume,  BUTTON_SIZE, BUTTON_SIZE) ;


  // Connecting buttons callbacks:
  g_signal_connect(G_OBJECT(gui->button_play),    "clicked",        G_CALLBACK(play_music),         NULL) ;
  g_signal_connect(G_OBJECT(gui->button_pause),   "clicked",        G_CALLBACK(pause_music),        NULL) ;
  g_signal_connect(G_OBJECT(gui->button_prev),    "clicked",        G_CALLBACK(prev_music),         NULL) ;
  g_signal_connect(G_OBJECT(gui->button_next),    "clicked",        G_CALLBACK(next_music),         NULL) ;
  g_signal_connect(G_OBJECT(gui->button_stop),    "clicked",        G_CALLBACK(stop_music),         NULL) ;
  g_signal_connect(G_OBJECT(gui->button_repeat),  "clicked",        G_CALLBACK(repeat_all_music),  NULL) ;
  g_signal_connect(G_OBJECT(gui->button_shuffle), "clicked",        G_CALLBACK(shuffle_music),      &is_shuffle) ;

  g_signal_connect(G_OBJECT(gui->button_volume),  "value-changed",  G_CALLBACK(change_volume),      NULL) ;

  gtk_box_pack_start(GTK_BOX(gui->controls_buttonbox), gui->button_prev,    TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->controls_buttonbox), gui->button_play,    TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->controls_buttonbox), gui->button_pause,   TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->controls_buttonbox), gui->button_next,    TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->controls_buttonbox), gui->button_stop,    TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->controls_buttonbox), gui->button_repeat,  TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->controls_buttonbox), gui->button_shuffle, TRUE, TRUE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->controls_buttonbox), gui->button_volume,  TRUE, TRUE, 0) ;


  // Configure current song displaying display.
  gui->song_name_entry = gtk_entry_new() ;
  gtk_entry_set_alignment(GTK_ENTRY(gui->song_name_entry), 0.5);
  g_object_set(G_OBJECT(gui->song_name_entry), "editable", FALSE, NULL) ;
  gtk_widget_set_can_focus(gui->song_name_entry, TRUE);


  #ifdef G_OS_UNIX
  // Configure folder chooser button.
  // TODO: Try to limit the size of the button content so that the window doesn't grow with the content length !
  gui->folder_chooser_button = gtk_button_new_with_label("Select a folder to play content") ;
  gtk_widget_set_tooltip_markup(gui->folder_chooser_button,  "Select a folder to play music files from.")      ;

  g_signal_connect(G_OBJECT(gui->folder_chooser_button), "clicked", G_CALLBACK(get_folder_to_play), NULL) ;
  #endif


  #ifdef G_OS_WIN32
  // Configure files chooser button.
  // TODO: Try to limit the size of the button content so that the window doesn't grow with the content length !
  gui->folder_chooser_button = gtk_button_new_with_label("Select music files to play") ;

  gtk_widget_set_tooltip_markup(gui->folder_chooser_button,  "Select music files to play:\n"
                                                             "<big><b>Use multiples selection:</b></big> <b>hold</b> <big><b><i>Ctrl</i></b></big> <b>or</b> <big><b><i>Shift</i></b></big> <b>by using the mouse</b>.\n"
                                                             "<big><b>For composing your playlist</b></big> and <b>enjoy !!!</b>.")      ;

  g_signal_connect(G_OBJECT(gui->folder_chooser_button), "clicked", G_CALLBACK(get_files_to_play), NULL) ;
  #endif


  // Configure cover image container.
  gui->image_container  = gtk_fixed_new() ;
  gui->image_widget = gtk_image_new_from_file(settings.path_to_default_image.c_str()) ;
  gtk_fixed_put(GTK_FIXED(gui->image_container), gui->image_widget, 0, 0) ;
  gtk_widget_set_size_request(gui->image_container, settings.image_resized_size, settings.image_resized_size ) ;


  GtkWidget *vbox_image_container = gtk_box_new(GTK_ORIENTATION_VERTICAL,   0) ;
  GtkWidget *hbox_image_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gui->image_container_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0) ;

  gui->timeline_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 1.0, 0.01)  ;

  gtk_scale_set_draw_value(GTK_SCALE(gui->timeline_scale), TRUE) ;

  gtk_range_set_slider_size_fixed(GTK_RANGE(gui->timeline_scale), TRUE) ;

  gtk_scale_set_value_pos(GTK_SCALE(gui->timeline_scale), GTK_POS_RIGHT) ;

  g_object_set(gui->timeline_scale, "lower-stepper-sensitivity", GTK_SENSITIVITY_OFF, NULL) ;
  g_object_set(gui->timeline_scale, "upper-stepper-sensitivity", GTK_SENSITIVITY_OFF, NULL) ;

  g_signal_connect(G_OBJECT(gui->timeline_scale), "change-value", G_CALLBACK(timeline_change_value), NULL) ;
  g_signal_connect(G_OBJECT(gui->timeline_scale), "format-value", G_CALLBACK(timeline_format_value), NULL) ;

  // Launching first application lifetime timeout, as long delayed from the second we can.
  timeline_update_id = g_timeout_add_full(G_PRIORITY_DEFAULT, 333, (GSourceFunc) timeout_timeline, NULL, NULL) ;



  gtk_box_pack_start(GTK_BOX(hbox_image_container), gtk_label_new(""),      TRUE,  TRUE,  5) ;
  gtk_box_pack_start(GTK_BOX(hbox_image_container), gui->image_container,   FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(hbox_image_container), gtk_label_new(""),      TRUE,  TRUE,  5) ;

  gtk_box_pack_start(GTK_BOX(vbox_image_container), gtk_label_new(""),      TRUE,  TRUE,  5) ;
  gtk_box_pack_start(GTK_BOX(vbox_image_container), hbox_image_container,   FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(vbox_image_container), gtk_label_new(""),      TRUE,  TRUE,  5) ;


  gtk_box_pack_start(GTK_BOX(gui->image_container_hbox), vbox_image_container, TRUE, TRUE, 0) ;


  gtk_box_pack_start(GTK_BOX(gui->main_vbox), gui->menu->menu_bar,              FALSE, FALSE, 5) ;
  gtk_box_pack_start(GTK_BOX(gui->main_vbox), gui->controls_buttonbox,          FALSE, FALSE, 5) ;
  gtk_box_pack_start(GTK_BOX(gui->main_vbox), gui->image_container_hbox,        FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->main_vbox), gui->timeline_scale,              FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->main_vbox), gui->song_name_entry,             FALSE, FALSE, 0) ;
  gtk_box_pack_start(GTK_BOX(gui->main_vbox), gui->folder_chooser_button,       FALSE, FALSE, 5) ;

  gtk_container_add(GTK_CONTAINER(gui->window), gui->main_vbox) ;

  gtk_container_set_border_width(GTK_CONTAINER(gui->window), 16) ;

  g_signal_connect(G_OBJECT(gui->window),"destroy",G_CALLBACK(destroy),NULL) ;

  g_signal_connect(G_OBJECT(gui->window),"delete-event",G_CALLBACK(delete_event),NULL) ;

  /** ***** [END] Main GUI generating, configurating and connect callbacks [END ***** **/


  // Print out others infos about configuration.
  if (is_config_loaded) {
  #if (INFO >= 2)
  fprintf(stdout, "\n%s: Settings successfull from configuration file loaded.\n", g_get_prgname() ) ;
  fprintf(stdout,"\n%s: current configuration:\n\n%s", g_get_prgname(),   g_key_file_to_data(conf_file, NULL, NULL) ) ;
  #endif
  }
  else {
  #if (INFO >= 2)
  fprintf(stdout, "\n%s: Error by loading configuration file\nReset default settings...\n", g_get_prgname() ) ;
  #endif
  }
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: Volume set at start to value: %.2lf\n", g_get_prgname(), settings.volume  ) ; fflush(stdout) ;
  #endif


  gtk_widget_show_all( GTK_WIDGET(gui->window) )  ;

  gtk_widget_hide(gui->button_pause) ;

  gtk_window_set_focus_on_map(GTK_WINDOW(gui->window), TRUE) ;

  // Activate the application.
  g_application_activate(G_APPLICATION(app)) ;

  // Launching application lifetime timeouts.
  change_media_id = g_timeout_add_full(G_PRIORITY_DEFAULT, 333, (GSourceFunc) timeout_update_media, NULL, NULL) ;


  // Setting volume according user configuration.
  libvlc_audio_set_volume(media_player, static_cast<int>(settings.volume * 100.0)) ;

  // Releasing app at start mutex in form of a simply control boolean global variable.
  start_app = false ;

  // Enter GUI mainloop.
  status = g_application_run(G_APPLICATION(app), argc, argv) ;

  g_object_unref(app);

  /** Free libvlc pointers **/
  libvlc_media_player_release(media_player) ;
  libvlc_release(vlc_inst) ;

  return status;

}


static gboolean timeline_change_value(GtkRange *range, GtkScrollType scroll, gdouble value, gpointer user_data) {

  if (libvlc_media_player_is_playing(media_player)) {

    if ( (value <= 0.0) || (value >= 1.0)) {

      return TRUE ;

    }

    libvlc_media_player_set_position(media_player, static_cast<float>(value)) ;

  }

  return TRUE ;

}

static gchar* timeline_format_value(GtkScale *scale, gdouble value, gpointer user_data) {

  return g_strdup_printf("%02li:%02li/%02li:%02li", static_cast<long int>(value *  factor) / 60, static_cast<long int>(value *  factor) % 60, static_cast<long int>(duration_min), static_cast<long int>(duration_sec)) ;

}





static void activate(GApplication *application) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  /** This signal is receive by calling: g_application_run() function,
    *
    * so the just by starting the application to run by calling the g_application_activate() function.
    *
  **/

  #ifdef G_OS_WIN32
  putenv("GTK_DATA_PREFIX=./") ;
  #endif


  #ifdef MAC_INTEGRATION // The library gtk-mac-integration-gtk3 define this.
  // @NOTE: the mac top application menu doesn't update correctly the menu radio buttons !
  gtkosx_application_set_menu_bar(gtkosx_application_get(), GTK_MENU_SHELL(gui->menu->menu_bar)) ;
  gtkosx_application_sync_menubar(gtkosx_application_get());
  #endif

  #ifdef G_OS_UNIX
  GDBusConnection *dbus_connection = g_application_get_dbus_connection(G_APPLICATION(app)) ;

  if (dbus_connection != NULL and G_IS_DBUS_CONNECTION(dbus_connection) ) {

    g_dbus_connection_start_message_processing(dbus_connection) ;

  }

  g_application_set_default(g_application_get_default()) ;

  #ifdef DEBUG
  fprintf(stdout,"GtkApplication DBUS path: %s\n", g_application_get_dbus_object_path(G_APPLICATION(app)) ) ;
  #endif

  #endif




  gtk_box_set_spacing(GTK_BOX(gui->controls_buttonbox), settings.space_buttons) ;

  // Activate the features buttons and menucheckbox according user configuration:

  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_shuffle->menuitem), is_shuffle) ;

  gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_min_interface->menuitem), (settings.minimal_interface) ? TRUE : FALSE) ;

  switch (is_repeat_all) {

    case 0 :

     gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_repeat_off->menuitem), TRUE ) ;
     break ;

    case 1 :

     gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_repeat_all->menuitem), TRUE ) ;
     break ;

    case 2 :

     gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_repeat_one->menuitem), TRUE ) ;
     break ;

    default :

    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(gui->menu->button_repeat_off->menuitem), TRUE ) ;
    settings.is_repeat_all=0 ;
    break ;

  }

  // Setting the user wanted theme variant:
  if (settings.theme_light) {

     gtk_menu_item_activate( GTK_MENU_ITEM(gui->menu->button_theme_light->menuitem) ) ;
  }
  else {

    gtk_menu_item_activate( GTK_MENU_ITEM(gui->menu->button_theme_dark->menuitem) ) ;
  }

  if (settings.icon_set_oxygen) {

    gtk_menu_item_activate(GTK_MENU_ITEM(gui->menu->button_icons_oxygen->menuitem)) ;
  }
  else {

    gtk_menu_item_activate(GTK_MENU_ITEM(gui->menu->button_icons_high_contrast->menuitem)) ;

  }



  while (gtk_events_pending()) {

    gtk_main_iteration() ;

  }


  return ;

}

static void open_files(GApplication  *application, GFile **files, gint n_files, const gchar *hint) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  /** GtkApplication command line open folder or files argument treatment function:
    * This will permit the g_win32_get_command_line() function to be automatically called internally.
    * And many others things.
    *************************************************************************************************/


  // Setting control variables:
  music_song_counter = 0 ;

  int i ;

  playlist_shuffle_indexes.clear() ;
  playlist_shuffle_back_up.clear() ;
  folder_music_playlist_container.clear() ;

  imaging_cover_container.clear() ;
  title_author_container.clear()  ;
  album_names_container.clear()   ;

  for (i = 0 ; i < n_files ; ++i) {

     gchar *path = g_file_get_path(files[i]) ;

     if (i == 0) {

        // First argument should be a valid folderpath or a valid filepath ;
        if (path == NULL) {
          fprintf(stderr,"Given argument(s) are not a valid filepath(s) or a directory path:\n%s\n",  g_get_prgname() ) ;
          exit(EXIT_FAILURE) ;
        }

        // Checking if the given argument(s) are a directory or a file(s) path.
        if (g_file_test(path, G_FILE_TEST_IS_DIR) ) {
          is_arg_dir = true ;

        }
        else if (g_file_test(path, G_FILE_TEST_IS_REGULAR) ) {
          is_arg_dir = false ;

        }


      }

      // Checking given argument on the cmdline.

      if (is_arg_dir) {

        if (! parse_folder(path) ) {


          #ifdef INFO
          #if (INFO >= 1)
          fprintf(stderr,"%s: Failed to parse folder\n -> %s\nHave not detected any playable compatible music file !!!\n\nSupported filetypes:\n", g_get_prgname(), path) ;
          for (int c=0 ; c < static_cast<int>(extension_list.size()) ; c++) {

            if (c < static_cast<int>(extension_list.size()) - 1) {
              fprintf(stderr,"%s, ",extension_list.at(c).c_str()) ;
            }
            else {
              fprintf(stderr,"%s.",extension_list.at(c).c_str()) ;
            }
          }
          #endif
          #endif

          string msg = "Failed to parse folder: " ;

          gchar *dir_basename = g_path_get_basename(path) ;

          msg += dir_basename  ;

          g_free(dir_basename) ;

          msg += " \n\nDoes not found any playable compatible music file in folder !!!" ;

          display_message_dialog("Error selected folder !", msg.c_str()) ;

        }
        else {

          // Registering folder into Recent folders manager:...


          GError *error = NULL ;

          gchar *folderpath_utf8 = g_locale_to_utf8(path, strlen(path), NULL, NULL, &error) ;

          if (error != NULL) {

            #ifdef DEBUG
            fprintf(stderr,"Failed to convert from locale to utf8:  %s\n", error->message) ;
            #endif

            g_error_free(error) ;

            error = NULL ;

            current_folder = path ;

          }
          else {

            current_folder = folderpath_utf8 ;

          }

          // Registering folder into Recent folders manager:...
          add_folder_to_recent_folder_list(folderpath_utf8) ;

          g_free(folderpath_utf8) ;

        }

      }
      else {

        static bool dirpath_found = false ;

        check_file_selection(path) ;

        if (! dirpath_found) {

          char *dirname = g_path_get_dirname(path) ;

          GError *error = NULL ;

          char *folderpath_utf8 = g_locale_to_utf8(dirname, strlen(dirname), NULL, NULL, &error) ;

          if (error != NULL) {

            #ifdef DEBUG
            fprintf(stderr,"Failed to convert from locale to utf8:  %s\n", error->message) ;
            #endif

            g_error_free(error) ;

            error = NULL ;

            current_folder = path ;

          }
          else {

            current_folder = folderpath_utf8 ;

          }


          // Registering folder into Recent folders manager:
          add_folder_to_recent_folder_list(folderpath_utf8) ;

          g_free(folderpath_utf8) ;

        }



     }

     g_free(path) ;

  }

  if (not is_arg_dir) {
    // Because the fallback function is called into the parse_folder(...) function anyway.
    if (imaging_cover_container.size() == 0) {
      // Fallback cover images getting function.
      search_and_set_cover_image(current_folder.c_str()) ;
    }

  }

  // Shrink containers size.
  playlist_shuffle_indexes.shrink_to_fit() ;
  playlist_shuffle_back_up.shrink_to_fit() ;
  folder_music_playlist_container.shrink_to_fit() ;

  imaging_cover_container.shrink_to_fit() ;
  title_author_container.shrink_to_fit()  ;
  album_names_container.shrink_to_fit()   ;

  // Reset controls variables:
  music_song_counter = 0 ;

  // Shuffle feature support.
  shuffle_playlist() ;

  reverse(playlist_shuffle_indexes.begin(), playlist_shuffle_indexes.end()) ;

  playlist_shuffle_back_up = playlist_shuffle_indexes ;

  // stdout output:
  #ifdef INFO
  #if (INFO >= 1)
  if (is_arg_dir) {

    fprintf(stdout,"\n%s: Read music files from directory:\n%s\n", g_get_prgname(), current_folder.c_str()) ;

  }
  else {
    fprintf(stdout,"\n%s: Read music files...", g_get_prgname()) ;
  }
  #endif
  #endif

  if ( not imaging_cover_container.empty() ) {

    cover_image = imaging_cover_container.at(0) ;
  }

  if (! cover_image.empty()) {

    set_cover_image( cover_image ) ;

  }


  // Show play button and hide pause because they take the same place in the GUI.
  gtk_widget_hide(gui->button_pause) ;
  gtk_widget_show(gui->button_play)  ;

  at_start = true ;

  // Start playing music.
  play_music(NULL, NULL) ;


  return ;

}

static void startup(GApplication *application, gpointer user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  while ( not g_application_get_is_registered(application) ) {

    while (gtk_events_pending()) {

      gtk_main_iteration() ;
    }
  }

  #ifdef MAC_INTEGRATION
  //gtkosx_application_attention_request(gtkosx_application_get(), INFO_REQUEST);
  gtkosx_application_attention_request(gtkosx_application_get(), CRITICAL_REQUEST);
  #endif

  return ;
}

#ifdef G_OS_UNIX
static void about_activated(GSimpleAction *action, GVariant *parameter, gpointer app) {

  display_about_dialog(NULL, NULL) ;

  return ;

}

static void play_folder_activated(GSimpleAction *action, GVariant *parameter, gpointer app) {

  get_folder_to_play(NULL, NULL) ;

  return ;

}

static void play_files_activated(GSimpleAction *action, GVariant *parameter, gpointer app) {

  get_files_to_play(NULL, NULL) ;

  return ;

}

static void preferences_activated(GSimpleAction *action, GVariant *parameter, gpointer app) {

  configure_program_dialog(NULL, NULL) ;

  return ;

}

static void quit_activated(GSimpleAction *action, GVariant *parameter, gpointer app) {

  destroy(NULL, NULL) ;

  return ;

}
#endif

static void shutdown_app(GApplication *application, gpointer user_data) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  destroy(NULL, NULL) ;

}

void at_exit_handler(void) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  GSource* g_source_media_change = g_main_context_find_source_by_id(g_main_context_default(), change_media_id) ;

  GSource* g_source_timeline_update = g_main_context_find_source_by_id(g_main_context_default(), timeline_update_id) ;

  g_rec_mutex_clear(&mainloop_ctrl_rec_mutex) ;

  if (g_source_media_change != NULL) {

    g_source_destroy(g_source_media_change)     ;
  }

  if (g_source_timeline_update != NULL) {

    g_source_destroy(g_source_timeline_update)  ;
  }

  #ifdef G_OS_WIN32

  free(PATH_TO_ICONS) ;
  free(PATH_TO_IMAGE) ;

  free(PATH_TO_PRG_IMAGE_LITTLE) ;
  free(PATH_TO_PRG_IMAGE_MIDDLE) ;
  free(PATH_TO_PRG_IMAGE_BIG) ;

  free(PATH_TO_HIGH_CONTRAST_BUTTON_ICONS) ;
  free(PATH_TO_HIGH_CONTRAST_MENU_ICONS) ;

  free(PATH_TO_OXYGEN_BUTTON_ICONS) ;
  free(PATH_TO_OXYGEN_MENU_ICONS) ;

  free(PATH_TO_GPLV3) ;

  free(PATH_TO_README) ;

  free(PATH_TO_PRG_ICON) ;

  free(PATH_TO_PRG_WIN_ICON) ;

  free(PATH_TO_CONF_FILE) ;

  #endif


  return ;
}

void destroy(GtkWidget *widget, gpointer pointer) {

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  stop_music(NULL, NULL) ;

  g_application_quit(G_APPLICATION(app)) ;

  g_object_unref(app) ;

  exit(EXIT_SUCCESS) ;

}

static gboolean delete_event(GtkWidget *widget,GdkEvent *event,gpointer pointer) {

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

    return FALSE ;
  }
  #endif

  return FALSE ;
}