using namespace cv;
using namespace std;

// Apply the Clahe Enhancement algorithm to an image
Mat claheEnhance(Mat Image)
{
    Mat GaussBlurImg;
    GaussianBlur(Image, GaussBlurImg, Size(9,9),0);
    Ptr<CLAHE> clahe = createCLAHE();
    clahe->setClipLimit(4);
    clahe->setTilesGridSize(Size(9,9));
    Mat ClaheImg;
    clahe->apply(GaussBlurImg,ClaheImg);

    return ClaheImg;
}

// Apply the clahe Enhancement to a image two times simultaneously for further thresholding
Mat GetClaheEqual(Mat Image)
{

    // First enhancement
    Mat clahe1; 
    clahe1 = claheEnhance(Image);

    // Second enhancement
    Mat clahe2; 
    clahe2 = claheEnhance(Image);

    return clahe2;
} 