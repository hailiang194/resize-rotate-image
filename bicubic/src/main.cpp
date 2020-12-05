#include<iostream>
#include<sstream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<stdexcept>
#include<vector>
#include"scale-image.hpp"
#include"lagrange.hpp"

#define IMAGE_PATH_ARGV 1
#define IMAGE_SCALE_VALUE_ARGV 2
#define IMAGE_COLOR_ARGV 3
#define IS_ENOUGH_ARGV_FOR(ARGV_INDEX) (argc >= (ARGV_INDEX + 1))


int main(int argc, char *argv[])
{
    std::string imagePath = argv[IMAGE_PATH_ARGV];

    std::stringstream scaleStream;
    scaleStream << (IS_ENOUGH_ARGV_FOR(IMAGE_SCALE_VALUE_ARGV) ? argv[IMAGE_SCALE_VALUE_ARGV] : "1.0");
    double scale = 0.0;
    scaleStream >> scale;

    int imageReadFlag = (IS_ENOUGH_ARGV_FOR(IMAGE_COLOR_ARGV) && std::strcmp(argv[IMAGE_COLOR_ARGV], "G") == 0) ? cv::IMREAD_GRAYSCALE : cv::IMREAD_COLOR;

    cv::Mat image = cv::imread(imagePath, imageReadFlag);

    if(image.empty())
    {
        std::cout << "Could not read the image: " << std::endl;
        return 1;
    }

    ImageScaler scaler(image);
    cv::Mat scaleImage = scaler.scaleImage(scale);
    cv::imshow("Input: ", image);
    cv::imshow("Output: ", scaleImage);
    cv::imwrite("output.jpg", scaleImage);    
    cv::waitKey(0);
    /* std::vector<double> xSet; */

    /* xSet.push_back(1); */
    /* xSet.push_back(2); */
    /* xSet.push_back(3); */

    /* std::vector<double> ySet; */
    /* ySet.push_back(11); */
    /* ySet.push_back(31); */
    /* ySet.push_back(73); */

    /* Lagrange lagrange(xSet, ySet); */
    /* for(std::size_t i = 0; i < 10; ++i) */
    /* { */
    /*     std::cout << lagrange.getValue(i) << std::endl; */
    /* } */

    return 0;
}
