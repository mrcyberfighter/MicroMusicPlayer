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

#ifndef MICRO_MUSIC_PLAYER_DEFINES_HH
#define MICRO_MUSIC_PLAYER_DEFINES_HH


#define DEBUG_FUNC_MARK  do { fprintf(stdout,"\n%s(...) called\n", __func__) ; } while(0) ;

#define INFO 1 // Verbose output from program (0-3). Advice: disable it ( = 0) if you want define DEBUG.


#define PRG_START_MSG   do { fprintf(stdout,"\n\t********************* Micro Music Player *********************\n") ; } while(0) ;







/** ***** [START] Path defines [START] ***** **/


#ifndef MAIN_PATH
#define MAIN_PATH               "./"
#endif


#define PATH_TO_ICONS           "images/icons/"

#define PATH_TO_IMAGE           "images/images/"

#define ICON_SET_HIGH_CONTRAST  "high-contrast/"
#define ICON_SET_OXYGEN         "oxygen/"


#define PATH_TO_OXYGEN_BUTTON_ICONS           MAIN_PATH PATH_TO_ICONS     ICON_SET_OXYGEN         "22x22/"
#define PATH_TO_OXYGEN_MENU_ICONS             MAIN_PATH PATH_TO_ICONS     ICON_SET_OXYGEN         "16x16/"


#define PATH_TO_HIGH_CONTRAST_BUTTON_ICONS    MAIN_PATH PATH_TO_ICONS     ICON_SET_HIGH_CONTRAST   "22x22/"
#define PATH_TO_HIGH_CONTRAST_MENU_ICONS      MAIN_PATH PATH_TO_ICONS     ICON_SET_HIGH_CONTRAST   "16x16/"


#define PATH_TO_CONF_FILE       MAIN_PATH     "Configuration/micro-music-player.conf"

#define TMP_FILE_FOLDER  "/tmp"

#define TMP_FILE_NAME   "/MMP_tmp_cover_file.png"

#define TMP_FILE_PATH   TMP_FILE_FOLDER TMP_FILE_NAME

/** ***** [END] Path defines [END] ***** **/



/** [START] ***** Configuration settings [START] ***** **/
#define CONFIG_IS_REPEAT_ALL_ON   (bool) true
#define CONFIG_IS_SHUFFLE_ON      (bool) false




#define CONFIG_LITTLE    0
#define CONFIG_MIDDLE    1
#define CONFIG_BIG       2


#define SPACE_BUTTONS_LITTLE             8

#define DISPLAY_SIZE_LITTLE          256+64
#define IMAGE_RESIZED_SIZE_LITTLE       256


#define SPACE_BUTTONS_MIDDLE             12

#define DISPLAY_SIZE_MIDDLE         256+128
#define IMAGE_RESIZED_SIZE_MIDDLE    256+64


#define SPACE_BUTTONS_BIG                16

#define DISPLAY_SIZE_BIG            256+196
#define IMAGE_RESIZED_SIZE_BIG      256+128



/** ***** [END] Configuration settings [END] ***** **/

#define PATH_TO_GPLV3             MAIN_PATH   "License/GPLv3.txt"

#define PATH_TO_README            MAIN_PATH   "README/singlehtml/README.html"


#define PATH_TO_README_FILE       MAIN_PATH   PATH_TO_README    "README.html"
#define PATH_TO_PRG_IMAGE         MAIN_PATH   PATH_TO_IMAGE     "Micro_Music_Player.png"


#define DEFAULT_IMAGE_SIZE        256

#define RAND_ITERATIONS            16

#define BUTTON_SIZE                40



#endif