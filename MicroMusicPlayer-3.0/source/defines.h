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

#ifndef MICRO_MUSIC_PLAYER_DEFINES_HH
#define MICRO_MUSIC_PLAYER_DEFINES_HH



#define DEBUG_FUNC_MARK  do { fprintf(stdout,"\n%s(...) called\n", __func__) ; } while(0) ;

#define INFO 1 // Verbose output from program (0-3). Advice: disable it ( = 0) if you want define DEBUG.


#define PRG_START_MSG   do { fprintf(stdout,"\n\t********************* Micro Music Player *********************\n") ; } while(0) ;



/** About definition: **/
#define AUTHOR      "Brüggemann Eddie"
#define MAIL        "<mrcyberfighter@gmail.com>"
#define PRGNAME     "MicroMusicPlayer"
#define VERSION     "3.0"
#define LICENSE     "GPLv3"
#define PRGWEBURL   "http://www.open-source-projects.net/mmp/mmp"
#define COPYRIGHT   "Copyright 2015, 2016 (C) Eddie Brüggemann."



/** ***** [START] Path defines [START] ***** **/



#ifdef G_OS_UNIX

#ifndef PREFIX
#define PREFIX                    ".."
#define DATADIR                   PREFIX  "/"
#else
#define DATADIR                   PREFIX  "/share/" PRGNAME "/"
#endif



#define PATH_TO_ICONS             DATADIR  "images/icons/"

#define PATH_TO_IMAGE             DATADIR  "images/images/"

#define ICON_SET_HIGH_CONTRAST    PATH_TO_ICONS  "high-contrast/"
#define ICON_SET_OXYGEN           PATH_TO_ICONS  "oxygen/"


#define PATH_TO_OXYGEN_BUTTON_ICONS           ICON_SET_OXYGEN         "22x22/"
#define PATH_TO_OXYGEN_MENU_ICONS             ICON_SET_OXYGEN         "16x16/"


#define PATH_TO_HIGH_CONTRAST_BUTTON_ICONS    ICON_SET_HIGH_CONTRAST   "22x22/"
#define PATH_TO_HIGH_CONTRAST_MENU_ICONS      ICON_SET_HIGH_CONTRAST   "16x16/"


#define PATH_TO_CONF_FILE         DATADIR     "Configuration/micro-music-player.conf"

#define PATH_TO_MENU_UI_FILE      DATADIR     "Configuration/menus.ui"

#define PATH_TO_GPLV3             DATADIR   "License/GPLv3.txt"

#define PATH_TO_README            DATADIR   "README/README/README.html"


#define PATH_TO_README_FILE       PATH_TO_README
#define PATH_TO_PRG_WIN_ICON      PATH_TO_IMAGE     "preferences-desktop-sound.png"

#define PATH_TO_PRG_ICON          PATH_TO_IMAGE     "Micro_Music_Player_256.png"

/** ***** [END] Path defines [END] ***** **/

#endif


/** [START] ***** Configuration settings [START] ***** **/

#define DIRECTORY_MIMETYPE "inode/directory"


#define CONFIG_LITTLE    0
#define CONFIG_MIDDLE    1
#define CONFIG_BIG       2


#define SPACE_BUTTONS_LITTLE              8

#define IMAGE_RESIZED_SIZE_LITTLE       256


#define SPACE_BUTTONS_MIDDLE             12

#define IMAGE_RESIZED_SIZE_MIDDLE    256+32


#define SPACE_BUTTONS_BIG                16

#define IMAGE_RESIZED_SIZE_BIG       256+64


#define DEFAULT_IMAGE_SIZE        256

#define MIN_RAND_ITERATIONS         4
#define MAX_RAND_ITERATIONS        16

#define BUTTON_SIZE                40

/** ***** [END] Configuration settings [END] ***** **/


#ifdef G_OS_WIN32

#define IEXPLORER "iexplore.exe"

#endif


#endif