#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_resize.h"

std::vector<std::vector<double>> make_array(std::vector<std::vector<int>>& r, std::vector<std::vector<int>>& g, 
                                            std::vector<std::vector<int>>& b, unsigned char* c, int w, int h)
{
    std::vector<std::vector<double>> average(w, std::vector<double>(h)), 
                                     lightness(w, std::vector<double>(h)), 
                                     perception(w, std::vector<double>(h));
    for(int i = 0; i < w; ++i){
        for(int j = 0; j < h; ++j){
            r[i][j] = c[3*(j*w + i) + 0];
            g[i][j] = c[3*(j*w + i) + 1];
            b[i][j] = c[3*(j*w + i) + 2];

            average[i][j] = (r[i][j] + g[i][j] + b[i][j])/3;
            lightness[i][j] = (std::max(std::max(r[i][j], g[i][j]), b[i][j]) + std::min(std::min(r[i][j], g[i][j]), b[i][j]))/2;
            perception[i][j] = 0.21*r[i][j] + 0.72*g[i][j] + 0.07*b[i][j];
        }
    }
    std::cout << "Which brightness algorithm do you want to use? Average, Lightness or Perception? (1/2/3)\n";
    int num;
    std::cin >> num;
    switch(num){
        case 1:
        return average;
        case 2:
        return lightness;
        case 3:
        return perception;
        default:
        return average;
    }
}

void draw(std::vector<std::vector<double>>& v, int h, int w){
    std::vector<char> ascii{'`','^','"',',',':',';','I','l','!','i','~','+',
                            '_','-','?',']','[','}','{','1',')','(','|','t',
                            'f','j','r','x','n','u','v','c','z','X','Y','U',
                            'J','C','L','Q','0','O','Z','m','w','q','p','d',
                            'b','k','h','a','o','*','#','M','W','&','8','%',
                            'B','@','$'};
    std::ofstream text("out.txt");
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            for(int k = 0; k < 2; ++k){
                text << ascii[round(v[j][i]/4.12)];
            }
        }
        text << '\n';
    }
    text.close();
}

int main(){
    int input_w = 0, input_h = 0, input_ch = 0,
        out_w = 0, out_h = 0, out_ch = 0;

    std::string img_name = "";

    std::cout << "Enter image filename: ";
    std::cin >> img_name;
    const char* f = img_name.c_str();

    unsigned char *image = stbi_load(f, &input_w, &input_h, &input_ch, 3);
    unsigned char *out_image = nullptr;

    std::cout << "Do you want to resize the image before conversion? (y/n)\n";
    char c = ' ';
    std::cin >> c;

    if(c == 'y'){
        std::cout << "Enter image resolution in pixels: (width, height)\n";
        std::cin >> out_w >> out_h;
        out_image = new unsigned char[out_w*out_h*3];
        stbir_resize_uint8( image , input_w , input_h , 0,
                            out_image, out_w, out_h, 0, 3);
    } else{
        out_image = image;
        out_w = input_w;
        out_h = input_h;
    }    
    std::vector<std::vector<double>> brightness(out_w, std::vector<double>(out_h));
    std::vector<std::vector<int>> r(out_w, std::vector<int>(out_h)),
                                  g(out_w, std::vector<int>(out_h)),
                                  b(out_w, std::vector<int>(out_h));
    
    brightness = make_array(r, g, b, out_image, out_w, out_h);
    draw(brightness, out_h, out_w);
}