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

#include "generate_menu.h"

static void open_recent_folder(GtkRecentChooser *chooser, gpointer user_data) ;

static gboolean recent_filter_func(const GtkRecentFilterInfo *filter_info, gpointer user_data) ;

static void generate_accel_label(MenuItem *menuitem, guint accel_key, GdkModifierType accel_modifier, GtkAccelGroup *menu_files_accel_group) ;

static void pack_menuitem(MenuItem *menuitem, const char *image) ;

static void generate_accel_label(MenuItem *menuitem, guint accel_key, GdkModifierType accel_modifier, GtkAccelGroup *menu_files_accel_group) ;

static void generate_accel_label(MenuItem *menuitem, guint accel_key, GdkModifierType accel_modifier, GtkAccelGroup *menu_files_accel_group) {

  if (gtk_accelerator_valid(accel_key, accel_modifier)) {

    // Menu item has an shortcut

    gchar *tmp_accel_label = gtk_accelerator_get_label(accel_key, accel_modifier) ;

    menuitem->accel_label = gtk_accel_label_new(tmp_accel_label) ;

    g_free(tmp_accel_label) ;

    gtk_label_set_justify(GTK_LABEL(menuitem->accel_label), GTK_JUSTIFY_RIGHT) ;




    gtk_widget_add_accelerator(menuitem->menuitem,
                               "activate",
                               menu_files_accel_group,
                               accel_key,
                               accel_modifier,
                               GTK_ACCEL_VISIBLE);  
     
                         
  }
  else {

    menuitem->accel_label = NULL ;
  }

  return ;

}

static void pack_menuitem(MenuItem *menuitem, const char *image=NULL) {
 
   /** Pack a big part of my menu entries. **/
 
   if (image) {
    // Menu item has an associate image

    string filepath(settings.path_to_menu_icons) ;

    filepath += image ;

    menuitem->image = gtk_image_new_from_file(filepath.c_str()) ;

  }

   /** Menu item container **/
  menuitem->hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0) ;

  if (image) {
    gtk_box_pack_start(GTK_BOX(menuitem->hbox), menuitem->image, FALSE, FALSE, 0) ;
  }

  gtk_box_pack_start(GTK_BOX(menuitem->hbox),   menuitem->label, FALSE, FALSE, 0) ;

  GtkWidget *dummy_label=gtk_label_new("") ; /** For expand between Text and shortcut text **/

  gtk_box_pack_start(GTK_BOX(menuitem->hbox),  dummy_label,      TRUE,  TRUE,  0) ;


  if (menuitem->accel_label != NULL) {
    gtk_box_pack_start(GTK_BOX(menuitem->hbox), menuitem->accel_label, FALSE, FALSE, 0) ;
  }
  else {
    gtk_box_pack_start(GTK_BOX(menuitem->hbox), gtk_label_new(""),      FALSE, FALSE, 0) ;
  }


  gtk_container_add(GTK_CONTAINER(menuitem->menuitem),menuitem->hbox) ;

  return ;

 }

static void setup_menu_item(MenuItem *menuitem, const char type, const char *label, const char *image, GtkAccelGroup *menu_files_accel_group,  GdkModifierType accel_modifier,  guint accel_key) {

  /** Generate one menu item according to the given settings **/

  switch (type) {

    case 'N' :

      menuitem->menuitem  = gtk_menu_item_new() ;
      break ;

    case 'C' :

      menuitem->menuitem  = gtk_check_menu_item_new() ;

      //gtk_check_menu_item_set_draw_as_radio(GTK_CHECK_MENU_ITEM(menuitem->menuitem), TRUE) ;

      break ;

  }



  menuitem->label = gtk_label_new(label) ;

  gtk_label_set_justify(GTK_LABEL(menuitem->label), GTK_JUSTIFY_LEFT) ;

  generate_accel_label(menuitem, accel_key, accel_modifier, menu_files_accel_group) ;

  pack_menuitem(menuitem, image) ;

  return ;
}



