#include "imagepuzzle.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>

namespace SNGSIY006{

    /***********class constructors and de_constructors**********/
    
    TileManager::TileManager
    (int grid_size, int no_swaps): grid_size(grid_size), no_swaps(no_swaps){

        //initialising the tile_grid
        tile_board = new Tile*[grid_size];
        for(int r = 0; r < grid_size; r++){
            tile_board[r] = new Tile[grid_size];
        }
    };
    
   
   Tile::Tile(){};
   Tile::Tile
   (int n_rows, int  n_cols): no_of_rows(n_rows), no_of_cols(n_cols) {
        //initialising tile array
        tile = new unsigned char*[no_of_rows];
        for(int r = 0 ; r <  no_of_rows ; r++){
        tile[r] = new unsigned char[no_of_cols];
        }
    }; 

    /******************Class Methods****************/

/**
 * prints out the combine image tiles after swaps
*/
    void SNGSIY006::TileManager::print_combined_image
    (int swap_index) {
    int combined_image_height = height;
    int combined_image_width = width;

    std::vector<std::vector<unsigned char>> combined_image
    (combined_image_height, std::vector<unsigned char>
    (combined_image_width));

    int tile_height = height / grid_size;
    int tile_width = width / grid_size;

    for (int r = 0; r < grid_size; r++) {
        for (int c = 0; c < grid_size; c++) {
            unsigned char** tile_vector = (tile_board[r][c]).get_tile_dyn_mem();

            for (int row = 0; row < tile_height; row++) {
                for (int col = 0; col < tile_width; col++) {
                    combined_image[r * tile_height + row][c * tile_width + col] = tile_vector[row][col];
                }
            }
        }
    }

    // Generate the filename with the swap index
    std::ostringstream oss;
    oss << "image_" << swap_index << ".pgm";

    // Write the combined image to a file
    std::ofstream out(oss.str(), std::ios::binary);
    if (!out.is_open()) {
        std::cout << "Error opening file for writing.";
        return;
    }
    out << "P5" << "\n";
    out << "# Combined Image" << "\n";
    out << combined_image_width << " " << combined_image_height << "\n";
    out << 255 << "\n";
    for (int row = 0; row < combined_image_height; row++) {
        for (int col = 0; col < combined_image_width; col++) {
            out.write((char*)&combined_image[row][col], 1);
        }
    }
    out.close();
}

    //helper method to get the direction
    char get_direction
    (std::string directions){
         std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist
        (0, directions.size() - 1);
        return directions[dist(gen)];
    }

    /**method to swap individual tiles
     * in a image
    */
     void SNGSIY006::TileManager::swap_tiles
     (){
        horizontal = vertical = grid_size-1;

        
        int count=0;
        while(no_swaps != 0 ){

            std::string directions = "LURD";

            char direction = get_direction(directions);
            // iterates a number of times and give out the image each time
            switch (direction)
            {
            case 'U':
                if (vertical > 0) {
                    std::swap
                    (tile_board[vertical][horizontal], tile_board[vertical - 1][horizontal]);
                    vertical--; 
                    count++;
                }else{
                    no_swaps++;
                   
                }
                break;
            case 'D':
                if(vertical < grid_size - 1) { 
                    std::swap
                    (tile_board[vertical][horizontal], tile_board[vertical + 1][horizontal]);
                    vertical++;
                     count++;
                    
                }else{
                    no_swaps++;
                   
                }
                
                break;
            case 'L':

                if (horizontal > 0) { 
                    std::swap
                    (tile_board[vertical][horizontal], tile_board[vertical][horizontal - 1]);
                    horizontal--;
                    count++;
                }else{
                    no_swaps++;
                    
                }
            
                break;
            case 'R': 
                if (horizontal < grid_size - 1) { // Check if there's room to move right
                        std::swap
                        (tile_board[vertical][horizontal], tile_board[vertical][horizontal + 1]);
                        horizontal++;
                        count++;
                    }else{
                        no_swaps++;
                        
                    }
                break;
            }
        print_combined_image(count);
        no_swaps--;
        }
    }
    
    //getting the tile grid dynamic memory
    unsigned char** SNGSIY006::Tile::get_tile_dyn_mem
    (){
        return tile;
    }

    Tile** SNGSIY006::TileManager::get_board_mem
    (){
        return tile_board;
    }

    /**
     * method to extract image tiles , then add them and swap them
     * it uses helper metho such as swap to achieve this
    */
    void SNGSIY006::TileManager::extract_and_swap_image
    (){

       
        int no_of_cols = width / grid_size;
        int no_of_rows = height / grid_size;


/********extracting*/

        int xCount = 0;  int yCount = 0;
        for(int r = 0; r < grid_size; r++){
            xCount=0;
            for(int c = 0; c < grid_size; c++){                
                Tile tile_obj(no_of_rows,no_of_cols);
                unsigned char** tile_vector = tile_obj.get_tile_dyn_mem();

                for(int row = 0; row < no_of_rows; row++){
                    for(int col = 0; col < no_of_cols; col++){
                        if (r== grid_size-1 && c == grid_size-1){
                            tile_vector[row][col] = 0;//
                        }else {
                        tile_vector[row][col] = tile_frame[r*no_of_rows+row][c*no_of_cols + col];
                        }

                    }
                }
              
                tile_board[r][c]= tile_obj;
                xCount += no_of_cols;

            }
            yCount += no_of_rows;
        }  
        
/********extracting*/

/********extracting*/
        //swap method, swaps tiles
        swap_tiles();
/********extracting*/
    }


/**
 * method to read the image data and store it in
 * a dynamically allocated memory
*/
    void SNGSIY006::TileManager::read_image
    ( std::string image_name){
            
            std::ifstream image(image_name, std::ios::binary);
            std::string image_line;
           
            std::getline(image, image_line); // Skipping the 1st line
            std::string P_5 = image_line;
            std::getline(image, image_line); // Skipping the 2nd line
            std::getline(image, image_line); // Read image dimensions
            std::istringstream iss(image_line);
            iss >> width >> height;

            
            // Skip the 4th line
            std::getline(image, image_line);
            int greyscale = std::stoi(image_line);

            tile_frame = std::vector<std::vector<unsigned char>>
            (height, std::vector<unsigned char>(width));

            //writing to the char_vec
            for(int r=0; r < height; r++){
                for(int c= 0; c< width; c++){
                    char ch;
                    image.read(&ch,1);
                    tile_frame[r][c] = static_cast<unsigned char>(ch);
                }
            }
            

             
    
    } 

    
    // free up all the memory , after use
    TileManager::~TileManager(){
        // Free memory
        for (int i = 0; i < grid_size; ++i) {
            delete[] tile_board[i];
        }
      
        delete[] tile_board;
    }

}