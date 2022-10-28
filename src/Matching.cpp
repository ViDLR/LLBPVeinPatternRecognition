// Include all internal libraries
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <glob.h> 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <chrono>

// Include all external libraries
#include"Preprocess_function.h"


using namespace cv;
using namespace std;
using namespace filesystem;

// Warning
// Some element should be changed according to your own data, all strings matching names need to be changed, mine was: ex: 22/0103H3C.txt (volunteer 22, image 0103H3C)

// Main executable for Matching images
int main(int argc, char** argv)
{   
    // Get the path of the input images and the path of the registered data
    string path_input = argv[1];
    string path_registered = argv[2];
    string inputformat = {"jpg"}; // Format can be added or changed here
    string registeredformat = {"txt"}; // Format can be added or changed here

    // Two vector to register input images for matching and registered bytes files
    vector<string> Registered;
    vector<string> input;

    //  Two vector of bytes for matching
    vector<string> llbp;
    vector<string> llbp2;

    // Length of the studied line, 6 is arbitrary it can be changed
    int Nline = 6;
    Mat Image;
    string name;

    // Matching variables and correct guess number
    int correct = 0;
    float bestmatching;
    string bestmatch_name;


    // we get all the input images using glob library
    glob(path_input + "*." + inputformat, input, false);

    // Test all the input images to find matches
    for (size_t k = 0; k < input.size(); k++)
    {
        // input variables for matching 
        name = input[k];
        Image = imread(name, 0);

        // we get the LLBP bytes of the input image
        llbp = Preprocess_function(Image, Nline);
        if ( !Image.data )
        {
            printf(" !image.data \n ");
            return 1;
        }

        //  initialization of matching variables, 1.0 is the worst matching and 0.0 is the best similarity (same image)
        bestmatching = 1.0;
        bestmatch_name = "";

        // We use filesystem library to go through all the registered volunteers
        for (const auto & entry : filesystem::directory_iterator(path_registered)){

            glob(string(entry.path()) + "/*." + registeredformat, Registered, false);

            //  compare the registered .txt files of images with the input
            for (size_t i = 0; i < Registered.size(); i++)
            {   
                    llbp2 = getllbpfromfile(Registered[i], Nline);

                    // get the Hamming distance between the two images bytes
                    float HD_diff = LLBP_matching_HD(llbp, llbp2);
                    
                    if (HD_diff < bestmatching)
                    {
                        bestmatching = HD_diff;
                        bestmatch_name = Registered[i].substr(17);
                    }
                    
            }
            
        
        }
        // Warning
        // This may need to be changed according to your own data
        // on my data set, the images where variating from 1 or 2 number for each volunteer, so I used it as a verification process for the match

        if (stoi(name.substr(13, 3)) <= stoi(bestmatch_name.substr(3, 3)) <= stoi(name.substr(13, 3)) +2)
        {
            correct ++;
        }

        // Warning
        // This may need to be changed according to your own data
        std::cout << "input is : " << name.substr(12, 7) << " bestmatch is " << bestmatch_name << " with a HD of : " << bestmatching << "\n";
    }
    
    // Warning
    // This need to be changed according to your own data
    std::cout << "out of " << input.size() << " images, we have " << correct << " correct matches, " << correct / input.size() * 100 << "%% correct \n";
    return 0;
}
