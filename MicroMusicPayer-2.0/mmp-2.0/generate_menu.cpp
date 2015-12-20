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
 
#ifndef MICRO_MUSIC_PLAYER_GUI_MENU_HH
#define MICRO_MUSIC_PLAYER_GUI_MENU_HH

void setup_menu_item(MenuItem *menuitem, const char type, const char *label, const char *accel_label, const char *image, GtkAccelGroup *menu_files_accel_group,  GdkModifierType accel_modifier,  guint accel_key) {
  /** Generate one menu item according to the given settings **/

  switch (type) {

    case 'N' :

      menuitem->menuitem  = gtk_menu_item_new() ;
      break ;

    case 'C' :

      menuitem->menuitem  = gtk_check_menu_item_new() ;

      gtk_check_menu_item_set_draw_as_radio(GTK_CHECK_MENU_ITEM(menuitem->menuitem), TRUE) ;

      break ;

    default :

      menuitem->menuitem  = NULL ;

      fprintf(stderr,"Error menu item type\n") ;
      return ;

  }



  menuitem->label = gtk_label_new(label) ;

  gtk_label_set_justify(GTK_LABEL(menuitem->label), GTK_JUSTIFY_LEFT);

  if (accel_label) {
    /** Menu item has an shortcut **/

    menuitem->accel_label = gtk_accel_label_new(accel_label) ;

    gtk_label_set_justify(GTK_LABEL(menuitem->accel_label), GTK_JUSTIFY_RIGHT) ;


    if (accel_key != 0) {

      gtk_widget_add_accelerator(menuitem->menuitem,
                                 "activate",
                                 menu_files_accel_group,
                                 accel_key,
                                 accel_modifier,
                                 GTK_ACCEL_VISIBLE);
    }
  }

  if (image) {
    /** Menu item has an associate image **/

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


  if (accel_label) {
    gtk_box_pack_start(GTK_BOX(menuitem->hbox), menuitem->accel_label, FALSE, FALSE, 0) ;
  }

  gtk_container_add(GTK_CONTAINER(menuitem->menuitem),menuitem->hbox) ;


  return ;
}

void initialize_menu(Menu *menu) {
    /** Generate all the menu, partially trought setup_menu_item() calls. **/

    menu->menu_bar = gtk_menu_bar_new() ;

    GdkModifierType NONE       = (GdkModifierType) 0 ;
    GdkModifierType CTRL       = (GdkModifierType) GDK_CONTROL_MASK        ;
    GdkModifierType CTRL_SHIFT = (GdkModifierType) (CTRL | GDK_SHIFT_MASK) ;


    menu->accel_group  = gtk_accel_group_new() ;

    menu->menu_actions = gtk_menu_new() ;

    menu->menubutton_actions  = g_slice_new(MenuItem) ;

    setup_menu_item(menu->menubutton_actions, 'N', " Music ", NULL , "multimedia-player.png", NULL, CTRL, 0) ;


    menu->button_prev  = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_prev, 'N'," Previous song ", " Ctrl + B " , "media-skip-backward.png", menu->accel_group, CTRL, GDK_KEY_b) ;

    g_signal_connect(G_OBJECT(menu->button_prev->menuitem), "activate", G_CALLBACK(prev_music), NULL) ;



    menu->button_next  = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_next, 'N', " Next song ", " Ctrl + N " , "media-skip-forward.png", menu->accel_group, CTRL, GDK_KEY_n) ;

    g_signal_connect(G_OBJECT(menu->button_next->menuitem), "activate", G_CALLBACK(next_music), NULL) ;



    menu->button_play = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_play, 'N', " Play | Pause song ", " Ctrl + P " , "media-playback-start.png", menu->accel_group, CTRL, GDK_KEY_p) ;

    g_signal_connect(G_OBJECT(menu->button_play->menuitem), "activate", G_CALLBACK(play_music), NULL) ;



    menu->button_stop = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_stop, 'N', " Stop song ", " Ctrl + S " , "media-playback-stop.png", menu->accel_group, CTRL, GDK_KEY_s) ;

    g_signal_connect(G_OBJECT(menu->button_stop->menuitem), "activate", G_CALLBACK(stop_music), NULL) ;



    menu->button_mode = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_mode, 'N', " Play Mode ", NULL , "applications-multimedia.png", NULL,  (GdkModifierType) 0, 0) ;



    menu->separator_01 = gtk_separator_menu_item_new() ;


    menu->button_repeat  = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_repeat, 'C', " Repeat All ", " Ctrl + Maj + R " , "media-playlist-repeat.png", menu->accel_group, CTRL_SHIFT, GDK_KEY_R) ;

    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menu->button_repeat->menuitem), CONFIG_IS_REPEAT_ALL_ON) ;

    g_signal_connect(G_OBJECT(menu->button_repeat->menuitem), "activate", G_CALLBACK(menu_repeat_all_music), NULL) ;




    menu->button_shuffle = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_shuffle, 'C', " Shuffle ",   " Ctrl + Maj + S " ,    "media-playlist-shuffle.png", menu->accel_group, CTRL_SHIFT, GDK_KEY_S) ;

    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menu->button_shuffle->menuitem), CONFIG_IS_SHUFFLE_ON) ;

    g_signal_connect(G_OBJECT(menu->button_shuffle->menuitem), "activate", G_CALLBACK(menu_shuffle_music), NULL) ;


    menu->separator_02 = gtk_separator_menu_item_new() ;

    menu->button_file = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_file, 'N', " Play single file ",   " Ctrl + F " ,    "folder-music.png", menu->accel_group, CTRL, GDK_KEY_f) ;

    g_signal_connect(G_OBJECT(menu->button_file->menuitem), "activate", G_CALLBACK(get_file_to_play), NULL) ;



    menu->separator_03 = gtk_separator_menu_item_new() ;


    menu->show_playlist = g_slice_new(MenuItem) ;

    setup_menu_item(menu->show_playlist, 'N', " Display playlist ", NULL , "applications-multimedia.png", NULL,  NONE, 0) ;

    g_signal_connect(G_OBJECT(menu->show_playlist->menuitem), "activate", G_CALLBACK(build_playlist), NULL) ;


    menu->separator_04 = gtk_separator_menu_item_new() ;


    menu->button_config = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_config, 'N', " Configure ", NULL , "preferences-system.png", NULL,  NONE, 0) ;

    g_signal_connect(G_OBJECT(menu->button_config->menuitem), "activate", G_CALLBACK(configure_program_dialog), NULL) ;



    menu->menu_info = gtk_menu_new() ;

    menu->menubutton_info  = g_slice_new(MenuItem) ;

    setup_menu_item(menu->menubutton_info, 'N', " Infos ? ", NULL , "user-info.png",      NULL, NONE, 0) ;


    menu->button_readme  = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_readme, 'N', " README ",    " R ", "document-readme.png", menu->accel_group, NONE,  GDK_KEY_r) ;

    g_signal_connect(G_OBJECT(menu->button_readme->menuitem), "activate", G_CALLBACK(launch_readme_html), NULL) ;


    menu->button_about  = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_about, 'N', " About ", " Ctrl + A ", "dialog-about.png",    menu->accel_group, CTRL,  GDK_KEY_a) ;

    g_signal_connect(G_OBJECT(menu->button_about->menuitem), "activate", G_CALLBACK(display_about_dialog), NULL) ;



    menu->separator_05 = gtk_separator_menu_item_new() ;


    menu->button_quit = g_slice_new(MenuItem) ;

    setup_menu_item(menu->button_quit, 'N', " Quit ", " Ctrl + Q " , "system-shutdown.png", menu->accel_group, CTRL,  GDK_KEY_q) ;

    g_signal_connect(G_OBJECT(menu->button_quit->menuitem), "activate", G_CALLBACK(destroy), NULL) ;


    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), menu->menubutton_actions->menuitem) ;

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->menubutton_actions->menuitem),menu->menu_actions);


    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_play->menuitem      )   ;
    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_stop->menuitem      )   ;
    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_next->menuitem      )   ;
    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_prev->menuitem      )   ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->separator_01               )   ;
    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_repeat->menuitem    )   ;
    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_shuffle->menuitem   )   ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->separator_02               )   ;
    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_file->menuitem      )   ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->separator_03               )   ;
    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->show_playlist->menuitem    )   ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->separator_04               )   ;
    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_config->menuitem    )   ;

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->separator_05               )   ;
    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_actions), menu->button_quit->menuitem      )   ;


    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_bar), menu->menubutton_info->menuitem) ;

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->menubutton_info->menuitem), menu->menu_info);

    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_info), menu->button_readme->menuitem       )   ;
    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu_info), menu->button_about->menuitem        )   ;

}

#endif
