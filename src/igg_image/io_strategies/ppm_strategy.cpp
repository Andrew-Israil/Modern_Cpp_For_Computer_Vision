#include "igg_image/io_strategies/ppm_strategy.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>

namespace igg {

bool PpmIoStrategy::Write(const std::string& file_name,
                          const ImageData& data) const {

}

ImageData PpmIoStrategy::Read(const std::string& file_name) const{
    using namespace std;
    
    ifstream infile("ppmfile.txt", ios_base ::in);
    string line, format;

    ImageData img;
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