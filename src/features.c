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
                        maxValue = pixel->R;
                        maxX = x;
                        maxY = y;
                    }
                } else if  (component == 'B') {
                    if (pixel->B > maxValue) {
                        maxValue = pixel->R;
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
