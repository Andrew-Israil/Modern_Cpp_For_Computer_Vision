#include "igg_image/io_strategies/ppm_strategy.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>

namespace igg {

using namespace std;

bool PpmIoStrategy::Write(const std::string& file_name,
                          const ImageData& data) const {
    ofstream outfile(file_name);
    if(! outfile.is_open()){
        cerr << "Can't open " << file_name << endl;
        return false;
    }

    int max_pixels_per_row = 5; /*to comply with the recommendation of
                                  max 70 char per row*/
      
    outfile << "P3\n"
            << data.rows << " " << data.cols << "\n" 
            << data.max_val << "\n";
    
    for (int i = 0; i < data.rows * data.cols; ++i) {
        outfile << data.data[0][i] << " " 
                << data.data[1][i] << " " 
                << data.data[2][i] << "  ";

        if (((i + 1) % data.cols == 0) || ((i + 1) % max_pixels_per_row == 0)) 
            outfile << "\n";
    }

    return true;
}

ImageData PpmIoStrategy::Read(const std::string& file_name) const{
    ImageData img;
    ifstream infile(file_name, ios_base ::in);
    if (!infile) {
        cerr << "Error: Can not open file " << file_name << std::endl;
        return img;
    }

    string line, format;
    img.rows = -1;
    img.cols = -1;
    img.max_val = -1;

    while(getline(infile, line)){

        // skip comments
        if((line[0] == '#'))
            continue;
        
        if(format.empty()){
            format = line;
            if(format == "P3"){
                continue;
            } else {
                cerr << "ERROR: Unsupported Format, Not P3" << endl;
                return img;
            } 
        }
        
        if(img.rows == -1){
            stringstream ss(line);
            ss >> img.rows >> img.cols;
            continue;
        }

        if(img.max_val == -1){
            stringstream ss(line);
            ss >> img.max_val;
            break;
        }
    }

        enum Color{RED, GREEN, BLUE};
        img.data.resize(3);
        int pixels_count = img.rows* img.cols;
        img.data[RED].resize(pixels_count);
        img.data[GREEN].resize(pixels_count);
        img.data[BLUE].resize(pixels_count);

        for(int i = 0; i < pixels_count; ++i){
            infile >> img.data[RED][i];
            infile >> img.data[GREEN][i];
            infile >> img.data[BLUE][i];
        }

        return img;    
}

} // namespace igg