# building_a_video_from_a_large_image

A program which creates images of swapped tiles from a pgm image, it creates a puzzle version of the image that can be processed and solved.

This program was/is built as part of an Assingment for my C++ course, it mainly focues on the basics of programming in C++

# Getting started

- Use the command : "make" to compile the code files
- use the command : ./muPuzzle -s <int>(grid_size) -i <string>(image_name) -n <int>(no_swaps)

# The main behaviour of program files:

# The imagepuzzle.h file

imagepuzzle.h file contains all the function prototypes implemented in the imagepuzzle.cpp file , it has classes declared holding the methods, it consist of construtors and destructors for memory clean up after use.

# The imagepuzzle.cpp file

The imagepuzzle consist of the necessary code iplementation for reading the pgm image file , storing the data from the image , carving the image into a grid , and swapping the tile then storing the combine images for outputting as separate image file after iteration or number of swaps.

# The imagepuzzledriver.cpp file

This is the entry point of the program , it contains function calls for executions , and is an entry point for command line inputs.

# Makefile

Build : use "make"

clean command : cleans up extra object and target files after compiling.
