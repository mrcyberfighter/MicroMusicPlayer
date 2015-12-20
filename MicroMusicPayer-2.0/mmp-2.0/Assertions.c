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

#ifndef MICRO_MUSIC_PLAYER_ASSERTIONS_HH
#define MICRO_MUSIC_PLAYER_ASSERTIONS_HH

#ifdef ASSERTIONS


static bool is_debugging = false ;

void start_debug_by_signal_emit(GtkWidget *widget, gpointer user_data) {

  if (!  is_debugging) {

    is_debugging = true ;
  }
  else {

    is_debugging = false ;

  }
 
  GtkWidget *widgets[]={
                         gui->button_prev,
                         gui->button_next,
                         gui->button_pause,
                         //gui->button_repeat
                         } ;


  const uint32_t nb = (uint32_t) sizeof(widgets) / sizeof(GtkWidget *) ;

  //gui->button_repeat

  GtkWidget *widget_emitter ;

  GRand *rand ;

  GTimeVal tv ;

  g_get_current_time(&tv) ;

  uint32_t sleep_time = 1 ;

  uint16_t first_sleep_modulo = 256     ;
  uint16_t last_sleep_modulo  = 256 * 8 ;

  while ( is_debugging ) {

    if (! is_debugging) {

      return ;
    }

    g_usleep((tv.tv_usec + sleep_time) % first_sleep_modulo ) ;



 
    rand = g_rand_new_with_seed((guint32) tv.tv_usec + sleep_time);

    widget_emitter = widgets[g_rand_int(rand) % nb ] ;

    g_signal_emit_by_name((gpointer) widget_emitter, "clicked", NULL);

    int randint = 1 ;

    int DEBUG_COUNTER = 1 ;

    while (gtk_events_pending()) {

       g_get_current_time(&tv) ;

       randint += 100 ;

       fprintf(stdout,"DEBUG_COUNTER: %d\n", DEBUG_COUNTER) ;

       DEBUG_COUNTER++ ;

       gtk_main_iteration() ;

   
    }

    g_get_current_time(&tv) ;

    uint32_t sleep_time = tv.tv_usec % last_sleep_modulo + randint ;

    g_usleep(sleep_time) ;

  }

}

#endif

#ifdef ASSERTIONS_HOOK

double timeit = 90.0 ;

void assert_music_stop_hook(GtkWidget *widget, gpointer user_data) {

  Mix_RewindMusic();
  if (Mix_SetMusicPosition(timeit) ==-1) {
    printf("Mix_SetMusicPosition: %s\n", Mix_GetError());
  }

}

void incr_timeit(GtkWidget *widget, double *user_data) {

  ((*user_data)) += 0.10 ;

}

void decr_timeit(GtkWidget *widget, double *user_data) {

  ((*user_data)) -= 0.10 ;

}

#endif

#endif