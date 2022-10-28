using namespace cv;
using namespace std;

// This function return the morphological transformation of the image, but also calculate the adaptive thresholding using OTSU technique for further work
Mat GetTransformations(Mat Image)
{    
    // Get the morphological transformation of the enhanced image
    Mat kernel = Mat::ones(Size(6,6),CV_32F);
    Mat Morpho;
    morphologyEx(Image, Morpho, MORPH_CLOSE, kernel);

    // Get the adpative binary thesholding with OTSU technique, the veins will be in white
    Mat Thresh;
    threshold(Morpho,Thresh,0,255,THRESH_BINARY_INV + THRESH_OTSU);

    return Morpho;
} 
