#include <estia-image.h>
#include <stddef.h>

#include "utils.h"

/**
 * @brief Here, you have to define functions of the pixel struct : getPixel and setPixel.
 * 
 */
pixelRGB* getPixel( unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y ){
    //int x, y;
    //unsigned char* Data;
    unsigned int position;
    if((x>=width) || (y>=height) || (!data) || (n<3)){
        return NULL;
    }
    else{
        position = (y * width + x) * n;
        return (pixelRGB *) &(data[position]);
    }
    }
