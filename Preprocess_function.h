#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <glob.h> 

#include"ROI_function.h"
#include"Transformation_function.h"
#include"LLBP_function.h"
#include"Clahe_function.h"

using namespace cv;
using namespace std;

// Function that execute all the processing algorithm and return the LLBP vector of bytes of an image
vector<string> Preprocess_function(Mat Image, int Nline)
{ 
    // Resize the image for calculation and get the ROI 
    Image = getROI(Image);

    // Enhance the image for better thresholding
    Image = GetClaheEqual(Image);

    // Get all the transformations, morphological and binary thresholding
    Image = GetTransformations(Image);

    // Get the LLBP bytes for a given image and line length
    vector<string> llbp = LLBP_bin(Image, Nline);
    
    return llbp;
}