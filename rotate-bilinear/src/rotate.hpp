#ifndef ROTATE_HPP
    #define ROTATE_HPP

#include<opencv2/core/mat.hpp>
#include<opencv2/core.hpp>
#include<cmath>
#include<array>
#include<iostream>

#define SQR(x) ((x) * (x))

#define PI 3.14159 
#define DEGREE_TO_RADIAN(degree) (degree * PI / 180)
#define EPSILON 0.0001 
#define COMPARE_DOUBLE(A, B) (((A - B < EPSILON) && (B - A < EPSILON)))

class ImageRotation
{
public:
    ImageRotation(cv::Mat& image);
    ImageRotation(const ImageRotation& rotation);
    ImageRotation& operator=(const ImageRotation& rotation);
    ~ImageRotation();

    cv::Mat rotateImage(double radian);

    //get image
    const cv::Mat& image() const;
    const cv::Mat& image();

private:

    /**
     * get blank rotate image
     * preImage: image before rotating
     * radian: rotate degree in radian
     */
    cv::Mat __getBlankRotateImage(cv::Mat& preImage, double radian);

    /**
     * draw ratated image
     * preImage: image before rotating
     * rotatedImage: rotated image
     * radian: rotate degree in radian
     */
    void __fill(const cv::Mat& preImage, cv::Mat& rotatedImage, double radian);

    /**
     * rotate image with 90 degree
     * rotatedImage: rotated image
     */
    cv::Mat __leftRotation(cv::Mat& rotatedImage);
    
    /**
     * copy the value of (srcX, srcY) of src to the position (desX, desY) of des
     * src: source matrix
     * srcX: x postion of src that is copied
     * srcY: y position of src that is copied
     * des: destination matrix
     * desX: x position of des to copy
     * desY: y position of des to copy
     */ 
    void __copyCell(const cv::Mat& src, std::size_t srcX, std::size_t srcY, cv::Mat& des, std::size_t desX, std::size_t desY);

    /**
     * get the color
     * colors: matrix of computing color
     */
    uchar __getColor(const cv::Mat_<uchar>& colors);

    /**
     * generate color for position (row, col) of rotatedImage
     * preImage: image before rotating
     * originalRow: row mapping from preImage for row
     * originalCol: col mapping from preImage for col
     * rotatedImage: rotated image
     * row: row position of rotatedImage
     * col: col position of rotatedImage
     */
    void __generateColor(const cv::Mat& preImage, std::size_t originalRow, std::size_t originalCol, cv::Mat& rotatedImage, std::size_t row, std::size_t col);

    cv::Mat& m_image;
};

inline const cv::Mat& ImageRotation::image() const
{
    return m_image;
}

inline const cv::Mat& ImageRotation::image()
{
    return static_cast<const ImageRotation&>(*this).image();
}

#endif //ROTATE_HPP
