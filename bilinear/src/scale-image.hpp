#ifndef SCALE_IMAGE_HPP
    #define SCALE_IMAGE_HPP

#include<opencv2/core/mat.hpp>
#include<iostream>
#include<cmath>
#include<array>
#include<limits>

#define CALCULATE(x, x1, value1, x2, value2) (((x - x1) / (x2 - x1)) * value1 + ((x2 - x) / (x2 - x1)) * value2)
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
     * set corressponding position of old matrix with new matrix
     * scaleMatrix: scale matrix
     * return the matrix that is used to check if the corressponding position is colored.
     */
    cv::Mat_<bool> __setPositionForOldColor(cv::Mat& scaleMatrix, double scale);

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
     * Get color for posion (row, col) of scaleMatrix
     * row: scaleMatrix row position
     * col: scaleMatrix column position
     * row1: first m_image row mapping position
     * col1: first m_image col mapping position
     * row2: first m_image row mapping position
     * col2: first m_image col mapping position
     * color: mapping color
     * return color of posion (row, col) of scaleMatrix
     */
    uchar __getColor(std::size_t row, std::size_t col, double scale, std::size_t row1, std::size_t col1, std::size_t row2, std::size_t col2, std::array<uchar, 4> color);

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

inline uchar ImageScaler::__getColor(std::size_t row, std::size_t col, double scale, std::size_t row1, std::size_t col1, std::size_t row2, std::size_t col2, std::array<uchar, 4> color)
{
    double firstVerticalMeasure = row1 != row2 ? (double)CALCULATE(col, row1 * scale, color[0], row2 * scale, color[1]) : (double)color[0];

    double secondVerticalMeasure = row1 != row2 ? (double)CALCULATE(col, row1 * scale, color[2], row2 * scale, color[3]) : (double)color[2];
    return ((col1 != col2) ? CALCULATE(row, col1 * scale, firstVerticalMeasure, col2 * scale, secondVerticalMeasure) : firstVerticalMeasure);
}

#endif
