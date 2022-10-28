using namespace cv;

// Return the ROI inside the resized image
Mat getROI(Mat Image)
{
    // resize the image for calculations, the input was 1920x1080
    Size s = Image.size(); 
    Mat ImREZ; 
    resize(Image, ImREZ, Size(s.width/4, s.height/4), INTER_LINEAR); 

    // initialize the variables for ROI isolation and get the ROI
    s = ImREZ.size(); 
    int newwidth1 = 0.1*s.width;
    int newwidth2 = s.width - 0.1*s.width;
    int newheight1 = 0.15*s.height;
    int newheight2 = s.height - 0.1*s.height;
    Mat imROI = ImREZ(Range(newheight1,newheight2),Range(newwidth1,newwidth2));
    
    return imROI;
} 
