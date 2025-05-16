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

void dimension(const char* filename) {
    unsigned char* data;
    int width, height, nbChannels;
    if (read_image_data(filename, &data, &width, &height, &nbChannels) != 0){
        printf("Dimensions %s: %d x %d\n", filename, width, height);
        free_image_data(data);    
    } else {
        printf("Error");
    }
    
}

/** void second_line(char *source_path){
*    unsigned char* data;
*    int width, height, nbChannels;
*    if (read_image_data(source_path, &data, &width, &height, &nbChannels) != 0) {
*        printf("Dimensions %s: %d R %d G %d B\n", source_path, 3*width, 3*width+1, 3*width+2);
*        free_image_data(data);
*    } else {
*        printf("Error");
*    }

}**/