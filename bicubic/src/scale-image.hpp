#ifndef SCALE_IMAGE_HPP
    #define SCALE_IMAGE_HPP

#include<opencv2/core/mat.hpp>
#include<opencv2/core.hpp>
#include<iostream>
#include<array>
#include<vector>
#include<limits>
#include<stdexcept>
#include"lagrange.hpp"

#define CUBE(x) (x * x * x)
#define SQR(x) (x * x)

class ImageScaler
{
public:
    typedef std::array<std::size_t, 2> position_t;    
    ImageScaler(cv::Mat& image);
    ImageScaler(const ImageScaler& scaler);
    ImageScaler& operator=(const ImageScaler& scaler);
    ~ImageScaler();

    //get image 
    const cv::Mat& image() const;
    const cv::Mat& image();

    /**
     * Scale image
     * scale: scale
     * return Mat of matrix that is scaled
     */
    cv::Mat scaleImage(double scale);

private:
    /**
     * Get matrix scale
     * scale: scale of new matrix by scaled matrix
     * return scaled zeros matrix
     */
    cv::Mat __scaleMatrix(double scale);

    /**
     * fill all the vertical lines which have at least 1 postion is colored after initalize scale matrix
     * scaleMatrix: scale matrix
     * scale: scale
     * colored: matrix for mapping is a cell is colored
     */
    void __fill(cv::Mat& scaleMatrix, double scale);

    /**
     * Fill the down and left border of the image
     * scaleMatrix: scaled matrix
     * scale: scale
     */
    void __fillBorder(cv::Mat& scaleMatrix, double scale);

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
     * get color at the postion (row, col)
     * colors: colors mapping
     * row: row position
     * col: col position
     * scale: scale
     * return the color of position(x, y)
     */
    uchar __getColor(cv::Mat_<uchar> colors, std::size_t row, std::size_t col, std::size_t firstRow, std::size_t firstCol, double scale);

    /**
     * generate color for postion (row, col) of scaleMatrix
     * row: row position
     * col: col position
     * firstRow: first row position for generate image from original image
     * firstCol: first coloumn position for generate image from original image
     * scale: scale
     */
    void __generateColor(cv::Mat& scaleMatrix, std::size_t row, std::size_t col, std::size_t firstRow, std::size_t firstCol, double scale);

    cv::Mat& m_image;
};

inline const cv::Mat& ImageScaler::image() const
{
    return m_image;
}

inline const cv::Mat& ImageScaler::image()
{
    return static_cast<const ImageScaler&>(*this).image();
}

#endif
