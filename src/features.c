#include <estia-image.h>
#include <stdio.h>
#include <stdlib.h>

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
    int width, height, nbChannels, x, y, somme, maxSom, max_x, max_y;
   
    unsigned char* data;
    //unsigned char R, G, B;
    
    if(read_image_data(filename, &data, &width, &height, &nbChannels) == 0){
        fprintf(stderr, "Erreur de lecture du fichier.\n");
        return;
    }

    if(nbChannels < 3){
        fprintf(stderr, "Nombre de canaux de l'image inferieur a 3.\n");
        free(data);
    }
    
    maxSom = -1;
    //maxR = maxG = maxB = max_x = max_y = 0;
    max_x = max_y = 0;
    pixelRGB *pixel = NULL, *pixel_max = NULL;

    for(y=0; y<height; y++){
        for(x=0; x<width; x++){

            pixel = getPixel(data, width, height, nbChannels, x, y);

            //position = (y * width + x) * nbChannels;
            if(!pixel){
                continue;
            }
            /*R = data[position];
            G = data[position+1];
            B = data[position+2];*/

            somme = pixel->R + pixel->G + pixel->B;

            if(somme>maxSom){

                maxSom = somme;
                /*maxR = R;
                maxG = G;
                maxB = B;*/
                max_x = x;
                max_y = y;

            }
        }
    }

    pixel_max = getPixel(data, width, height, nbChannels, max_x, max_y);

    if(pixel_max){
        printf("max_pixel (%d, %d): %d, %d, %d\n", max_x, max_y, pixel_max->R, pixel_max->G, pixel_max->B);
    }else{
        printf("Erreur de recuperation du pixel.\n");
    }
    
    free(data);
    
}

void min_pixel(char *filename){
    int width, height, nbChannels, x, y, somme, minSom, min_x, min_y;
   
    unsigned char* data;
    //unsigned char R, G, B;
    
    if(read_image_data(filename, &data, &width, &height, &nbChannels) == 0){
        fprintf(stderr, "Erreur de lecture du fichier.\n");
        return;
    }

    if(nbChannels < 3){
        fprintf(stderr, "Nombre de canaux de l'image inferieur a 3.\n");
        free(data);
    }
    
    minSom = 256 * 3;
    //maxR = maxG = maxB = max_x = max_y = 0;
    min_x = min_y = 0;
    pixelRGB *pixel = NULL, *pixel_min = NULL;

    for(y=0; y<height; y++){
        for(x=0; x<width; x++){

            pixel = getPixel(data, width, height, nbChannels, x, y);

            //position = (y * width + x) * nbChannels;
            if(!pixel){
                continue;
            }
            /*R = data[position];
            G = data[position+1];
            B = data[position+2];*/

            somme = pixel->R + pixel->G + pixel->B;

            if(somme<minSom){

                minSom = somme;
                /*maxR = R;
                maxG = G;
                maxB = B;*/
                min_x = x;
                min_y = y;

            }
        }
    }

    pixel_min = getPixel(data, width, height, nbChannels, min_x, min_y);

    if(pixel_min){
        printf("min_pixel (%d, %d): %d, %d, %d\n", min_x, min_y, pixel_min->R, pixel_min->G, pixel_min->B);
    }else{
        printf("Erreur de recuperation du pixel.\n");
    }
    
    free(data);
    
}

void max_component(char component, char *source_path) {
    unsigned char *data;
    int width, height, nbChannels;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        int maxValue = -1;
        int maxX = 0, maxY = 0;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                
                pixelRGB* pixel = getPixel(data, width, height, nbChannels, x, y);

                if (component == 'R') {
                    if (pixel->R > maxValue) {
                        maxValue = pixel->R;
                        maxX = x;
                        maxY = y;
                    }
                } else if  (component == 'G') {
                    if (pixel->G > maxValue) {
                        maxValue = pixel->G;
                        maxX = x;
                        maxY = y;
                    }
                } else if  (component == 'B') {
                    if (pixel->B > maxValue) {
                        maxValue = pixel->B;
                        maxX = x;
                        maxY = y;
                    }
                }
            }
        }
        
        printf("max_component %c (%d, %d): %d\n", component, maxX, maxY, maxValue);
        free_image_data(data);
    } 
}

void min_component(char component, char *source_path) {
    unsigned char *data;
    int width, height, nbChannels;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        int minValue = 256;
        int minX = 0, minY = 0;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                
                pixelRGB* pixel = getPixel(data, width, height, nbChannels, x, y);

                if (component == 'R') {
                    if (pixel->R < minValue) {
                        minValue = pixel->R;
                        minX = x;
                        minY = y;
                    }
                } else if  (component == 'G') {
                    if (pixel->G < minValue) {
                        minValue = pixel->G;
                        minX = x;
                        minY = y;
                    }
                } else if  (component == 'B') {
                    if (pixel->B < minValue) {
                        minValue = pixel->B;
                        minX = x;
                        minY = y;
                    }
                }
            }
        }
        
        printf("min_component %c (%d, %d): %d\n", component, minX, minY, minValue);
        free_image_data(data);
    } 
}
