#include"scale-image.hpp"

ImageScaler::ImageScaler(cv::Mat& image)
    :m_image(image)
{

}

ImageScaler::ImageScaler(const ImageScaler& scaler)
    :m_image(scaler.m_image)
{

}

ImageScaler& ImageScaler::operator=(const ImageScaler& scaler)
{
    m_image = scaler.m_image;
    return (*this);
}

ImageScaler::~ImageScaler()
{

}


cv::Mat ImageScaler::scaleImage(double scale)
{
    cv::Mat scaleMatrix = __scaleMatrix(scale);
    __fill(scaleMatrix, scale);
    __fillBorder(scaleMatrix, scale);
    return scaleMatrix;
}

cv::Mat ImageScaler::__scaleMatrix(double scale)
{
    double scaleRows = m_image.rows * scale;
    double scaleCols = m_image.cols * scale;

    return cv::Mat::zeros(scaleRows, scaleCols, m_image.type()); 
}


void ImageScaler::__fill(cv::Mat& scaleMatrix, double scale)
{
    for(std::size_t row = 0; row < scaleMatrix.rows; ++row)
    {
        for(std::size_t col = 0; col < scaleMatrix.cols; ++col)
        {
            std::size_t x1 = floor(col / scale);
            std::size_t x2 = ceil(col / scale);
            std::size_t y1 = floor(row / scale);
            std::size_t y2 = ceil(row / scale);

            int channels = m_image.channels();


            switch(channels)
            {
                case 1:
                    {

                        scaleMatrix.at<uchar>(col, row) = __getColor(row, col, scale, x1, y1, x2, y2, 
                                {m_image.at<uchar>(x1, y1), m_image.at<uchar>(x1, y2), m_image.at<uchar>(x2, y1), m_image.at<uchar>(x2, y2)}); 
                        break;
                    }
                case 2:
                    {
                        cv::Mat_<cv::Vec2b> _image= static_cast<cv::Mat_<cv::Vec2b>>(m_image);
                        static_cast<cv::Mat_<cv::Vec2b>>(scaleMatrix).at<cv::Vec2b>(col, row)[0] = __getColor(row, col, scale, x1, y1, x2, y2, 
                                {_image.at<cv::Vec2b>(x1, y1)[0], _image.at<cv::Vec2b>(x1, y2)[0], _image.at<cv::Vec2b>(x2, y1)[0], _image.at<cv::Vec2b>(x2, y2)[0]} 
                            );                        
                         static_cast<cv::Mat_<cv::Vec2b>>(scaleMatrix).at<cv::Vec2b>(col, row)[1] = __getColor(row, col, scale, x1, y1, x2, y2, 
                                {_image.at<cv::Vec2b>(x1, y1)[1], _image.at<cv::Vec2b>(x1, y2)[1], _image.at<cv::Vec2b>(x2, y1)[1], _image.at<cv::Vec2b>(x2, y2)[1]} 
                            );                        
                         break;
                   }
                case 3:
                    {

                        cv::Mat_<cv::Vec3b> _image= static_cast<cv::Mat_<cv::Vec3b>>(m_image);
                        static_cast<cv::Mat_<cv::Vec3b>>(scaleMatrix).at<cv::Vec3b>(col, row)[0] = __getColor(row, col, scale, x1, y1, x2, y2, 
                                {_image.at<cv::Vec3b>(x1, y1)[0], _image.at<cv::Vec3b>(x1, y2)[0], _image.at<cv::Vec3b>(x2, y1)[0], _image.at<cv::Vec3b>(x2, y2)[0]} 
                            );                        
                         static_cast<cv::Mat_<cv::Vec3b>>(scaleMatrix).at<cv::Vec3b>(col, row)[1] = __getColor(row, col, scale, x1, y1, x2, y2, 
                                {_image.at<cv::Vec3b>(x1, y1)[1], _image.at<cv::Vec3b>(x1, y2)[1], _image.at<cv::Vec3b>(x2, y1)[1], _image.at<cv::Vec3b>(x2, y2)[1]} 
                            );                        
                         static_cast<cv::Mat_<cv::Vec3b>>(scaleMatrix).at<cv::Vec3b>(col, row)[2] = __getColor(row, col, scale, x1, y1, x2, y2, 
                                {_image.at<cv::Vec3b>(x1, y1)[2], _image.at<cv::Vec3b>(x1, y2)[2], _image.at<cv::Vec3b>(x2, y1)[2], _image.at<cv::Vec3b>(x2, y2)[2]} 
                            );                        
                         break;
                    }
            }

        }
    }
}

void ImageScaler::__fillBorder(cv::Mat& scaleMatrix, double scale)
{
    //fill the down border
    for(std::size_t row = scaleMatrix.rows - scale; row < scaleMatrix.rows; ++row)
    {
        for(std::size_t col = 0; col <= scaleMatrix.cols - scale; ++col)
        {
            __copyCell(scaleMatrix, scaleMatrix.rows - scale, col, scaleMatrix, row, col);
        }
    }
    //fill the left border
    for(std::size_t col = scaleMatrix.cols - scale; col < scaleMatrix.cols; ++col)
    {
        for(std::size_t row = 0; row <= scaleMatrix.rows - scale; ++row)
        {
            __copyCell(scaleMatrix, row, scaleMatrix.cols - scale, scaleMatrix, row, col);
        }
    }
    //fill the last one at the end of image
    for(std::size_t row = scaleMatrix.rows - scale; row < scaleMatrix.rows; ++row)
    {
        for(std::size_t col = scaleMatrix.cols - scale; col < scaleMatrix.cols; ++col)
        {
            __copyCell(scaleMatrix, scaleMatrix.rows - scale, scaleMatrix.cols - scale, scaleMatrix, row, col);
        }
    }
}

void ImageScaler::__copyCell(const cv::Mat& src, std::size_t srcX, std::size_t srcY, cv::Mat& des, std::size_t desX, std::size_t desY)
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


