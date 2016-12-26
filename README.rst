mmp (Micro Music Player)
========================

:Developer: Eddie Brüggemann

:Contact: <mrcyberfighter@gmail.com>

:version: 3.0

:Language: C++

:Release Time: 24/12/2016

:License: GPLv3

Dependencies:
-------------

* gtk+-3.0 (Tested with >= 3.14)

* liblvc.

  :note: You can get prebuilt of libvlc at https://nightlies.videolan.org/build/

Build system
------------

Test on:
++++++++

* GNU/Linux (Works properly).

* MSYS2 with x86_64-w64-mingw32-g++ as CXX

  .. code-block:: bash

    $ ./configure CXX=x86_64-w64-mingw32-g++ # (Works properly).

  * liblvc build obtain at: <https://nightlies.videolan.org/build/>

  Else pacman provide a git build of libvlc but currently

  you won't be able to redistribute it due of a bug from the library build.

* MACOSX (Version Sierra) (Works properly).

  * libvlc self-build search at http://wwww.open-source-projects/index/ to get it.

Tested but not works on:
++++++++++++++++++++++++

* cygwin

  with as CXX:
 
    * g++ (Compilation and install success but BUG by choosing music folder or file(s) to play).
 
    * x86_64-w64-mingw32-g++ (Doesn't Compile due of gtk+-3.18 implementation).

Installation
------------

  Simply type:

  .. code-block:: bash

    $ ./configure
   
    $ make
   
    $ sudo make install

:note: Sea the file INSTALL for further informations.

:warning: On Mac Os X it seems that a bug must be corrected by typing: ``chmod a+x install-sh``.

Notes
-----

  This program, ``mmp`` version **3.0**, was written on an ``Ubuntu 16.10`` distribution.

  Then adapt to:

  * **Windows 7 (64 bits)**, and compiled with a native ``x86_64-w64-mingw32-g++`` compiler.

  * **MacOS Sierra**, and compiled with the g++ compiler.

  So some functionalities are not available on some portages, very sorry !

  :Windows: This program was tested on a **Windows 7 64 bits** system and should work on **Windows** versions **>= 7**.

  :MacOS: This program was tested on a **Mac OS** *Sierra*, I don't know about retro-compatiblity and future O.S release compatiblity.

Credits
-------

  Thanks to my beloved **mother**, my **family** and to the **doctors**.

  **Stay away** from **drugs**: **drugs destroy your brain and your life**.

  Thanks to my **uncle** too, who let free usage of his **Mac O.S**, for the development of **mmp** version **1.0**,

  during my holydays where i write this lines from...

      By the way **Mac O.S** seems to me a little bit strange the first times but i think it’s good stuff finally.

      I think that **Mac** compile right with his ``C++ compiler`` but not verbose enough about errors.

      The **Mac** ``terminal`` is near enough from the **GNU/Linux** ``terminal``,

      so that i could work...

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


-----------------------------------------------------------

Presentation from mmp (Micro Music Player)
------------------------------------------

**mmp** is a little, minimal features, music player program with following simple functionalities:

  + **Play**, **Stop**, **Pause**, **Resume** music playing.

  + Playing **Next**, **Previous**, song control options.

  + **Shuffle**, **Repeat All** and **Repeat One** features.

  + **Timeline** view, control and current elapsed time displaying.

  + **Volume** control setting.

**mmp** is an easy music folder or files playing concept music player so that you only have to select a folder which contains some **mmp** compatible music file(s) to play it content, or selecting a list of compatible music files.

After listing the folder content or file(s) and searching for an cover image to display ; **mmp** will give you full access to the music folder content or file(s) and display the album cover image if found.

A cover image is in form of a compatible image file resized to **mmp** 3 differents, free choosable, fixed interface sizes (**little**, **middle**, **big**).

Then **mmp** play the folder content or the selected music files in lexicographic sorted order (so as your O.S present you the files) or in shuffle mode.

And the cover image is displayed, except you're using the Minimal interface.

You can access the playlist to choose a music file to play immediatly.

Features
--------

+ **Play** a folder content.

+ **Play** files, to play the selected file instead of an entire folder.

+ **Display playlist**:

  Display a window displaying the playable files from the folder content i.e the file playlist.

  The current playing music file is marked with an icon in the marging.

  You can double-click on a file to play it.

+ **Minimal interface**:

  You can switch between the normal interface which present a cover if possible or a minimal interface which doesn't present any cover image.

  :note: The **Minimal Interface** looks like a car radio !


+ **Recent folders**:

  Everytime you open music file(s) or a directory for listening music, **mmp** will store it

  in the recent folders list.

  :note: Only the folders registered by **mmp** will appear in the recent folder list.


+ **Timeline progressbar**: displaying the progress of the music file reading, which you can drag the slider from to change the current position of the music file.


+ **Elapsed time** of the current music file reading displaying.


+ **Send notification** to the user at song playing start (Not available on **Windows** nor **Mac** and subject of restrictions on **GNU/Linux**).

  .. warning:: Restriction on **GNU/Linux** systems.

    For using Gtk notification a dbus connection is required.

    And I doubt that all **GNU/Linux** distribution use the

    DBus desktop messaging processing system.

    And notify that: I cite the Gtk documentation,

    .. code-block:: text

        There is no guarantee that the notification
     
        is displayed immediately, or even at all.


+ **Configure program**: at your convenience.

  The **Configure program** window is divided into 3 pages:

  1. Player settings

  + You can *click-on*, *click-off* the **repeat all** | **Repeat one**  and **shuffle** mode to be set as you want.

  + You can change the **volume intensity** (from **0.0** to **1.0**, which default to **0.5**.) to be set as the default volume intensity from the program.

  + You can set the **default music folder** used when you open a folder, you immediately in **!**

    :warning: Feature not available on **Windows** but **Windows** store your precedent location in the file selector.

  2. Appearance

  + You can choose the icons set to use in the interface: 2 different sets available.

    * The **HighContrast** icon set *theme*: black and white icons.

    * The **Oxygen** icon set *theme*: colored icons.

  + You can choose the theme variant:

    + **Light**.

    + **Dark** (if available).

  + You can choose the main size from the interface from 3 available sizes:

    * **Little** size.

    * **Middle** size.

    * **Big** size.

  3. Misc (Not available on **Windows** nor **Mac**)

    * Set **Micro Music Player** as **default music player**.

    * **Reset** ``files associations``.

    * **Enable**/**Disable** Send Notifications.

  + You can **Enable** and **Disable** the **Minimal interface** as you want.

  .. note::

    Changes are immediately applied on the program,

    You must press the **Apply** button to store the settings, so that you can get it back at every new start from the program.


+ Magic behavior:

  When you press the **stop** button or your playlist is finished,

  you can simply press the **play** button to relaunch it from the beginning.

+ Current song presentation:

  The current playing song displaying entry field is formatted like this:

  ::

    [N°/Total] - Author - Title

You can open a folder or files with **mmp** through your file navigator or start it with the commandline:

.. code-block:: bash

  $ mmp [folder|file(s)]path # mmp is a symbolic link.

What **mmp** not does:
----------------------

**mmp** provide nothing else features:

+ No music library indexing feature.

+ No database connection for cover images downloading or any indexing.

So **mmp** stay as simple as possible: as a simple *play files* or a *folder content*, with no internet connection required anyway, only your music folder and **mmp**.

This is because i implement it at start only for personnal usage so it´s a personnal requirement builded program,

but finally i decide to distribute it because **mmp** is so easy, as in the concept as the short source code,

so that you can use it like this or modify it, in the way you want, according to the terms of the **GPLv3** license.



**mmp** menus and shortcuts
---------------------------

  1. **Files**

    + ``Ctrl + F`` -> **Open file(s)**.

    + ``Ctrl + D`` -> **Open directory**. (Not available on **Windows**).

    + **Recent folders** list.

    ---

    + ``Ctrl + Q`` -> **Quit** the application.

  2. **Music**

    + ``Ctrl + P`` -> **Play** | **Pause** the music.

    + ``Ctrl + S`` -> **Stop** music.

    + ``Ctrl + N`` -> **Next song** in the playlist.

    + ``Ctrl + B`` -> **Previous song** in the playlist (Backward).

    ---

    + ``Ctrl + R`` -> *Enable* | *Disable* **Repeat all** feature.

    + ``Ctrl + Maj + R`` -> *Enable* | *Disable* **Repeat one** feature.

    + **Repeat off**.

    ---

    + ``Ctrl + S`` -> *Enable* | *Disable* **Shuffle** feature.

    ---

    + ``Ctrl + +`` -> **Increment volume**.

    + ``Ctrl + -`` -> **Decrement volume**.

    ---

    + ``Ctrl + Maj + P`` -> **Display playlist**.

  3. **Config**

    + ``Ctrl + M`` -> *Enable* | *Disable* **Minimal interface**.

    ---

    + ``Ctrl + T``        -> *Enable* **the light theme.**

    + ``Ctrl + Maj + T``  -> *Enable* **the dark theme (if available).**

    ---

    + ``Ctrl + I``       -> *Enable* **the Oxygen icon set**.

    + ``Ctrl + Maj + I`` -> *Enable* **the HighContrast icon set**.

    ---

    + ``Ctrl + C`` -> *Display* **Configuration window**.

  4. **Info ?**

    + ``Ctrl + N`` -> *Display* The notice.

      .. warning:: On **Windows**: This works well as long as the ``start`` command is still present on your system.

        Else you can type ````Micro Music Player notice```` into your **Windows** O.S *search bar* to read the notice.

    + ``Ctrl + A`` -> *Display* the **About window**.

mmp supported filetypes:
------------------------

Music files filetypes:
++++++++++++++++++++++

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
++++++++++++++++++++++

The most common images formats:

  + **jpeg**, **jpg**, **jpe** (*Joint Photographic Experts Group*).

  + **png** (*Portable Network Graphics*).

  + **bmp**, **dib** (*bitmap image file or device independent bitmap*).

  + **tiff**, **tif** (*Tagged Image File Format*).

In fact all the image filetypes supported by gdk-pixbuf. Which are on my system:

  + **.gdkp**

  + **.bmp**

  + **.pnm**

  + **.pbm**

  + **.pgm**

  + **.ppm**

  + **.wmf**

  + **.apm**

  + **.gif**

  + **.tiff**

  + **.tif**

  + **.ani**

  + **.icns**

  + **.png**

  + **.svg**

  + **.svgz**

  + **.svg.gz**

  + **.tga**

  + **.targa**

  + **.jpeg**

  + **.jpe**

  + **.jpg**

  + **.xpm**

  + **.xbm**

  + **.qtif**

  + **.qif**

  + **.ico**

  + **.cur**

  :note: The supported image files are automatic detected in relationship to gdk-pixbuf.

