#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld() {
    printf("Hello World !");
}

void first_pixel (char *source_path) {
    unsigned char* data;
    int width, height, nbChannels;
    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        // HERE
        unsigned char r = data[0]; // Red component
        unsigned char g = data[1]; // Green component
        unsigned char b = data[2]; // Blue component
        printf("first_pixel: %d, %d, %d\n", r, g, b);

        free_image_data(data);    
    } else {
        printf("Error");
    }
}

void dimension(const char* filename) {
    unsigned char* data;
    int width, height, nbChannels;
    if (read_image_data(filename, &data, &width, &height, &nbChannels) != 0) {
        printf("dimension: %d, %d\n",width,height);      
    } else {
        printf("Error");
    }

    free_image_data(data);  
}

void second_line(const char* filename){
    unsigned char* data;
    int width, height, nbChannels;
    if (read_image_data(filename, &data, &width, &height, &nbChannels) != 0)  {
        printf("Second_line: %d, %d, %d\n", data[3*width], data[3*width+1], data[3*width+2]);
    } else {
        printf("Error");
    }
    free_image_data(data);
}


void tenth_pixel(char* filename){
    unsigned char* data;
    int width, height, nbChannels;
    if (read_image_data(filename, &data, &width, &height, &nbChannels) != 0)  {
        int pixel_index = 9;
        int data_index = pixel_index * nbChannels;
        unsigned char r = data[data_index];     
        unsigned char g = data[data_index + 1]; 
        unsigned char b = data[data_index + 2];
        printf("tenth_pixel: %d, %d, %d\n", r, g, b);
        free_image_data(data);
    } else {
        printf("Error");
    }
}
    
void print_pixel( char *filename, int x, int y ){
    unsigned char *data;
    int width,height, nbChannels;
    pixelRGB *pixel1;
    if(read_image_data(filename, &data, &width, &height, &nbChannels) == 0){
        fprintf(stderr, "Erreur de lecture du fichier.\n");
        return;
    }
    
    pixel1 = getPixel(data, width, height, nbChannels, x, y);

    if(!pixel1){
        fprintf(stderr, "Erreur d indexage.\n");
        return;
    }
    printf("print_pixel(%d, %d): %d, %d, %d\n", x, y, pixel1->R, pixel1->G, pixel1->B);    
    //getPixel(data, width, height, nbChannels, x, y);
}

void max_pixel(char *filename){
    unsigned char R, G, B;
    int width, height, nbChannels, x, y, somme, maxSom, maxR,maxG, maxB, max_x, max_y;
    //pixelRGB *pixel2;
    position = (y * width + x) * nbChannels;
    
    if(read_image_data(filename, &data, &width, &height, &nbChannels) == 0){
        fprintf(stderr, "Erreur de lecture du fichier.\n");
        return;
    }

    //pixel2 = getPixel(data, width, height, nbChannels, x, y);
    unsigned char* data[position];
    R = data[position];
    G = data[position+1];
    B = data[position+2];
    somme = R + G + B;
    if(!pixel2){
        for(y=0; y<height; y++){
            for(x=0; x<width; x++){
                if(somme>maxSom){
                    maxSom = somme;
                    maxR = R;
                    maxG = G;
                    maxB = B;
                    max_x = x;
                    max_y = y;

                }
            }
        }
        printf("max_pixel (%d, %d): %d, %d, %d", max_x, max_y, maxR, maxG, maxB);
    }
}