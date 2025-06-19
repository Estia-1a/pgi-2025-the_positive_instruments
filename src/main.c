#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <estia-image.h>
#include <getopt.h>

#include "features.h"
#include "utils.h"
#include "argsparse.h"

int main(int argc, char **argv) {
  /*To use debug mode: 
   - add --debug: freud.exe --debug -f images/input/image.jpeg
   or 
   - Simply run your compiled project with start button on the blue menu bar at the bottom of the VS Code window.
   */

  /*DO NOT EDIT THIS PART*/
  Config configuration ;
  parse_arguments( argc, argv, &configuration ) ;
  check_debug_mode(configuration);
  check_file();
  /* END */

  /* Use "if ( strncmp( command, <commandname>, 9 ) == 0 )" to check if your <commandname> is called by program.*/
  /* Example with helloworld command
   * If helloworld is a called command: freud.exe -f images/input/image.jpeg -c helloworld 
   */
  if ( strncmp( configuration.command, "helloworld", 10 ) == 0 ) {
    /* helloworld() function is defined in feature.h and implemented in feature.c */
    helloWorld();
  } else if ( strncmp( configuration.command, "first_pixel", 3 ) == 0 ) {
    /* helloworld() function is defined in feature.h and implemented in feature.c */
    first_pixel(configuration.filenames[0]);
  } else if ( strncmp( configuration.command, "dimension",3) == 0 ) {
    /* dimension() function is defined in feature.h and implemented in feature.c */
    dimension( configuration.filenames[0] );
  } else if (strncmp(configuration.command, "second_line", 6) == 0){
    second_line(configuration.filenames[0]);
  } else if ( strncmp( configuration.command, "tenth_pixel",4) == 0 ) {
    tenth_pixel( configuration.filenames[0] );
  } else if (strncmp(configuration.command, "print_pixel", 10) == 0){
    int x, y;
    x = atoi(configuration.arguments[0]);
    y = atoi(configuration.arguments[1]);
    print_pixel(configuration.filenames[0], x, y);
  } else if (strncmp(configuration.command, "max_pixel", 6) == 0){
    max_pixel(configuration.filenames[0], stdout);
  } else if (strncmp(configuration.command, "min_pixel", 6) == 0){
    min_pixel(configuration.filenames[0], stdout);
  }else if (strncmp(configuration.command, "max_component", 13) == 0) {
    char comp = configuration.arguments[0][0];  // ex: 'R'
    max_component(comp, configuration.filenames[0], stdout);
  } else if (strncmp(configuration.command, "min_component", 13) == 0) {
    char comp = configuration.arguments[0][0];  // ex: 'R'
    min_component(comp, configuration.filenames[0], stdout);
  } else if (strncmp(configuration.command, "stat_report", 11) == 0){

    stat_report(configuration.filenames[0]);
  } /*else if(strncmp(configuration.command, "write_image_data", 11) == 0){
    write_image_data(configuration.filenames[0]);
  }*/
  else if (strncmp(configuration.command, "color_gray", 10) == 0) {
    color_gray(configuration.filenames[0]);
  }else if (strncmp(configuration.command, "color_invert", 12) == 0) {
    color_invert(configuration.filenames[0]);
  }else if (strncmp(configuration.command, "rotate_cw", 9) == 0) {
    rotate_cw(configuration.filenames[0]);
  }else if (strncmp(configuration.command, "color_gray_luminance", 20) == 0) {
    color_gray_luminance(configuration.filenames[0]);
  }else if (strncmp(configuration.command, "rotate_acw", 9) == 0) {
    rotate_acw(configuration.filenames[0]);
  }else if (strncmp(configuration.command, "color_green", 11) == 0) {
    color_green(configuration.filenames[0]);
  }else if (strncmp(configuration.command, "color_blue", 10) == 0) {
    color_blue(configuration.filenames[0]);
  }else if (strncmp(configuration.command, "color_red", 9) == 0) {
    color_red(configuration.filenames[0]);
  }else if (strncmp(configuration.command, "color_desaturate", 15)==0){
    color_desaturate(configuration.filenames[0]);  
  }
  else if(strncmp(configuration.command, "mirror_horizontal", 9) == 0){
    mirror_horizontal(configuration.filenames[0], "image_out.bmp");
  }
  else if(strncmp(configuration.command, "mirror_vertical", 9) == 0){
    mirror_vertical(configuration.filenames[0], "image_out.bmp");
  }
  else if(strncmp(configuration.command, "mirror_total", 9) == 0){
    mirror_total(configuration.filenames[0], "image_out.bmp");
  }
  else if (strncmp(configuration.command, "color_desaturate", 15)==0){
    color_desaturate(configuration.filenames[0]);
  }
  /*
   * TO COMPLETE
   */
  
  return 0;
}