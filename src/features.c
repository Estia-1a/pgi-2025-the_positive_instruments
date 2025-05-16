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
    unsigned char **data;
    int width, height, channel_count;
    int result = read_image_data(source_path, &data, &width, &height, &channel_count);
    
    unsigned char r = data[0][0]; // Red component
    unsigned char g = data[0][1]; // Green component
    unsigned char b = data[0][2]; // Blue component

    printf("first_pixel: %d, %d, %d\n", r, g, b);
}

void dimension(const char* filename) {
    unsigned char* data;
    int width, height, nbChannels;
    read_image_data(filename, &data, &w, &h, &nbChannels);
    printf("Dimensions %s: %d x %d\n", filename, w, h);
    free_image_data(data);
}
