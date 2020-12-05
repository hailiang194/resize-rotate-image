#include"rotate.hpp"

ImageRotation::ImageRotation(cv::Mat& image)
    :m_image(image)
{

}

ImageRotation::ImageRotation(const ImageRotation& rotation)
    :m_image(rotation.m_image)
{

}

ImageRotation& ImageRotation::operator=(const ImageRotation& rotation)
{
    this->m_image = rotation.m_image;
    return (*this);
}

ImageRotation::~ImageRotation()
{

}

cv::Mat ImageRotation::rotateImage(double radian)
{
    if(COMPARE_DOUBLE(radian, 0))
        return m_image.clone();

    if(radian < 0.0)
    {
        radian = DEGREE_TO_RADIAN(360) + radian;
    }
    cv::Mat leftRotatedImage = m_image;
    std::size_t leftRotateTime = 0;
    for(leftRotateTime = 0; leftRotateTime < floor(radian / DEGREE_TO_RADIAN(90)); ++leftRotateTime)
    {
        leftRotatedImage = __leftRotation(leftRotatedImage);
    }

    radian = radian - leftRotateTime * DEGREE_TO_RADIAN(90);

    if(COMPARE_DOUBLE(radian, 0))
        return leftRotatedImage.clone();



    cv::Mat rotatedImage = __getBlankRotateImage(leftRotatedImage, radian);    
    __fill(leftRotatedImage, rotatedImage, radian);
    return rotatedImage;
}

cv::Mat ImageRotation::__getBlankRotateImage(cv::Mat& preImage, double radian)
{
    double leftBase = preImage.cols / sin(radian);
    double rightBase = preImage.rows / cos(radian);

    std::size_t col = (leftBase + rightBase) * sin(radian) * cos(radian);
    std::size_t row = (preImage.cols * preImage.cols) / leftBase + (preImage.rows * preImage.rows) / rightBase;

    return cv::Mat::zeros(row, col, m_image.type()); 
}

void ImageRotation::__fill(const cv::Mat& preImage, cv::Mat& rotatedImage, double radian)
{
    double rowCenter = preImage.rows / 2.0;
    double colCenter = preImage.cols / 2.0;
    double rotateRowCenter = rotatedImage.rows / 2.0;
    double rotateColCenter = rotatedImage.cols / 2.0;

    for(std::size_t row = 0; row < rotatedImage.rows; ++row)
    {
        for(std::size_t col = 0; col < rotatedImage.cols; ++col)
        {
            double originalCol = (col - rotateColCenter) * cos(radian) - (row - rotateRowCenter) * sin(radian);
            double originalRow = ((row - rotateRowCenter) + sin(radian) * originalCol) / cos(radian);

            originalCol += colCenter;
            originalRow += rowCenter;

            if((originalRow < 0 || originalCol < 0) || (originalRow >= preImage.rows || originalCol >= preImage.cols))
            {
                continue;
            }
            
            __generateColor(preImage, originalRow, originalCol, rotatedImage, row, col);
        }
    }
}

cv::Mat ImageRotation::__leftRotation(cv::Mat& rotatedImage)
{
    cv::Mat leftRotationImage= cv::Mat::zeros(rotatedImage.cols, rotatedImage.rows, rotatedImage.type());

    for(std::size_t row = 0; row < rotatedImage.rows; ++row)
    {
        for(std::size_t col = 0; col < rotatedImage.cols; ++col)
        {
            __copyCell(rotatedImage, row, col, leftRotationImage, rotatedImage.cols - 1 - col, row);
        }
    }

    return leftRotationImage;
}

void ImageRotation::__copyCell(const cv::Mat& src, std::size_t srcX, std::size_t srcY, cv::Mat& des, std::size_t desX, std::size_t desY)
{
    int channels = m_image.channels();

        switch(channels)
        {
            case 1:
                {
                    des.at<uchar>(desX, desY) = src.at<uchar>(srcX, srcY);
                    break;
                }
            case 2:
                {
                    cv::Mat_<cv::Vec2b> _des = static_cast<cv::Mat_<cv::Vec2b>>(des);
                    _des.at<cv::Vec2b>(desX, desY)[0] = src.at<cv::Vec2b>(srcX, srcY)[0];
                    _des.at<cv::Vec2b>(desX, desY)[1] = src.at<cv::Vec2b>(srcX, srcY)[1];
                    break;
                }
            case 3:
                {
                    cv::Mat_<cv::Vec3b> _des = static_cast<cv::Mat_<cv::Vec3b>>(des);
                    _des.at<cv::Vec3b>(desX, desY)[0] = src.at<cv::Vec3b>(srcX, srcY)[0];
                    _des.at<cv::Vec3b>(desX, desY)[1] = src.at<cv::Vec3b>(srcX, srcY)[1];
                    _des.at<cv::Vec3b>(desX, desY)[2] = src.at<cv::Vec3b>(srcX, srcY)[2];

                    break;
                }
        }

}

uchar ImageRotation::__getColor(const cv::Mat_<uchar>& colors)
{
    double firstVectircalColor = (colors(0, 0) + colors(1, 0)) / 2;
    double secondVectircalColor = (colors(0, 1) + colors(1, 1)) / 2;

    return (firstVectircalColor + secondVectircalColor) / 2;
}

void ImageRotation::__generateColor(const cv::Mat& preImage, std::size_t originalRow, std::size_t originalCol, cv::Mat& rotatedImage, std::size_t row, std::size_t col)
{
    switch(preImage.channels())
    {
        case 1:
            {
                cv::Mat_<uchar> colors(2, 2);
                colors << preImage.at<uchar>(originalRow, originalCol), preImage.at<uchar>(originalRow, originalCol + 1),
                        preImage.at<uchar>(originalRow + 1, originalCol), preImage.at<uchar>(originalRow + 1, originalCol + 1);
                rotatedImage.at<uchar>(row, col) = __getColor(colors);
                break;
            }
        case 2:
            {
                cv::Mat_<cv::Vec2b> _preImage = static_cast<cv::Mat_<cv::Vec2b>>(preImage);
                for(std::size_t i = 0; i < 2; ++i)
                {
                
                    cv::Mat_<uchar> colors(2, 2);
                    colors << preImage.at<cv::Vec2b>(originalRow, originalCol)[i], preImage.at<cv::Vec2b>(originalRow, originalCol + 1)[i],
                        preImage.at<cv::Vec2b>(originalRow + 1, originalCol)[i], preImage.at<cv::Vec2b>(originalRow + 1, originalCol + 1)[i];
   
                    static_cast<cv::Mat_<cv::Vec2b>>(rotatedImage).at<cv::Vec2b>(row, col)[i] = __getColor(colors);
                }
                
                break;
            }
        case 3:
            {
                cv::Mat_<cv::Vec3b> _preImage = static_cast<cv::Mat_<cv::Vec3b>>(preImage);
                for(std::size_t i = 0; i < 3; ++i)
                {
                
                    cv::Mat_<uchar> colors(2, 2);
                    colors << preImage.at<cv::Vec3b>(originalRow, originalCol)[i], preImage.at<cv::Vec3b>(originalRow, originalCol + 1)[i],
                        preImage.at<cv::Vec3b>(originalRow + 1, originalCol)[i], preImage.at<cv::Vec3b>(originalRow + 1, originalCol + 1)[i];
   
                    static_cast<cv::Mat_<cv::Vec3b>>(rotatedImage).at<cv::Vec3b>(row, col)[i] = __getColor(colors);
                }

                break;
            }
    }
}