void initialize_menu(Menu *menu) {
  
    /** Generate all the menu, partially trought setup_menu_item() calls. **/

    menu->menu_bar = gtk_menu_bar_new() ;

    GdkModifierType MODIFIER_NONE       = (GdkModifierType) 0 ;
    GdkModifierType MODIFIER_CTRL       = (GdkModifierType) GDK_CONTROL_MASK        ;
    GdkModifierType MODIFIER_CTRL_SHIFT = (GdkModifierType) (MODIFIER_CTRL | GDK_SHIFT_MASK) ;


    menu->accel_group  = gtk_accel_group_new() ;

    menu->menu_actions = gtk_menu_new() ;

    menu->menubutton_actions  = g_slice_new(MenuItem) ;

    setup_menu_item(menu->menubutton_actions, 'N', " Music ", "multimedia-player.png", NULL, MODIFIER_CTRL, 0) ;


    menu->button_prev  = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_prev, 'N'," Previous song ", "media-skip-backward.png", menu->accel_group, MODIFIER_CTRL, GDK_KEY_b) ;

    g_signal_connect(G_OBJECT(menu->button_prev->menuitem), "activate", G_CALLBACK(prev_music), NULL) ;



    menu->button_next  = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_next, 'N', " Next song ", "media-skip-forward.png", menu->accel_group, MODIFIER_CTRL, GDK_KEY_n) ;

    g_signal_connect(G_OBJECT(menu->button_next->menuitem), "activate", G_CALLBACK(next_music), NULL) ;



    menu->button_play = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_play, 'N', " Play | Pause song ", "media-playback-start.png", menu->accel_group, MODIFIER_CTRL, GDK_KEY_p) ;

    g_signal_connect(G_OBJECT(menu->button_play->menuitem), "activate", G_CALLBACK(play_music), NULL) ;



    menu->button_stop = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_stop, 'N', " Stop song ", "media-playback-stop.png", menu->accel_group, MODIFIER_CTRL, GDK_KEY_s) ;

    g_signal_connect(G_OBJECT(menu->button_stop->menuitem), "activate", G_CALLBACK(stop_music), NULL) ;



    menu->button_mode = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_mode, 'N', " Play Mode ", "applications-multimedia.png", NULL,  MODIFIER_NONE, 0) ;





    // Radio buttons menu items are build by hand (without using setup_menu_item(...)) because it's a special case.
    // By the way by using the same GTK_SHELL_MENU for setting the gtk_osx_menubar it doesn't display the shortcuts into the Mac top menubar ???
    // And their a bug into the gtk_osx_menubar which doesn't update the checked of radio buttons. The radio buttons appears in the same state all the time. 
    menu->button_repeat_all  = g_slice_new(MenuItem) ;

    GSList *group= NULL ;

    menu->button_repeat_all->menuitem = gtk_radio_menu_item_new(group) ;

    menu->button_repeat_all->label = gtk_label_new(" Repeat All ") ;

    gtk_label_set_justify(GTK_LABEL(menu->button_repeat_all->label), GTK_JUSTIFY_LEFT);

    generate_accel_label(menu->button_repeat_all, GDK_KEY_r, MODIFIER_CTRL, menu->accel_group) ;

    pack_menuitem(menu->button_repeat_all, "media-playlist-repeat.png") ;

    g_signal_connect(G_OBJECT(menu->button_repeat_all->menuitem), "activate", G_CALLBACK(menu_repeat_all_music), NULL) ;



    // Radio buttons menu items are build by hand (without using setup_menu_item(...)) because it's a special case.
    // By the way by using the same GTK_SHELL_MENU for setting the gtk_osx_menubar it doesn't display the shortcuts into the Mac top menubar ???
    // And their a bug into the gtk_osx_menubar which doesn't update the checked of radio buttons. The radio buttons appears in the same state all the time.
    menu->button_repeat_one  = g_slice_new(MenuItem) ;

    menu->button_repeat_one->menuitem = gtk_radio_menu_item_new_from_widget( GTK_RADIO_MENU_ITEM(menu->button_repeat_all->menuitem)) ;

    menu->button_repeat_one->label = gtk_label_new(" Repeat One ") ;

    gtk_label_set_justify(GTK_LABEL(menu->button_repeat_one->label), GTK_JUSTIFY_LEFT);

    generate_accel_label(menu->button_repeat_one, GDK_KEY_r, MODIFIER_CTRL_SHIFT, menu->accel_group) ;

    pack_menuitem(menu->button_repeat_one, "media-playlist-repeat-song.png") ;

    gboolean is_menuitem_repeat_one = TRUE ;

    g_signal_connect(G_OBJECT(menu->button_repeat_one->menuitem), "activate", G_CALLBACK(menu_repeat_one_music), &is_menuitem_repeat_one) ;


    // Radio buttons menu items are build by hand (without using setup_menu_item(...)) because it's a special case.
    // By the way by using the same GTK_SHELL_MENU for setting the gtk_osx_menubar it doesn't display the shortcuts into the Mac top menubar ???
    // And their a bug into the gtk_osx_menubar which doesn't update the checked of radio buttons. The radio buttons appears in the same state all the time. 
    menu->button_repeat_off  = g_slice_new(MenuItem) ;

    menu->button_repeat_off->menuitem = gtk_radio_menu_item_new_from_widget(GTK_RADIO_MENU_ITEM(menu->button_repeat_all->menuitem)) ;

    menu->button_repeat_off->label = gtk_label_new(" Repeat Off ") ;

    gtk_label_set_justify(GTK_LABEL(menu->button_repeat_off->label), GTK_JUSTIFY_LEFT);

    generate_accel_label(menu->button_repeat_off, 0, MODIFIER_NONE, NULL) ; // Menu item has no shortcut.

    pack_menuitem(menu->button_repeat_off, "user-offline.png") ;

    g_signal_connect(G_OBJECT(menu->button_repeat_off->menuitem), "activate", G_CALLBACK(menu_repeat_off_music), NULL) ;







    menu->button_shuffle = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_shuffle, 'C', " Shuffle ", (is_shuffle) ? "media-playlist-shuffle.png" : "user-offline.png", menu->accel_group, MODIFIER_CTRL_SHIFT, GDK_KEY_S) ;

    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menu->button_shuffle->menuitem), FALSE) ;

    g_signal_connect(G_OBJECT(menu->button_shuffle->menuitem), "activate", G_CALLBACK(menu_shuffle_music), NULL) ;


    menu->button_incr_vol = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_incr_vol, 'N', " Increment volume ", "audio-volume-high.png", menu->accel_group, MODIFIER_CTRL, GDK_KEY_KP_Add) ;

    g_signal_connect(G_OBJECT(menu->button_incr_vol->menuitem), "activate", G_CALLBACK(increment_volume), NULL) ;


    menu->button_decr_vol = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_decr_vol, 'N', " Decrement volume ",  "audio-volume-low.png", menu->accel_group, MODIFIER_CTRL, GDK_KEY_KP_Subtract) ;

    g_signal_connect(G_OBJECT(menu->button_decr_vol->menuitem), "activate", G_CALLBACK(decrement_volume), NULL) ;







    menu->menu_files = gtk_menu_new() ;

    menu->menubutton_files = g_slice_new(MenuItem) ;

    setup_menu_item(menu->menubutton_files, 'N', " Files ", "system-file-manager.png", NULL, MODIFIER_NONE, 0) ;


    menu->button_file = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_file, 'N', " Play file(s) ",  "folder-music.png", menu->accel_group, MODIFIER_CTRL, GDK_KEY_f) ;

    g_signal_connect(G_OBJECT(menu->button_file->menuitem), "activate", G_CALLBACK(get_files_to_play), NULL) ;

    #ifdef G_OS_UNIX
    menu->button_folder = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_folder, 'N', " Play folder ", "folder-sound.png", menu->accel_group, MODIFIER_CTRL, GDK_KEY_D) ; // Or   "folder-music.png"

    g_signal_connect(G_OBJECT(menu->button_folder->menuitem), "activate", G_CALLBACK(get_folder_to_play), NULL) ;
    #endif


    menu->button_recent = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_recent, 'N', " Recent folders ", "document-open-recent.png", NULL, MODIFIER_NONE, 0) ;




    menu->menu_recent  = gtk_recent_chooser_menu_new() ;

    gtk_recent_chooser_set_show_icons(GTK_RECENT_CHOOSER(menu->menu_recent), TRUE);

    gtk_recent_chooser_set_show_not_found(GTK_RECENT_CHOOSER(menu->menu_recent), FALSE) ;

    gtk_recent_chooser_set_limit(GTK_RECENT_CHOOSER(menu->menu_recent), 15) ;

    gtk_recent_chooser_set_show_tips(GTK_RECENT_CHOOSER(menu->menu_recent), TRUE);

    gtk_recent_chooser_set_local_only(GTK_RECENT_CHOOSER(menu->menu_recent), TRUE);

    gtk_recent_chooser_set_sort_type(GTK_RECENT_CHOOSER(menu->menu_recent), GTK_RECENT_SORT_MRU) ;

    GtkRecentFilter *recent_chooser_filter = gtk_recent_filter_new() ;


    gtk_recent_filter_add_custom(recent_chooser_filter,
                                 static_cast<GtkRecentFilterFlags>( GTK_RECENT_FILTER_MIME_TYPE | GTK_RECENT_FILTER_APPLICATION),
                                 &recent_filter_func,
                                 NULL,
                                 NULL) ;



    gtk_recent_chooser_set_filter(GTK_RECENT_CHOOSER(menu->menu_recent), GTK_RECENT_FILTER(recent_chooser_filter));




    g_signal_connect(G_OBJECT(menu->menu_recent), "item-activated", G_CALLBACK(open_recent_folder), NULL) ;


    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->button_recent->menuitem), menu->menu_recent) ;








    menu->show_playlist = g_slice_new(MenuItem) ;

    setup_menu_item(menu->show_playlist, 'N', " Display playlist ", "applications-multimedia.png", menu->accel_group,  MODIFIER_CTRL_SHIFT, GDK_KEY_p) ;

    g_signal_connect(G_OBJECT(menu->show_playlist->menuitem), "activate", G_CALLBACK(build_playlist), NULL) ;







    menu->menu_config = gtk_menu_new() ;


    menu->menubutton_config = g_slice_new(MenuItem) ;

    setup_menu_item(menu->menubutton_config, 'N', " Config ", "main-configuration.png", NULL,  MODIFIER_NONE, 0) ;



    menu->button_min_interface = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_min_interface, 'C', " Minimal interface ", "window-minimize.png", menu->accel_group,  MODIFIER_CTRL, GDK_KEY_m) ;

    g_signal_connect(G_OBJECT(menu->button_min_interface->menuitem), "activate", G_CALLBACK(switch_minimal_normal_interface), NULL) ;



    // Radio buttons menu items are build by hand (without using setup_menu_item(...)) because it's a special case.
    // By the way by using the same GTK_SHELL_MENU for setting the gtk_osx_menubar it doesn't display the shortcuts into the Mac top menubar ???
    // And their a bug into the gtk_osx_menubar which doesn't update the checked of radio buttons. The radio buttons appears in the same state all the time.
    menu->button_theme_light  = g_slice_new(MenuItem) ;

    GSList *group_theme= NULL ;

    menu->button_theme_light->menuitem = gtk_radio_menu_item_new(group_theme) ;

    menu->button_theme_light->label = gtk_label_new(" Theme light ") ;

    gtk_label_set_justify(GTK_LABEL(menu->button_theme_light->label), GTK_JUSTIFY_LEFT);

    generate_accel_label(menu->button_theme_light, GDK_KEY_t, MODIFIER_CTRL, menu->accel_group) ;

    pack_menuitem(menu->button_theme_light, "preferences-desktop-display.png") ;

    g_signal_connect(G_OBJECT(menu->button_theme_light->menuitem), "activate", G_CALLBACK(switch_to_light_theme_menu), NULL) ;


    // Radio buttons menu items are build by hand (without using setup_menu_item(...)) because it's a special case.
    // By the way by using the same GTK_SHELL_MENU for setting the gtk_osx_menubar it doesn't display the shortcuts into the Mac top menubar ???
    // And their a bug into the gtk_osx_menubar which doesn't update the checked of radio buttons. The radio buttons appears in the same state all the time.
    menu->button_theme_dark  = g_slice_new(MenuItem) ;

    menu->button_theme_dark->menuitem = gtk_radio_menu_item_new_from_widget( GTK_RADIO_MENU_ITEM(menu->button_theme_light->menuitem)) ;

    menu->button_theme_dark->label = gtk_label_new(" Theme dark ") ;

    gtk_label_set_justify(GTK_LABEL(menu->button_theme_dark->label), GTK_JUSTIFY_LEFT);

    generate_accel_label(menu->button_theme_dark, GDK_KEY_t, MODIFIER_CTRL_SHIFT, menu->accel_group) ;

    pack_menuitem(menu->button_theme_dark, "preferences-desktop-display.png") ;

    g_signal_connect(G_OBJECT(menu->button_theme_dark->menuitem), "activate", G_CALLBACK(switch_to_dark_theme_menu), NULL) ;


    // Radio buttons menu items are build by hand (without using setup_menu_item(...)) because it's a special case.
    // By the way by using the same GTK_SHELL_MENU for setting the gtk_osx_menubar it doesn't display the shortcuts into the Mac top menubar ???
    // And their a bug into the gtk_osx_menubar which doesn't update the checked of radio buttons. The radio buttons appears in the same state all the time.
    menu->button_icons_oxygen  = g_slice_new(MenuItem) ;

    GSList *group_icons= NULL ;

    menu->button_icons_oxygen->menuitem = gtk_radio_menu_item_new(group_icons) ;

    menu->button_icons_oxygen->label = gtk_label_new(" Oxygen ") ;

    gtk_label_set_justify(GTK_LABEL(menu->button_icons_oxygen->label), GTK_JUSTIFY_LEFT);

    generate_accel_label(menu->button_icons_oxygen, GDK_KEY_i, MODIFIER_CTRL, menu->accel_group) ;

    pack_menuitem(menu->button_icons_oxygen,  (settings.icon_set_oxygen) ? "face-raspberry.png" : "face-sad.png") ;

    g_signal_connect(G_OBJECT(menu->button_icons_oxygen->menuitem), "activate", G_CALLBACK(configure_oxygen_radiobutton), NULL) ;


    // Radio buttons menu items are build by hand (without using setup_menu_item(...)) because it's a special case.
    // By the way by using the same GTK_SHELL_MENU for setting the gtk_osx_menubar it doesn't display the shortcuts into the Mac top menubar ???
    // And their a bug into the gtk_osx_menubar which doesn't update the checked of radio buttons. The radio buttons appears in the same state all the time.
    menu->button_icons_high_contrast  = g_slice_new(MenuItem) ;

    menu->button_icons_high_contrast->menuitem = gtk_radio_menu_item_new_from_widget( GTK_RADIO_MENU_ITEM(menu->button_icons_oxygen->menuitem)) ;

    menu->button_icons_high_contrast->label = gtk_label_new(" HighContrast ") ;

    gtk_label_set_justify(GTK_LABEL(menu->button_icons_high_contrast->label), GTK_JUSTIFY_LEFT);

    generate_accel_label(menu->button_icons_high_contrast, GDK_KEY_i, MODIFIER_CTRL_SHIFT, menu->accel_group) ;

    pack_menuitem(menu->button_icons_high_contrast, (settings.icon_set_oxygen) ? "face-sad.png" : "face-raspberry.png") ;

    g_signal_connect(G_OBJECT(menu->button_icons_high_contrast->menuitem), "activate", G_CALLBACK(configure_high_contrast_radiobutton), NULL) ;





    menu->button_config = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_config, 'N', " Configure ", "preferences-system.png", menu->accel_group,  MODIFIER_CTRL, GDK_KEY_c) ;

    g_signal_connect(G_OBJECT(menu->button_config->menuitem), "activate", G_CALLBACK(configure_program_dialog), NULL) ;






    menu->menu_info = gtk_menu_new() ;

    menu->menubutton_info  = g_slice_new(MenuItem) ;

    setup_menu_item(menu->menubutton_info, 'N', " Infos ? ", "user-info.png",      NULL, MODIFIER_NONE, 0) ;


    menu->button_readme  = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_readme, 'N', " Notice ", "document-readme.png", menu->accel_group, MODIFIER_CTRL, GDK_KEY_n) ;

    g_signal_connect(G_OBJECT(menu->button_readme->menuitem), "activate", G_CALLBACK(launch_notice_html), NULL) ;


    menu->button_about  = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_about, 'N', " About ", "dialog-about.png",    menu->accel_group, MODIFIER_CTRL,  GDK_KEY_a) ;

    g_signal_connect(G_OBJECT(menu->button_about->menuitem), "activate", G_CALLBACK(display_about_dialog), NULL) ;






    menu->button_quit = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_quit, 'N', " Quit ", "system-shutdown.png", menu->accel_group, MODIFIER_CTRL,  GDK_KEY_q) ;

    g_signal_connect(G_OBJECT(menu->button_quit->menuitem), "activate", G_CALLBACK(destroy), NULL) ;




    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), menu->menubutton_files->menuitem      ) ;

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->menubutton_files->menuitem), menu->menu_files ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->button_file->menuitem         ) ;

    #ifdef G_OS_UNIX
    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->button_folder->menuitem       ) ;
    #endif

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->button_recent->menuitem       ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), gtk_separator_menu_item_new()       ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_files), menu->button_quit->menuitem         ) ;



    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), menu->menubutton_actions->menuitem        ) ;

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->menubutton_actions->menuitem),menu->menu_actions  ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_play->menuitem           ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_stop->menuitem           ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_next->menuitem           ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_prev->menuitem           ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), gtk_separator_menu_item_new()         ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_repeat_all->menuitem     ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_repeat_one->menuitem     ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_repeat_off->menuitem     ) ;



    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), gtk_separator_menu_item_new()     ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_shuffle->menuitem    ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), gtk_separator_menu_item_new()     ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_incr_vol->menuitem   ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_decr_vol->menuitem   ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), gtk_separator_menu_item_new()     ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->show_playlist->menuitem     ) ;



    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), menu->menubutton_config->menuitem               ) ;

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->menubutton_config->menuitem), menu->menu_config         ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_config), menu->button_min_interface->menuitem         ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_config), gtk_separator_menu_item_new()                ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_config), menu->button_theme_light->menuitem           ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_config), menu->button_theme_dark->menuitem            ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_config), gtk_separator_menu_item_new()                ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_config), menu->button_icons_oxygen->menuitem          ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_config), menu->button_icons_high_contrast->menuitem   ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_config), gtk_separator_menu_item_new()                ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_config), menu->button_config->menuitem                ) ;



    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), menu->menubutton_info->menuitem       ) ;

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->menubutton_info->menuitem), menu->menu_info   ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_info), menu->button_readme->menuitem        ) ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_info), menu->button_about->menuitem         ) ;


    return ;
}

