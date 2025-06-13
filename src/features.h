#ifndef FEATURES_H
#define FEATURES_H


void helloWorld();

void tenth_pixel(char*);

void first_pixel (char *source_path);

void dimension(const char*);

void second_line(const char*);

void print_pixel( char *filename, int x, int y );

void max_pixel(char *filename);

void min_pixel(char *filename);

void max_component(char component, char *source_path);

void min_component(char component, char *source_path);

void color_gray(const char* filename);

void color_invert(char *source_path);

#endif
