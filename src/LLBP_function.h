#include <iostream>
#include <iomanip>
#include <fstream>

using namespace cv;
using namespace std;

// Binary Threshold function for LLBP bytes
string Sx(int x)
{
    if (x >= 0){
        return "1";
        } 
    else{
        return "0";
        }   
}

// Function to get the bytes of pixels using LLBP technique for a given image
vector<string> LLBP_bin(Mat Image, int Nline)
{

    // Get the image size and initialize the variables
    Size s = Image.size();
    int c = Nline/2; // middle of the line, central pixel
    vector<string> llbpm; // vector of bytes

    // Go through all the pixels, remove a part of the border of the image corresponding to the chosen size of the line (Nline)
    for (size_t i = c; i < s.width - c; i++)
    {
        for (size_t j = c; j < s.height - c; j++)
        {

            // Get the intensity of the central pixel and initialize the bytes for vertical and horrizontal values
            int hc = int(Image.at<uchar>(i, j));
            string binaryh;
            string binaryv;

            // Central part of LLBP algorithm, here the attribution to a generalized intensity on lines is not used (2^(n-c-1) part of the LLBP algorithms)
            for (size_t n = 1; n <= Nline; n++)
            {
                // Left/Top side of the line
                if (n < c)
                {
                    binaryh.append(Sx(int(Image.at<uchar>(i, (n-c))) - hc));
                    binaryv.append(Sx(int(Image.at<uchar>((n-c), j))- hc));

                }

                // Right/Bottom side of the line
                else if (n > c)
                {
                    binaryh.append(Sx(int(Image.at<uchar>(i, (n-c))) - hc));
                    binaryv.append(Sx(int(Image.at<uchar>((n-c), j))- hc));
                }
            }

            // the magnitude is equal to horizontal and vertical values, but we can also compare each of them
            string llbpmindex = {binaryh+binaryv};
            llbpm.push_back(llbpmindex);
               
        }
    }
    
    return llbpm;
}

// Get the llbp bytes from the txt files
vector<string> getllbpfromfile(string datafile, int Nline)
{
    // initialize the file in read position
    std::fstream file;
    file.open(datafile, ios::in);

    // variables for attribution
    vector<string> bincode;
    string byte;
    string ch;
    
    // we get the data in the txt file
    getline(file, ch);

    // transform the data in readable and comparable format
    for (size_t i = 0; i < ch.size(); i++)
    {
        byte.push_back(ch[i]);
        
        if (byte.size() == 2 * (Nline-1))
        {
            bincode.push_back(byte);
            byte.clear();
        }
    }
    
    // don't forget to close the file
    file.close();

    return bincode;
}

// Comparision of bytes codes of two images using Hamming Distance (HD) between bytes
float LLBP_matching_HD(vector<string> bincode1, vector<string> bincode2)
{
    // variables for attribution
    float HDim; // Difference of all bytes in the image
    float HD_diff; // final difference
    float compt; // Difference between two bytes for HD
    
    // Comparision between every corresponding bytes of two images
    for (size_t i = 0; i < bincode1.size() ; i++)
    {
        compt = 0.0;

        for (size_t k = 0; k < bincode1[i].size(); k++)
        {
            if (bincode1[i][k] != bincode2[i][k])
            {   
                compt ++;                
            }
        }
        HDim += compt / bincode1[i].size();
    }
    HD_diff = HDim/bincode1.size();
    
    return HD_diff;
}

// Function to write the txt file for matching later
void write_image_bin(string image_path, vector<string> LLBP_bin_image)
{
    // initialize the file in write position
    std::ofstream file;
    file.open(image_path);

    // Write all information in the txt files
    for (int i = 0; i < LLBP_bin_image.size(); i++) {
        for (size_t k = 0; k < LLBP_bin_image[i].size(); k++)
        {
            file << LLBP_bin_image[i][k] << "";
        }
    }

    // signal to the user that a file has been writen, and close the file
    std::cout << image_path + " is writen" << "\n";
    file.close();
}
