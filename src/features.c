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

void first_pixel (char *filename) {
    unsigned char* data;
    int width, height, nbChannels;
    if (read_image_data(filename, &data, &width, &height, &nbChannels) != 0) {
        unsigned char r = data[0]; // Red component
        unsigned char g = data[1]; // Green component
        unsigned char b = data[2]; // Blue component
        printf("first_pixel: %d, %d, %d\n", r, g, b);

        free_image_data(data);    
    } 
}

void dimension(const char *filename) {
    unsigned char* data;
    int width, height, nbChannels;
    if (read_image_data(filename, &data, &width, &height, &nbChannels) != 0) {
        printf("dimension: %d, %d\n",width,height);      
    } else {
        printf("Error");
    }

    free_image_data(data);  
}

void second_line(const char *filename){
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
    
void print_pixel( char *source_path, int x, int y ){
    unsigned char *data;
    int width,height, nbChannels, index_R, index_G, index_B;

    if(read_image_data(source_path, &data, &width, &height, &nbChannels) == 0){
        fprintf(stderr, "Erreur de lecture du fichier.\n");
        return;
    }
    
    if((x<width)&&(y<height)){
        index_R = (y * width + x) * nbChannels;
        index_G = (y * width + x) * nbChannels + 1;
        index_B = (y * width + x) * nbChannels + 2;

    printf("print_pixel (%d, %d): %d, %d, %d\n", x, y, data[index_R], data[index_G], data[index_B]);
        
    }
    
    free_image_data(data);
}

void max_pixel(char *filename, FILE* out){
    int width, height, nbChannels, x, y, somme, maxSom, max_x, max_y;
   
    unsigned char* data;
    
    if(read_image_data(filename, &data, &width, &height, &nbChannels) == 0){
        fprintf(stderr, "Erreur de lecture du fichier.\n");
        return;
    }

    if(nbChannels < 3){
        fprintf(stderr, "Nombre de canaux de l'image inferieur a 3.\n");
        free_image_data(data);
    }
    
    maxSom = -1;
    max_x = max_y = 0;
    pixelRGB *pixel = NULL, *pixel_max = NULL;

    for(y=0; y<height; y++){
        for(x=0; x<width; x++){

            pixel = get_pixel(data, width, height, nbChannels, x, y);

            if(!pixel){
                continue;
            }

            somme = pixel->R + pixel->G + pixel->B;

            if(somme>maxSom){

                maxSom = somme;
                max_x = x;
                max_y = y;

            }
        }
    }

    pixel_max = get_pixel(data, width, height, nbChannels, max_x, max_y);

    if(pixel_max){
        fprintf(out, "max_pixel (%d, %d): %d, %d, %d\n", max_x, max_y, pixel_max->R, pixel_max->G, pixel_max->B);
    }else{
        printf("Erreur de recuperation du pixel.\n");
    }
    
    free_image_data(data);
    
}

void min_pixel(char *filename, FILE* out){
    int width, height, nbChannels, x, y, somme, minSom, min_x, min_y;
   
    unsigned char* data;
    //unsigned char R, G, B;
    
    if(read_image_data(filename, &data, &width, &height, &nbChannels) == 0){
        fprintf(stderr, "Erreur de lecture du fichier.\n");
        return;
    }

    if(nbChannels < 3){
        fprintf(stderr, "Nombre de canaux de l'image inferieur a 3.\n");
        free_image_data(data);
    }
    
    minSom = 256 * 3;
    /*maxR = maxG = maxB = max_x = max_y = 0;*/
    min_x = min_y = 0;
    pixelRGB *pixel = NULL, *pixel_min = NULL;

    for(y=0; y<height; y++){
        for(x=0; x<width; x++){

            pixel = get_pixel(data, width, height, nbChannels, x, y);

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

    pixel_min = get_pixel(data, width, height, nbChannels, min_x, min_y);

    if(pixel_min){
        fprintf(out, "min_pixel (%d, %d): %d, %d, %d\n", min_x, min_y, pixel_min->R, pixel_min->G, pixel_min->B);
    }else{
        printf("Erreur de recuperation du pixel.\n");
    }
    
    free_image_data(data);
    
}

void max_component(char component, char *source_path, FILE* out) {
    unsigned char *data;
    int width, height, nbChannels;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        int maxValue = -1;
        int maxX = 0, maxY = 0;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                
                pixelRGB* pixel = get_pixel(data, width, height, nbChannels, x, y);

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
        
        fprintf(out, "max_component %c (%d, %d): %d\n", component, maxX, maxY, maxValue);
        free_image_data(data);
    } 
}

void min_component(char component, char *source_path, FILE* out) {
    unsigned char *data;
    int width, height, nbChannels;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        int minValue = 256;
        int minX = 0, minY = 0;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                
                pixelRGB* pixel = get_pixel(data, width, height, nbChannels, x, y);

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
        
        fprintf(out, "min_component %c (%d, %d): %d\n", component, minX, minY, minValue);
        free_image_data(data);
    } 
}

void stat_report(const char* FileImage){
    int width, height, nbChannels;
    unsigned char* data;

    if(read_image_data(FileImage, &data, &width, &height, &nbChannels) == 0){
        fprintf(stderr, "Erreur lors de la lecture de l'image.\n");
        return;
    }


    FILE *fichier = fopen("start_report.txt", "w");

    if (fichier == NULL){
        fprintf(stderr, "Erreur lors de la création du fichier.\n");
        free_image_data(data);
        return;
    }

    
    fprintf(fichier, "\n"); 
    max_pixel((char*)FileImage, fichier);

    fprintf(fichier, "\n"); 
    min_pixel((char*)FileImage, fichier);

    fprintf(fichier, "\n");
    max_component('R', (char*)FileImage, fichier);

    fprintf(fichier, "\n");
    max_component('G', (char*)FileImage, fichier);

    fprintf(fichier, "\n");
    max_component('B', (char*)FileImage, fichier);

    fprintf(fichier, "\n"); 
    min_component('R', (char*)FileImage, fichier);

    fprintf(fichier, "\n");
    min_component('G', (char*)FileImage, fichier);

    fprintf(fichier, "\n");
    min_component('B', (char*)FileImage, fichier);
    
    fclose(fichier);
    free_image_data(data);
    printf("Le fichier startReport a ete cree avec succes.\n");
}


void color_gray(char *source_path){
    unsigned char *data;
    int width, height, nbChannels;
    
    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        for (int y=0; y<height; y=y+1){
            for (int x=0; x<width; x=x+1){
                pixelRGB* a = get_pixel(data, width, height, nbChannels, x, y); 
                unsigned char value = (a->R + a->G + a->B) /3 ;
                a->R = value;
                a->G = value;
                a->B = value;
            }
        }
        write_image_data("image_out.bmp", data, width, height); 
        printf("Image convertie en gris : image_out.bmp\n"); 
    }

    free_image_data(data);

}      


        
void color_invert(char *source_path) {
    unsigned char *data;
    int width, height, nbChannels;
    
    if (read_image_data(source_path, &data, &width, &height, &nbChannels) !=0){

        int i;
        for (i = 0; i < width * height * nbChannels; i++) {
            data[i] = 255 - data[i];
        }
        
        write_image_data("image_out.bmp", data, width, height);
    }   
}


