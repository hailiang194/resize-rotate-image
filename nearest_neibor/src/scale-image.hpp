#ifndef SCALE_IMAGE_HPP
    #define SCALE_IMAGE_HPP

#include<opencv2/core/mat.hpp>
#include<array>
#include<limits>


class ImageScaler
{
public:
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
     * get the position of the neareast neibor of (x, y)
     * return an array corressponding to (x, y) of the neighbor
     */
    std::array<std::size_t, 2> __nearestNeigbor(cv::Mat& matrix, std::size_t x, std::size_t y, cv::Mat_<bool>& colored, double scale);


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
