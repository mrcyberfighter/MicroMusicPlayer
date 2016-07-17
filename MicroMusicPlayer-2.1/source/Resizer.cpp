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

#include "./global_vars.h"

#include "Resizer.h"

pair<int, int> Resizer::resizer(const string filename, int frame_width, int frame_height, bool use_frame) {

  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename.c_str(), NULL);

  image_width  = gdk_pixbuf_get_width(pixbuf)  ;
  image_height = gdk_pixbuf_get_height(pixbuf) ;


  float frame_image_width  = static_cast<float>(frame_width)  ;
  float frame_image_height = static_cast<float>(frame_height)  ;

  float factor= (static_cast<float>(frame_width) / static_cast<float>(frame_height) ) ;

  if ((image_width >= frame_image_width) && (image_height > frame_image_height)) {

    factor_width  =  static_cast<float>(image_width)  / static_cast<float>(image_height) ;
    factor_height =  static_cast<float>(image_height) / static_cast<float>(image_width) ;

    width  = 0.0f  ;
    height = 0.0f  ;


    if ((factor_width == 1.0) || (factor_height == 1.0)) {

      if (frame_image_height > frame_image_width) {
        width  = frame_image_width ;
        height = frame_image_width ;
      }
      else if (frame_image_height < frame_image_width) {
        width  = frame_image_height ;
        height = frame_image_height ;
      }
      else {
        width  = frame_image_height ;
        height = frame_image_height ;
      }

    }

    if (image_width > image_height) {

      if (factor_width < factor ) {

        while (height < frame_image_height) {

          if ((height + factor_height) >= frame_image_height) {
            width *= factor_height  ;
            break ;
          }

          width  += factor_width   ;
          height += factor_height  ;
        }
      }
      else if (factor_width > factor) {

        while (width < frame_image_width) {
          if ((width + factor_width) >= frame_image_width) {
            height *= factor_width ;
            break  ;
          }
          width  += factor_width   ;
          height += factor_height  ;
        }
      }

    }

    if (image_width < image_height) {

      if (factor_width < factor) {

        while (height < frame_image_height) {

          if ((height + factor_height) >= frame_image_height) {
            width *= factor_height ;
            break ;
          }
          width = width + factor_width    ;
          height =height+factor_height    ;
        }
      }
      else if (factor_width > factor) {

        while (width < frame_image_width) {

          if ((width + factor_width) >= frame_image_width) {
            height *= factor_width ;
            break  ;
          }
          width  += factor_width  ;
          height += factor_height ;
        }

      }
    }

  }

  else if ((image_width > frame_image_width) && (image_height <= frame_image_height)) {

    factor_width  = static_cast<float>(image_width)  / static_cast<float>(image_height) ;
    factor_height = static_cast<float>(image_height) / static_cast<float>(image_width)  ;
    width = 0.0f ;
    height =0.0f ;

    if (image_width == image_height) {
      if (frame_image_height > frame_image_width) {
        width  = frame_image_width ;
        height = frame_image_width ;
      }
      else if (height < frame_image_width) {
        width  = frame_image_height ;
        height = frame_image_height ;
      }
      else {
        width  = frame_image_height ;
        height = frame_image_height ;
      }
    }
    if (factor_width < factor) {
      while (height < frame_image_height) {
        if ((height + factor_height) >= height) {
          width *= factor_height ;
          break ;
        }

        width  += factor_width  ;
        height += factor_height ;
      }
    }
    else if (factor_width > factor) {

      while (width < frame_image_width) {

        if ((width + factor_width) >= frame_image_width) {
          height *= factor_width ;
          break  ;
        }
        width  += factor_width   ;
        height += factor_height  ;
      }
    }
  }

  else if ((image_width <= frame_image_width) && (image_height > frame_image_height)) {
    factor_width  = static_cast<float>(image_width) /  static_cast<float>(image_height) ;
    factor_height = static_cast<float>(image_height) / static_cast<float>(image_width) ;
    width  = 0.0f ;
    height = 0.0f ;


    if (image_width == image_height) {
      if (frame_image_height > frame_image_width) {
        width  = frame_image_width ;
        height = frame_image_width ;
      }
      else if (frame_image_height < frame_image_width) {
        width  = frame_image_height ;
        height = frame_image_height ;
      }
      else {
        width  = frame_image_height ;
        height = frame_image_height ;
      }
    }

    if (image_width > image_height) {

      if (factor_width < factor) {

        while (height < frame_image_height) {

          if ((height + factor_height) >= frame_image_height) {
            width *= factor_height ;
            break ;
          }

          width  += factor_width  ;
          height += factor_height ;
        }
      }
      else if (factor_width > factor) {

        while (width < frame_image_width) {

          if ((width + factor_width) >= width ) {
            height *= factor_width ;
            break  ;
          }
          width  += factor_width   ;
          height += factor_height  ;
        }
      }
    }
    if (image_width < image_height) {

      if (factor_width < factor) {         

        while (height < frame_image_height) {

          if ((height + factor_height) >= frame_image_height) {
            width *= factor_height ;
            break ;
          }
          width  += factor_width  ;
          height += factor_height ;
        }
      }
      else if (factor_width > factor) {

        while (width < frame_image_width) {
          if ((width + factor_width) >= width) {
            height *= factor_width ;
            break  ;
          }
          width  += factor_width  ;
          height += factor_height ;
       }

      }
    }

  }

  else if ((image_width <= frame_image_width) && (image_height <= frame_image_height)) {

    factor_width  = (float) image_width/image_height ;
    factor_height = (float) image_height/image_width ;

    width        = (float) image_width ;
    height       = (float) image_height ;


    /** BUG: if image_height > image_width and setting image_height < image_width
      *      I cannot compute the adapt width by setting height in a specific range
      */

    if (! (use_frame) ) {

      if (frame_image_height == frame_image_width) {

        if (width > height) {

          while (width < frame_image_width) {
            width++  ;
            height += factor_height ;
          }
        }
        else if (width < height) {

          while (height < frame_image_height) {
            width += factor_width  ;
            height++ ;
          }
        }
        else {

          while (width < frame_image_width) {
           width++  ;
           height++ ;
          }
        }

      }
      else if (frame_image_height < frame_image_width && (frame_image_width > width) ) {

        while (width < frame_image_width) {
          width++ ;
          height += factor_height ;
        }
      }
      else if (frame_image_height < frame_image_width && (frame_image_height > height) ) {

        while (height < frame_image_height) {

          height++ ;
          width += factor_width ;
        }
      }
      else if (frame_image_height > frame_image_width && (frame_image_width > width) )  {

        while (width < frame_image_width) {
          width++ ;
          height += factor_height ;
        }
      }
      else if (frame_image_height > frame_image_width && (frame_image_height > height) )  {

        while (height < frame_image_height) {

          height++ ;
          width += factor_width ;
        }
      }

    }

  }

  return make_pair(static_cast<int>(roundf(width)), static_cast<int>(roundf(height))) ;
}

bool Resizer::assertion(int prec) const {

  char buf_1[32]={0} ;
  char buf_2[32]={0} ;

  sprintf(buf_1, "%.*f", prec,  width/height) ;
  sprintf(buf_2, "%.*f", prec,  factor_width) ;

  if  ( strcmp(buf_1, buf_2) != 0 ) {
   //fprintf(stdout,"Assertion error !!!\nBe aware of false positive !!!\n") ;
   return false ;
  }

  //fprintf(stdout,"Assertion successfull !!!\n") ;
  return true ;


}