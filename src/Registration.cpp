// Include all internal libraries
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <glob.h> 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>

// Include all external libraries
#include"Preprocess_function.h"


using namespace cv;
using namespace std;
using namespace filesystem;

// Warning
// Some element should be changed according to your own data, all strings matching names need to be changed, mine was: ex: 22/0103H3C.txt (volunteer 22, image 0103H3C)


// Main executable for Registering images data
int main(int argc, char** argv) 
{   
    // Get the path of the input images 
    string path = argv[1];
    string inputformat = {"jpg"};
    string registeredformat = {"txt"}; // Format can be added or changed here

    // Two vector to register the bytes and the input images
    vector<string> Registered;
    vector<string> llbp;

    // Length of the studied line, 6 is arbitrary it can be changed
    int Nline = 6;
    Mat Image;
    string name;

    // We use filesystem library to go through all the volunteers to register the images data
    for (const auto & entry : filesystem::directory_iterator(path)){

        glob(string(entry.path()) + "/*." + inputformat, Registered, false);

        // Get all the bytes writen as a form of .txt files (will be changed to .bin later)
        for (size_t i = 0; i < Registered.size(); i++)
        {   

            name = Registered[i];
            Image = imread(name, 0) ;

            if ( !Image.data )
            {
                printf(" !image.data \n ");
                return 1;
            }

            // Get the bytes of the image using LLBP function and write the txt file
            llbp = Preprocess_function(Image, Nline);

            // Warning
            // This may need to be changed according to your own data
            name.replace(28,3,registeredformat);
            write_image_bin(name,llbp);
        }
    
    }

    return 0;
}