void rotate_cw(char *source_path) {
    unsigned char *data;
    int width, height, nbChannels;
    
    read_image_data(source_path, &data, &width, &height, &nbChannels);
    
    unsigned char *memoire = malloc(width * height * nbChannels);
    
    int i, j, c;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            for (c = 0; c < nbChannels; c++) {
                memoire[(j * height + (height - 1 - i)) * nbChannels + c] = data[(i * width + j) * nbChannels + c];
            }
        }
    }
    
    write_image_data("image_out.bmp", memoire, height, width);
    free(memoire);
    free_image_data(data);
}

void color_gray_luminance (char *source_path) {
    unsigned char *data;
    int width, height, nbChannels;
    
    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        for (int y=0; y<height; y=y+1){
            for (int x=0; x<width; x=x+1){
                pixelRGB* a = get_pixel(data, width, height, nbChannels, x, y); 
                unsigned char value = 0.21 * a->R + 0.72 * a->G + 0.07 * a->B;
                a->R = value;
                a->G = value;
                a->B = value;

            }
        }
    write_image_data("image_out.bmp", data, width, height); 
    printf("Image convertie en niveaux de gris : image_out.bmp\n");  
    }

    free_image_data(data);
}

void rotate_acw(char *source_path) {
    unsigned char *data;
    int width, height, nbChannels;
    
    read_image_data(source_path, &data, &width, &height, &nbChannels);
    
    unsigned char *memoire = malloc(width * height * nbChannels);
    
    int i, j, c;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            for (c = 0; c < nbChannels; c++) {
                memoire[((width - 1 - j) * height + i) * nbChannels + c] = data[(i * width + j) * nbChannels + c];
            }
        }
    }
    
    write_image_data("image_out.bmp", memoire, height, width);
    free(memoire);
    free_image_data(data);
}

