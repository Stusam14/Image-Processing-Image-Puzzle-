/**
 * @file imagepuzzledriver.cpp
 * @author Siaybonga Sengwayo
 * @brief 
 * @version 0.1
 * @date 2024-03-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "imagepuzzle.h"
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * @brief This is the driver file 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char * argv[]){


    if ( argc != 4 ){
        std::cout << "Invalid input params" << std::endl;
        return 0;
    }

    if(std::stoi((argv[1]))%2 == 0){
        std::cout << "grid_size must be odd \n";
        return 0;
    }

    int grid_size =std::stoi(argv[1]);
    std::string image_name = argv[2];
    int no_of_swaps = std::stoi(argv[3]);

    SNGSIY006::TileManager tile_manager
    (grid_size,no_of_swaps);

    tile_manager.read_image
    (image_name);
    tile_manager.extract_and_swap_image();
    
    

        
    
    return 0;
}