static gboolean recent_filter_func(const GtkRecentFilterInfo *filter_info, gpointer user_data) {

  const char **apps = filter_info->applications ;

  const char *mimetype = filter_info->mime_type ;

  if (g_strcmp0(mimetype, DIRECTORY_MIMETYPE) != 0) {

    return FALSE ;
  }

  int c = 0 ;

  GFile *g_file_mmp = g_file_new_for_path(g_get_prgname()) ;

  while (apps[c] != NULL) {


    #ifdef DEBUG
    fprintf(stderr,"%s app [%d]: %s\n", __func__, c, apps[c]) ;
    #endif
   
    GFile *g_file_current_app = g_file_new_for_path(apps[c]) ;

    if (g_file_equal(g_file_mmp, g_file_current_app) ) {
    
      #ifdef DEBUG
      fprintf(stdout,"Found my app which registered this folder !\n") ;
      #endif
     
      return TRUE ; // Case this program have registered the folder (Recent entry).

    }

    ++c ;

  }

  return FALSE ;


}






static void open_recent_folder(GtkRecentChooser *chooser, gpointer user_data) {

  stop_music(NULL, NULL) ;

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  // Setting control variables:
  music_song_counter = 0 ;

  // Clear all containers.
  playlist_shuffle_indexes.clear() ;
  playlist_shuffle_back_up.clear() ;
  folder_music_playlist_container.clear() ;

  imaging_cover_container.clear() ;
  title_author_container.clear()  ;
  album_names_container.clear()   ;


  cover_image.clear();



  GtkRecentInfo *recent_chooser_info = gtk_recent_chooser_get_current_item(chooser) ;

  // Getting the folderpath trough a GFile and the uri component of it.
  GFile *folder_uri = g_file_new_for_uri(gtk_recent_info_get_uri(recent_chooser_info));

  gchar *folderpath = g_file_get_path(folder_uri) ;

  g_object_unref(folder_uri) ;

  if (! parse_folder(folderpath) ) {

    g_free(folderpath) ;

    gtk_recent_info_unref(recent_chooser_info) ;

    return ;
  }


  gtk_recent_info_unref(recent_chooser_info) ;


  gchar *dirname = g_path_get_dirname(folderpath) ;

  current_folder = dirname ;

  g_free(dirname) ;

  g_free(folderpath) ;



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
  playlist_shuffle_back_up = playlist_shuffle_indexes ;

  /** Start settings **/
  set_pause(false)   ;
  set_playing(false) ;
  set_stop(true)     ;
  set_order(false)   ;

  // Show play button and hide pause because they take the same place in the GUI.
  gtk_widget_hide(gui->button_pause) ;
  gtk_widget_show(gui->button_play)  ;

  at_start = true ;

  #ifdef DEBUG
  vector<size_t> check_size={ imaging_cover_container.size(),
                              title_author_container.size(),
                              album_names_container.size(),
                              folder_music_playlist_container.size(),
                              playlist_shuffle_indexes.size(),
                              playlist_shuffle_back_up.size() } ;

  for (uint8_t c=0, cc=check_size.size()-1 ; c < check_size.size() ; cc=c, ++c) {

    g_assert( check_size.at(c) == check_size.at(cc) ) ;

  }
  #endif
 
 
  // Update the the playlist displaying windows content if actually shown.
  change_playlist() ;

  // Start playing music.
  play_music(NULL, NULL) ;

  return ;

}