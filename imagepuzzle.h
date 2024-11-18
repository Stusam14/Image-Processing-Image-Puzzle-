/**
 * Include guides to prevent the .h file from being called
 * more than once.
*/

#ifndef _IP_HEADER
#define _IP_HEADER
#include <vector>
#include <iostream>
#include <fstream>


namespace SNGSIY006{
    class Tile;
/**
 * class definition for Tile Management
*/
    class TileManager{

        private:
            int width;
            int height;
            int grid_size;
            int no_swaps;
            int horizontal,vertical;
            Tile** tile_board ;
            std::vector<std::vector<unsigned char>> tile_frame;
            std::vector<std::vector<unsigned char>> output_frame;
        public:
            TileManager(int grid_size , int no_swaps);
            
            Tile** get_board_mem();
            void read_image(std::string img_name);
            void extract_and_swap_image();
            void swap_tiles();
            void print_combined_image(int swap_index);
            ~TileManager();
    };

 /**
  * class definition for Tile , hold the images tiles
  * */  
    class Tile{
        public:
            int no_of_rows;
            int no_of_cols;
            Tile();
            Tile(int n_rows, int n_cols); 
            unsigned char** tile;
            unsigned char** get_tile_dyn_mem();     
    };

}

#endif