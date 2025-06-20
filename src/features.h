#include <stdio.h>

#ifndef FEATURES_H
#define FEATURES_H


void helloWorld();

void tenth_pixel(char*);

void first_pixel (char *source_path);

void dimension(const char*);

void second_line(const char*);

void print_pixel( char *filename, int x, int y );

void max_pixel(char *filename,FILE* out);

void min_pixel(char *filename, FILE* out);

void max_component(char component, char *source_path, FILE* out);

void min_component(char component, char *source_path, FILE* out);

void stat_report(const char* FileImage);

void color_gray(char *source_path);

void color_invert(char *source_path);

void rotate_cw(char*source_path);

void color_gray_luminance (char *source_path);

void rotate_acw(char*source_path);

void color_green (char *source_path);

void color_blue (char *source_path);

void color_red (char *source_path);

void mirror_horizontal (const char *fileImage_input, const char *fileImage_ouput);

void mirror_vertical (const char *fileImage_input, const char *fileImage_ouput);

void mirror_total (const char *fileImage_input, const char *fileImage_ouput);

void color_desaturate (char *source_path);

void scale_crop(char *source_path, int center_x, int center_y, int crop_width, int crop_height);

void scale_nearest(char *source_path, float scale);

void scale_bilinear(char *source_path, float scale);

#endif