void color_green(char *source_path){
    unsigned char *data;
    int width, height, nbChannels;
    
    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        for (int y=0; y<height; y=y+1){
            for (int x=0; x<width; x=x+1){
                pixelRGB* a = get_pixel(data, width, height, nbChannels, x, y); 
                a->R = 0;
                a->B = 0;
            }
        }
        write_image_data("image_out.bmp", data, width, height); 
        printf("Image convertie en vert : image_out.bmp\n"); 
    }

    free_image_data(data);
}

void color_blue(char *source_path){
    unsigned char *data;
    int width, height, nbChannels;
    
    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        for (int y=0; y<height; y=y+1){
            for (int x=0; x<width; x=x+1){
                pixelRGB* a = get_pixel(data, width, height, nbChannels, x, y); 
                a->R = 0;
                a->G = 0;
            }
        }
        write_image_data("image_out.bmp", data, width, height); 
        printf("Image convertie en bleue : image_out.bmp\n"); 
    }

    free_image_data(data);
}

void color_red(char *source_path){
    unsigned char *data;
    int width, height, nbChannels;
    
    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        for (int y=0; y<height; y=y+1){
            for (int x=0; x<width; x=x+1){
                pixelRGB* a = get_pixel(data, width, height, nbChannels, x, y); 
                a->G = 0;
                a->B = 0;
            }
        }
        write_image_data("image_out.bmp", data, width, height); 
        printf("Image convertie en rouge : image_out.bmp\n"); 
    }

    free_image_data(data);
}

void mirror_horizontal (const char *fileImage_input, const char *fileImage_ouput){
    unsigned char *data_input, *data_output; 
    int width, height, nbChannels, x, y, index_input, index_output, i;

    if(read_image_data(fileImage_input, &data_input, &width, &height, &nbChannels) == 0){
        fprintf(stderr, "Erreur lors de la lecture de l'image.\n");
        return;
    }

    data_output = malloc(sizeof(unsigned char)*width*height*nbChannels);

    for (y=0; y<height; y++){
        for(x=0; x<width; x++){
            index_input = ((y * width) + x) * nbChannels;
            index_output = ((y * width) +(width - 1 - x)) * nbChannels;

            for (i=0; i<nbChannels; i++){
                data_output[index_output + i] = data_input[index_input + i];
            }
        }
    }

    write_image_data(fileImage_ouput, data_output, width, height);

    free_image_data(data_input);
    free_image_data(data_output);


}

void mirror_vertical (const char *fileImage_input, const char *fileImage_ouput){
    unsigned char *data_input, *data_output; 
    int width, height, nbChannels, x, y, index_input, index_output, i;

    if(read_image_data(fileImage_input, &data_input, &width, &height, &nbChannels) == 0){
        fprintf(stderr, "Erreur lors de la lecture de l'image.\n");
        return;
    }

    data_output = malloc(sizeof(unsigned char)*width*height*nbChannels);

    for (y=0; y<height; y++){
        for(x=0; x<width; x++){
            index_input = ((y * width) + x) * nbChannels;
            index_output = (((height - 1 - y) * width) + x) * nbChannels;

            for (i=0; i<nbChannels; i++){
                data_output[index_output + i] = data_input[index_input + i];
            }
        }
    }

    write_image_data(fileImage_ouput, data_output, width, height);

    free_image_data(data_input);
    free_image_data(data_output);


}

void mirror_total (const char *fileImage_input, const char *fileImage_ouput){

    unsigned char *data_input, *data_output; 
    int width, height, nbChannels, x, y, index_input, index_output, i;

    if(read_image_data(fileImage_input, &data_input, &width, &height, &nbChannels) == 0){
        fprintf(stderr, "Erreur lors de la lecture de l'image.\n");
        return;
    }

    data_output = malloc(sizeof(unsigned char)*width*height*nbChannels);

    for (y=0; y<height; y++){
        for(x=0; x<width; x++){
            index_input = ((y * width) + x) * nbChannels;
            index_output = (((height - 1 - y) * width) + (width - 1 - x)) * nbChannels;

            for (i=0; i<nbChannels; i++){
                data_output[index_output + i] = data_input[index_input + i];
            }
        }
    }

    write_image_data(fileImage_ouput, data_output, width, height);

    free_image_data(data_input);
    free_image_data(data_output);

    

}

