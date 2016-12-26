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

#include "music_hooks.h"

void selected_song(const int song_index) {

  /** Play a song from playlist selection. **/


  set_stop(false) ;

  // Set playlist selected song index.
  music_song_counter = song_index ;

  // Update the displayed playlist window if currently displayed.
  update_playlist() ;

  timeout_action = true ;

}



static void following_song_hook(void) {

  /** Play next song hook function **/

  if (is_repeat_all == 2) {

    goto no_ops ;
  }

  if ( music_song_counter < (total_song_counter-1) && ! play_order && ! is_shuffle) {
    music_song_counter++ ;
  }
  else if ( music_song_counter > 0                 &&   play_order  && ! is_shuffle) {
    music_song_counter-- ;
  }
  else if (music_song_counter == (total_song_counter-1)  && ! is_shuffle) {

    /** End of playlist reached. **/

    if (is_repeat_all == 1) { // Repeat all feature enabled.

      music_song_counter = 0 ;

    }
    else {  // Repeat all feature disabled.

      if (! is_shuffle) { // Shuffle feature disabled.



        // We stop playing song as set from the user.
        stop_music(NULL, NULL) ;

        // Update the displayed playlist window if currently displayed.
        update_playlist() ;

        return ;
      }

    }

  }

  if (is_shuffle) {

    // Getting the index of next song and
    // so pop the index from the playlist_shuffle_indexes vector.
    music_song_counter = shuffle_get_song_index() ;

    if (is_end_of_shuffle_playlist()) {

      stop_music(NULL, NULL) ;

      return ;

    }

  }

  // Update the displayed playlist window if currently displayed.
  update_playlist() ;

  no_ops :

  timeout_action = true ;

}


void music_finished_hook(const struct libvlc_event_t *event, void *data) {

  /** Called from the libvlc event manager. **/

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif


  if (is_stopped) {

    // Music playing is stopped.

    return ;

  }

  following_song_hook() ;

  return ;

}

bool timeout_timeline(void *user_data) {

  /** Program lifetime tiemout, which have for purpose to:
    *
    *  to update the display timeline value.
    *
    *  @NOTE: see the function @timeout_update_media(...) comments in the same file underhand,
    *         for explanations about the GRecMutex using.
    *
  **/

  // Used for avoiding mainloop timeouts collisions: with a GLib Recurviv GMutex locking @Try (Else it can block the interface without the "try").
  gboolean ret = g_rec_mutex_trylock(&mainloop_ctrl_rec_mutex) ;

  if (not ret) {

    return TRUE ;
  }

  if (libvlc_media_player_is_playing(media_player)) {

    float delay = libvlc_media_player_get_position(media_player) ;

    gtk_range_set_value(GTK_RANGE(gui->timeline_scale), static_cast<double>(delay)) ;

  }

  g_rec_mutex_unlock(&mainloop_ctrl_rec_mutex) ;

  return TRUE ;

}


