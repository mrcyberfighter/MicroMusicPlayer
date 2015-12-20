MMP (Micro Music Player)
------------------------

:Developer: Eddie Brüggemann

:Contact: mrcyberfighter@gmail.com

:version: 2.0

:Language: C++

:Release Time: 14/12/2015

:License: GPLv3

.. image:: ./Micro_Music_Player.png

Presentation from MMP (Micro Music Player)
------------------------------------------

**MMP** is a little, minimal features, music player program with following simple functionalities:

  + **Play**, **Stop**, **Pause**, **Resume** music playing.

  + Playing **Next**, **Previous**, song control options.

  + **Shuffle** and **Repeat All** features (playlist modes).

  + **Volume** control setting.

**MMP** is an easy music folder or file playing concept music player so that you only have to select a folder which contains some **MMP** compatible music files (most common suppported filetypes: ``*.mp3``, ``*.ogg``, ``*.flac``, ``*.wma`` and ``*.wav``) to play it content, or a single file.

After listing the folder content and searching for an cover image to display ; **MMP** will give you full access to the folder music content and display the album cover image if found one in the choosen folder.

A cover image in form of a compatible image file (filetypes:  ``*.jpg``, ``*.jpe``, ``*.jpeg``,  ``*.png``,  ``*.bmp``, ``*.dib``,  or  ``*.tif``, ``*.tiff``) resized to **MMP** 3 differents, free choosable, fixed interface sizes (**little**, **middle**, **big** sizes).

Then **MMP** play the folder content music in lexicographic sorted order (so as your O.S present you the files) or in shuffle mode, wenn you don't select a single file for playing.

Additionnal features
--------------------

+ **Play** a single file, to play a unique music file instead of an entire folder.

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

  3. You can set the **default folder** set by folder selector opening.

  4. You can *click-on*, *click-off* the **repeat all** and **shuffle** mode to be set as you want.

  5. Else you can change the **default volume intensity** (*from 0 to 128 units*, which default to 64.) to be set as the default volume intensity from the program.

  Changes are immediately applied on the program, except the **default volume intensity**, but you must press the **Apply** button to store the settings, so that you can get it back at every new start from the program.
 
  You can open a folder with MicroMusicPlayer through your file navigator or start it with the commandline:

  ::

    $ mmp folderpath # mmp is a symbolic link.


MMP supported filetypes:
------------------------

Music files filetypes:


   + **mp3** (*MPEG-1 Audio Layer III or MPEG-2 Audio Layer III*).
   + **ogg** (*Ogg Vorbis*).
   + **flac** (*Free Lossless Audio Codec*).
   + **wav** (*WAVEform audio file format*).
   + **wma** (*Windows Media Audio*).
   + **aac** (*Advanced Audio Coding*).
   + **ac3** (*Dolby Digital*).
   + **mid** or **midi** (*Musical Instrument Digital Interface*).
   + **ape** (*Monkey’s Audio*).
   + **mov** (*QuickTime*).

  Else the complete supported filetypes list:

    \*.3ga
    \*.669
    \*.a52
    \*.aac
    \*.ac3
    \*.adt
    \*.adts
    \*.aif
    \*.aifc
    \*.aiff
    \*.amb
    \*.amr
    \*.aob
    \*.ape
    \*.au
    \*.awb
    \*.caf
    \*.dts
    \*.flac
    \*.it
    \*.kar
    \*.m4a
    \*.m4b
    \*.m4p
    \*.m5p
    \*.mid
    \*.mka
    \*.mlp
    \*.mod
    \*.mpa
    \*.mp1
    \*.mp2
    \*.mp3
    \*.mpc
    \*.mpga
    \*.mus
    \*.oga
    \*.ogg
    \*.oma
    \*.opus
    \*.qcp
    \*.ra
    \*.rmi
    \*.s3m
    \*.sid
    \*.spx
    \*.tak
    \*.thd
    \*.tta
    \*.voc
    \*.vqf
    \*.w64
    \*.wav
    \*.wma
    \*.wv
    \*.xa
    \*.xm


What MMP not do:
----------------

**MMP** provide nothing else features:

  + **No** music library indexing feature.

  + **No** access to music files metadatas.

  + **No** playing timeline (*Maybe it fail to the program*) so that you cannot set the position from the current playing music file.

  + **No** database connection for cover images downloading or any indexing.

    So **MMP** stay as simple as possible: as a simple `play a folder content or a file music player`, with no internet connection required anyway, only your music folder and **MMP**.

This is because i implement it at start only for personnal usage so it´s a personnal requirement builded program,

but finally i decide to distribute it because **MMP** is so easy, as in the concept as the short source code, so that you can use it like this or modify it, in the way you want, according the **GPLv3** license terms.


Installation
------------
   
  :depends: gtk-3-0 libvlc vlc-nox

  First run
   
  ::
   
    $ ./configure

  to sea if you satisfy all the requirement for compiling and installing Micro Media Player.

  Then simply enter:

  ::
   
    $ make

    $ sudo make install  

  To build and install the program.

  Enjoy to use Micro Media Player.


Credits
-------

  Thanks to my **mother**, my **family** and to the **doctors**.

  Stay away from **drugs**: **drugs destroy your brain and your life**.

  Thanks to my **uncle** too, who let free usage of his **Mac O.S**, for the development of **MMP** version 1.0.0,

  during my holydays where i write this lines from...

    By the way **Mac O.S** seems to me a little bit strange the first times but i think it's good stuff finally.

    I think that **Mac** compile right with his ``C++ compiler`` but not verbose enough about errors. The **Mac** ``terminal`` is near enough from the **Linux** ``terminal``, so that i could work...

    The strange is that there is **no** Mac version of **MMP** available due of the lack of time and the fact that i get no **Mac** packaging knowledge.

License
-------


    ::

      Micro Music Player a very simple play a folder or a file music player.
      Copyright (C) 2015  Brüggemann Eddie.

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