void color_desaturate(char *source_path) {

    unsigned char min(unsigned char a, unsigned char b, unsigned char c){
        unsigned char min_val = a ;
        if(b<min_val) min_val=b;
        if(c<min_val) min_val=c;
        return min_val; 
    }

    unsigned char max(unsigned char a, unsigned char b, unsigned char c){
        unsigned char max_val = a;
        if(b>max_val) max_val = b;
        if(c>max_val) max_val = c;
        return max_val;
    }

    
    unsigned char *data;
    int width, height, nbChannels;
    unsigned char R, G, B;
    unsigned char new_val;

    if (read_image_data(source_path, &data, &width, &height, &nbChannels) !=0){
        for(int y=0; y<height; y++){
            for(int x=0; x<width; x++){
                pixelRGB* a = get_pixel(data, width, height, nbChannels, x, y);
                R = a->R;
                G = a->G;
                B = a->B;

                new_val = (min(R, G, B)+max(R, G, B))/2;
                a->R = new_val;
                a->G = new_val;
                a->B = new_val;
            }
        }
    write_image_data("image_out.bmp", data, width, height);
    printf("Image desaturee : image_out.bmp\n");
    }

    free_image_data(data);
}

void scale_crop(char *source_path, int center_x, int center_y, int crop_width, int crop_height) {
    unsigned char* data;
    int width, height, nbChannels;
    
    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        unsigned char* cropped = malloc(crop_width * crop_height * nbChannels);
        
        int start_x = center_x - crop_width / 2;
        int start_y = center_y - crop_height / 2;
        
        int i, j, c;
        for (i = 0; i < crop_height; i++) {
            for (j = 0; j < crop_width; j++) {
                int src_x = start_x + j;
                int src_y = start_y + i;
                
                for (c = 0; c < nbChannels; c++) {
                    if (src_x >= 0 && src_x < width && src_y >= 0 && src_y < height) {
                        cropped[(i * crop_width + j) * nbChannels + c] = data[(src_y * width + src_x) * nbChannels + c];
                    } else {
                        cropped[(i * crop_width + j) * nbChannels + c] = 0;
                    }
                }
            }
        }
        
        write_image_data("image_out.bmp", cropped, crop_width, crop_height);
        free(cropped);
        free_image_data(data);
    }
    else{
        printf("Erreur");
    }
}

void scale_nearest(char* source_path, float scale) {
    unsigned char* data;
    int width, height, nbChannels;
    
    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        
        int new_width = (int)(width * scale);
        int new_height = (int)(height * scale);
        
        unsigned char *scaled = malloc(new_width * new_height * nbChannels);
        
        int i, j, c;
        for (i = 0; i < new_height; i++) {
            for (j = 0; j < new_width; j++) {
                
                int src_x = (int)(j / scale);
                int src_y = (int)(i / scale);
                
                if (src_x >= width) src_x = width - 1;
                if (src_y >= height) src_y = height - 1;
                
                for (c = 0; c < nbChannels; c++) {
                    scaled[(i * new_width + j) * nbChannels + c] = data[(src_y * width + src_x) * nbChannels + c];
                }
            }
        }
        
        write_image_data("image_out.bmp", scaled, new_width, new_height);
        free(scaled);
        free_image_data(data);
    }
}

void scale_bilinear(char* source_path, float scale) {
    unsigned char* data;
    int width, height, nbChannels;
    
    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
        
        int new_width = (int)(width * scale);
        int new_height = (int)(height * scale);
        
        unsigned char* scaled = malloc(new_width * new_height * nbChannels);
        
        int i, j, c;
        for (i = 0; i < new_height; i++) {
            for (j = 0; j < new_width; j++) {
                
                float src_x = j / scale;
                float src_y = i / scale;
                
                int x1 = (int)src_x;
                int y1 = (int)src_y;
                int x2 = x1 + 1;
                int y2 = y1 + 1;
                
                if (x2 >= width) x2 = width - 1;
                if (y2 >= height) y2 = height - 1;
                
                float dx = src_x - x1;
                float dy = src_y - y1;
                
                for (c = 0; c < nbChannels; c++) {
                    unsigned char p1 = data[(y1 * width + x1) * nbChannels + c];
                    unsigned char p2 = data[(y1 * width + x2) * nbChannels + c];
                    unsigned char p3 = data[(y2 * width + x1) * nbChannels + c];
                    unsigned char p4 = data[(y2 * width + x2) * nbChannels + c];
                    
                    float top = p1 * (1 - dx) + p2 * dx;
                    float bottom = p3 * (1 - dx) + p4 * dx;
                    float result = top * (1 - dy) + bottom * dy;
                    
                    scaled[(i * new_width + j) * nbChannels + c] = (unsigned char)result;
                }
            }
        }
        
        write_image_data("image_out.bmp", scaled, new_width, new_height);
        free(scaled);
        free_image_data(data);
    } else{
        printf("Erreur");
    }
}