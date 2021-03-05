#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>

void draw(std::vector<std::vector<double>>& v, int h, int w, std::string img){
    std::vector<char> ascii{'`','^','"',',',':',';','I','l','!','i','~','+',
                            '_','-','?',']','[','}','{','1',')','(','|','t',
                            'f','j','r','x','n','u','v','c','z','X','Y','U',
                            'J','C','L','Q','0','O','Z','m','w','q','p','d',
                            'b','k','h','a','o','*','#','M','W','&','8','%',
                            'B','@','$'};
    std::ofstream text(img + ".txt");
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            for(int k = 0; k < 2; ++k){
                text << ascii[round(v[j][i]/4.12)];
            }
        }
        text << '\n';
    }
    text.close();
    std::cout << "Image printed successfully!.\n";
}