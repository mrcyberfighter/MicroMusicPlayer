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

#ifndef MICRO_MUSIC_PLAYER_INCLUDES_HH
#define MICRO_MUSIC_PLAYER_INCLUDES_HH

#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <cstdbool>
#include <clocale>
#include <cassert>
#include <random>
#include <functional>

#ifdef G_OS_WIN32
#include <cstdio>
#endif

using namespace std ;

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gio/gio.h>
#include <gdk-pixbuf/gdk-pixbuf.h>



#ifdef MACOSX
// For Mac OSX menu and dock support.
#include <gtkmacintegration/gtkosxapplication.h>
#endif

// Including the libvlc header file.
#include <vlc/vlc.h>



#endif