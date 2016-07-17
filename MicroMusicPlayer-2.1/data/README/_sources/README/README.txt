
mmp (Micro Music Player)
------------------------

:Developer: Eddie Brüggemann

:Contact: mrcyberfighter@gmail.com

:version: 2.1

:Language: C++

:Release Time: |today|

:License: GPLv3

Presentation from mmp (Micro Music Player)
------------------------------------------

**mmp** is a little, minimal features, music player program with following simple functionalities:

  + **Play**, **Stop**, **Pause**, **Resume** music playing.

  + Playing **Next**, **Previous**, song control options.

  + **Shuffle** and **Repeat All** features (playlist modes).
 
  + **Timeline** view, control and current elapsed time displaying.
 
  + **Volume** control setting.

**mmp** is an easy music folder or files playing concept music player so that you only have to select a folder which contains some **mmp** compatible music file(s) to play it content, or comptable music files.

After listing the folder content or file(s) and searching for an cover image to display ; **mmp** will give you full access to the music folder content or file(s) and display the album cover image if found.

A cover image in form of a compatible image file (filetypes: ``*.jpg``, ``*.jpe``, ``*.jpeg``, ``*.png``, ``*.bmp``, ``*.dib``, or ``*.tif``, ``*.tiff``) resized to **mmp** 3 differents, free choosable, fixed interface sizes (**little**, **middle**, **big** sizes).

Then **mmp** play the folder content or the  selected music files in lexicographic sorted order (so as your O.S present you the files) or in shuffle mode.

Additionnal features
--------------------

+ **Play** files, to play the selected file instead of an entire folder.

+ **Display playlist**:

  Display a window displaying the folder content or the file playlist.

  The current playing music file is marked with an icon in the marging.

  You can double-click on a file to play it.

+ **Configure program**: at your convenience.

  1. Here you can choose the icons set to use in the interface: 2 different sets available.

    * The **HighContrast** icon set *theme*: black and white icons.

    * The **Oxygen** icon set *theme*: colored icons.

  2. You can choose the main size from the interface from 3 available sizes:

    * **Little** size.

    * **Middle** size.

    * **Big** size.

  3. You can set the **default music folder** used when you open a folder, you immediately in **!**.

  4. You can *click-on*, *click-off* the **repeat all** and **shuffle** mode to be set as you want.

  5. Else you can change the **default volume intensity** (*from 0 to 100 units*, which default to *50*.) to be set as the default volume intensity from the program.

    Changes are immediately applied on the program, except the **default volume intensity**,
 
    You must press the **Apply** button to store the settings, so that you can get it back at every new start from the program.

    You can open a folder or files with **mmp** through your file navigator or start it with the commandline:

    ::

      $ mmp [folder|file(s)]path # mmp is a symbolic link.

+ **Timeline progressbar**: displaying the progress of the music file reading, which you can drag the slider from to change the current position of the music file.

+ **Elapsed time** of the current music file reading displaying.

mmp supported filetypes:
------------------------

Music files filetypes:
~~~~~~~~~~~~~~~~~~~~~~

  The most common music filetypes:

    * **mp3** (*MPEG-1 Audio Layer III or MPEG-2 Audio Layer III*).
  
    * **ogg** (*Ogg Vorbis*).
  
    * **flac** (*Free Lossless Audio Codec*).
  
    * **wav** (*WAVEform audio file format*).
  
    * **wma** (*Windows Media Audio*).
  
    * **aac** (*Advanced Audio Coding*).
  
    * **ac3** (*Dolby Digital*).
  
    * **mid** or **midi** (*Musical Instrument Digital Interface*).
  
    * **ape** (*Monkey’s Audio*).
  
    * **mov** (*QuickTime*).

  Else the complete supported filetypes list:

    * *\*.3ga*
  
    * *\*.669*
  
    * *\*.a52*
  
    * *\*.aac*
  
    * *\*.ac3*
  
    * *\*.adt*
  
    * *\*.adts*
  
    * *\*.aif*
  
    * *\*.aifc*
  
    * *\*.aiff*
  
    * *\*.amb*
  
    * *\*.amr*
  
    * *\*.aob*
  
    * *\*.ape*
  
    * *\*.au*
  
    * *\*.awb*
  
    * *\*.caf*
  
    * *\*.dts*
  
    * *\*.flac*
  
    * *\*.it*
  
    * *\*.kar*
  
    * *\*.m4a*
  
    * *\*.m4b*
  
    * *\*.m4p*
  
    * *\*.m5p*
  
    * *\*.mid*
  
    * *\*.mka*
  
    * *\*.mlp*
  
    * *\*.mod*
  
    * *\*.mpa*
  
    * *\*.mp1*
  
    * *\*.mp2*
  
    * *\*.mp3*
  
    * *\*.mpc*
  
    * *\*.mpga*
  
    * *\*.mus*
  
    * *\*.oga*
  
    * *\*.ogg*
  
    * *\*.oma*
  
    * *\*.opus*
  
    * *\*.qcp*
  
    * *\*.ra*
  
    * *\*.rmi*
  
    * *\*.s3m*
  
    * *\*.sid*
  
    * *\*.spx*
  
    * *\*.tak*
  
    * *\*.thd*
  
    * *\*.tta*
  
    * *\*.voc*
  
    * *\*.vqf*
  
    * *\*.w64*
  
    * *\*.wav*
  
    * *\*.wma*
  
    * *\*.wv*
  
    * *\*.xa*
  
    * *\*.xm*

