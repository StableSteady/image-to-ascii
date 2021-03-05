#include <vector>
#include <iostream>

#define invalid_argument -1

std::vector<std::vector<double>> make_array(unsigned char* c, int w, int h)
{
    std::vector<std::vector<int>> r(w, std::vector<int>(h)),
                                  g(w, std::vector<int>(h)),
                                  b(w, std::vector<int>(h));
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
        throw(invalid_argument);
    }
}