// xrr_mapMonitor


#include "xrr.h"


#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


#define PROGRAM_NAME "xrr_map"
#define VERSION "0.01"


void print_usage() {
  printf(
	 "Usage: xrr [options]\n"
	 "Options:\n"
	 "-h | --help         show usage\n"
	 "-v | --version      display version\n"
	 "-l | --list         list devices and monitors\n"
	 "-r | --reset        reset mapping of wacom devices\n"
	 "-i | --interactive  interactive mode (default)\n"
	 );
}






int main(int argc, char *argv[]) {

  int c = 0;

  static struct option long_options[] = {
    {"help",        no_argument, 0, 'h'},
    {"version",     no_argument, 0, 'v'},
    {"list",        no_argument, 0, 'l'},
    {"reset",       no_argument, 0, 'r'},
    {"interactive", no_argument, 0, 'i'},
    {0, 0, 0, 0}
  };

  int option_index = 0;
  
  
  while ((c = getopt_long(argc, argv, "hvl::r::i", long_options, &option_index)) != -1) {

    switch (c) {
    case 'h':
      print_usage();
      return EXIT_SUCCESS;
      break;
    case 'v':
      printf("Version: %s %s\n", PROGRAM_NAME, VERSION);
      return EXIT_SUCCESS;
      break;
    case 'l':
      listDevices();
      return EXIT_SUCCESS;
      break;
    case 'r':
      resetMap();
      return 0;
      break;
    case 'i':
      break;
    default: print_usage();
      exit(EXIT_FAILURE);
    }

  }

  
  if (optind < argc) {
    print_usage();
    exit(EXIT_FAILURE);
    /*
    printf ("non-option ARGV-elements: ");
    while (optind < argc) 
      printf("%s\n", argv[optind++]);
    putchar('\n');
    */
  }
  
 
  
  if (MapInteractive() >= 0) {
    puts("Mapping was sucessful");
    return EXIT_SUCCESS;
  }
  else {
    fprintf(stderr, "Mapping failed!\n");
    return EXIT_FAILURE;
  }
  
  return 0;
}