Cover image filetypes:
~~~~~~~~~~~~~~~~~~~~~~

  + **jpeg**, **jpg**, **jpe** (*Joint Photographic Experts Group*).

  + **png** (*Portable Network Graphics*).

  + **bmp**, **dib** (*bitmap image file or device independent bitmap*).

  + **tiff**, **tif** (*Tagged Image File Format*).




What mmp not does:
------------------

**mmp** provide nothing else features:

+ No music library indexing feature.

+ No database connection for cover images downloading or any indexing.

So **mmp** stay as simple as possible: as a simple *play files* or a *folder content*, with no internet connection required anyway, only your music folder and **mmp**.

This is because i implement it at start only for personnal usage so it´s a personnal requirement builded program,

but finally i decide to distribute it because **mmp** is so easy, as in the concept as the short source code, so that you can use it like this or modify it, in the way you want, according to the terms of the **GPLv3** license.


Changelogs
----------

mmp version 2.0
~~~~~~~~~~~~~~~

has totally change the audio engine and the images management:

Instead of using the ``SDL2_mixer`` library it use the ``libvlc`` library (with which the famous media player **vlc** is build).

The ``opencv-3.0.0`` library is no more needed. **mmp** uses ``gtk+-3.0`` for the cover images resizing.

Nothing change for the user except that the program will never more crashing due of my missuse of the ``SDL2_mixer`` library.

mmp Version 2.1
~~~~~~~~~~~~~~~

Introduce some few new usefull concept.

**mmp** use some few metadatas from the files with fallback if not found for:

  1. Formatting the displaying to the user of the current playing music file, in following manner:
   
    ::
   
      N° of track Artist - Title Duration
     
  2. Getting the duration of the music file what permit:
 
    + To display the duration of the music file to the user.
   
    + Provide a timeline bar which you can drag the slider to change the current position in the track.
 
  3. Displaying a timeline bar.
 
  4. Getting the correct cover image.
 
    Because in version below 2.1 it could append that **mmp** display the back face of the a cover image or any other image.
   
    :note: It can still append but very much least as before: per example if **mmp** cannot access the metadata, but not necessarily in this case (because of fallback success).    
         

Credits
-------

  Thanks to my beloved **mother**, my **family** and to the **doctors**.

  **Stay away** from **drugs**: **drugs destroy your brain and your life**.

  Thanks to my **uncle** too, who let free usage of his **Mac O.S**, for the development of **mmp** version **1.0**,

  during my holydays where i write this lines from...

      By the way **Mac O.S** seems to me a little bit strange the first times but i think it’s good stuff finally.

      I think that **Mac** compile right with his ``C++ compiler`` but not verbose enough about errors. The **Mac** ``terminal`` is near enough from the **Linux** ``terminal``, so that i could work...

      The strange is that there is **no** Mac version of **mmp** available due of the lack of time and the fact that i get no **Mac** packaging knowledge.



License
-------


    ::

      Micro Music Player a very simple play a folder or a file music player.
      Copyright (C) 2015, 2016  Brüggemann Eddie.

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>.
     