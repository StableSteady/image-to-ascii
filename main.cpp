#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_resize.h"

#include "draw.hpp"
#include "get_pixel.hpp"

#define invalid_filename -2

int main()
try{
    int input_w = 0, input_h = 0, input_ch = 0,
        out_w = 0, out_h = 0, out_ch = 0;

    std::string img_name = "";

    std::cout << "Enter image filename: ";
    std::cin >> img_name;
    const char* f = img_name.c_str();

    unsigned char *image = stbi_load(f, &input_w, &input_h, &input_ch, 3);
    if(image == nullptr) throw(invalid_filename);

    unsigned char *out_image = nullptr;

    std::cout << "Do you want to resize the image before conversion? (y/n)\n";
    char c = ' ';
    std::cin >> c;

    switch(c){
        case 'y': case 'Y':
        std::cout << "Enter image resolution in pixels: (width, height)\n";
        std::cin >> out_w >> out_h;
        out_image = new unsigned char[out_w*out_h*3];
        stbir_resize_uint8( image , input_w , input_h , 0,
                            out_image, out_w, out_h, 0, 3);
        break;

        case 'n': case 'N':
        out_image = image;
        out_w = input_w;
        out_h = input_h;
        break;

        default:
        throw(invalid_argument);
    }
  
    std::vector<std::vector<double>> brightness(out_w, std::vector<double>(out_h));
    
    brightness = make_array(out_image, out_w, out_h);
    draw(brightness, out_h, out_w, img_name);

    if(c =='y' || 'Y') delete[] out_image;
}

catch(int s){
    switch(s){
        case -1:
        std::cout << "Invalid argument. Exiting...\n";
        break;

        case -2:
        std::cout << "Failed to load image. Exiting...\n";
        break;
    }
}