bool timeout_update_media(void *user_data) {

  /** Program lifetime tiemout, which have for purpose to:
    *
    *  change the current media (song) in all situations:
    *
    *  * The current song as elapsed: an event is send and this function is called.
    *
    *  * The user press the next or prev song button(s) or menu item(s).
    *
    *  * The user select a song into the playlist.
    *
  **/


  /** @NOTE: In fact the timeout is create into the Main context,

       so into the main thread, not in another thread.


       * And another timeout is created in the same manner

       for the timeline value displaying which must be updated,

       before one second have past,


       and from this I guess comes a problem:

       because (citation of the Glib documenation):

        """

        Note that timeout functions may be delayed, due to the processing of other event sources.

        Thus they should not be relied on for precise timing.

        After each call to the timeout function,

        the time of the next timeout is recalculated based on the current time

        and the given interval (it does not try to 'catch up' time lost in delays).

        """

       So we can't precise an interval which will guarantee that the 2 timeout will never be called at the same time !

       * I suppose that this 2 timeouts can collapse when called at the same moment.

         @NOTE: I don't know if this can happen, I have only remark that the program may,

                in some few case, crash, especially when it have run for a long time...


      * @FIXTRY: So I have try to fix the problem by adding a Mutex but a recursiv Mutex (GRecMutex)

                 which is: (citation of the Glib documenation)

                  """

                  The GRecMutex struct is an opaque data structure to represent a recursive mutex.

                  It is similar to a GMutex with the difference that it is possible to lock a GRecMutex multiple times

                  in the same thread without deadlock.

                  When doing so, care has to be taken to unlock the recursive mutex as often as it has been locked.

                  """


                Because a simple Mutex block all the others behaviours from the program: is not possible to open a file or folder chooser, and so on...


                And the solution of adding a pair of simple Mutex lock and unlock into

                the file and folder chooser

                is not possible since is possible that the current song may change while this toplevel windows are open !!!

  **/

  // Used for avoiding mainloop timeouts collisions: with a GLib Recurviv GMutex.
  g_rec_mutex_lock(&mainloop_ctrl_rec_mutex) ;

  if (! timeout_action) { g_rec_mutex_unlock(&mainloop_ctrl_rec_mutex) ; return TRUE ; }

  #ifdef DEBUG
  DEBUG_FUNC_MARK
  #endif

  libvlc_media_t *media ;

  media = libvlc_media_new_path(vlc_inst, folder_music_playlist_container.at( music_song_counter ).c_str() );

  if (media == NULL) {

    g_rec_mutex_unlock(&mainloop_ctrl_rec_mutex) ;

    return TRUE ;
  }

  libvlc_media_player_set_media(media_player, media);

  libvlc_media_player_play(media_player) ;

  while (! libvlc_media_player_is_playing(media_player)) { /* Wait until the music playing has stop. */ }

  duration_min = (libvlc_media_get_duration(media) / 1000.0) / 60 ;

  duration_sec = (libvlc_media_get_duration(media) / 1000)  % 60 ;

  double value = (static_cast<double>(duration_min) * 60.0) + (static_cast<double>(duration_sec)) ;


  gchar *media_duration = g_strdup_printf("%02li:%02li", static_cast<long int>(duration_min), static_cast<long int>(duration_sec)) ;


  factor = value ;

  #ifdef INFO
  #if (INFO >= 1)
  fprintf(stdout,"\n%s: playing song\n -> %s\n", g_get_prgname(), (to_string(music_song_counter+1)+" "+title_author_container.at(music_song_counter)+" "+string(media_duration)).c_str() ) ; fflush(stdout) ;
  #endif
  #endif


  #ifdef G_OS_UNIX
  if (settings.send_notification) {

    /** For using Gtk notification you will have create a *.desktop file
      * named has the same id as the application id (mmp.mrcyberfighter.desktop in this case)
      * and getting a dbus connection.
      *
      * Personnaly I dislike notifications but I think it's usefull in this case
      * and the displayed notification auto-disappears as fast as it's come, so it's OKAY.
    **/


    GNotification *notification = g_notification_new( g_get_application_name() ) ;

    g_notification_set_title(notification, "Micro Music Player") ;

    g_notification_set_default_action(notification, "app.actions") ;

    gchar *notification_body = g_strdup_printf("Play song: %s", title_author_container.at(music_song_counter).c_str()) ;

    g_notification_set_body(notification, notification_body) ;

    /** G_NOTIFICATION_PRIORITY_HIGH:
      * for events that require more attention,
      * usually because responses are time-sensitive
      * (for example chat and SMS messages or alarms).
      * This notification is an alarm so we choose this priority.
      ***********************************************************/

    g_notification_set_priority(notification, G_NOTIFICATION_PRIORITY_HIGH) ;


    g_application_send_notification(G_APPLICATION(app), "notification", notification);

    g_free(notification_body) ;

  }
  #endif

  libvlc_media_release(media);

  gtk_entry_set_text(GTK_ENTRY(gui->song_name_entry),
                                                      (
                                                      "[" +
                                                      to_string(music_song_counter+1) +
                                                      "/" +
                                                      to_string(total_song_counter)  +
                                                      "] - " +

                                                      title_author_container.at(music_song_counter)

                                                       ).c_str() );


  g_free(media_duration) ;

  gtk_button_set_label(GTK_BUTTON(gui->folder_chooser_button), album_names_container.at(music_song_counter).c_str() ) ;

  gtk_widget_set_tooltip_text(gui->folder_chooser_button, folder_music_playlist_container.at( music_song_counter ).c_str() ) ;

  timeout_action = false ;

  g_rec_mutex_unlock(&mainloop_ctrl_rec_mutex) ;

  return TRUE ;

}