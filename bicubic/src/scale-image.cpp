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
    for(std::size_t row = 0; row < scaleMatrix.rows - scale; ++row)
    {
        for(std::size_t col = 0; col < scaleMatrix.cols - scale; ++col)
        {
            std::size_t firstRow = 0;
            std::size_t firstCol = 0;

            if((row < scaleMatrix.rows - 3 * scale) && (col < scaleMatrix.cols - 3 * scale))
            {
                firstRow = floor(row / scale);
                firstCol = floor(col / scale);
                if((firstRow == (std::size_t)ceil(row / scale)) && 
                    (firstCol == (std::size_t)ceil(col / scale)))
                {
                    __copyCell(m_image, firstRow, firstCol, scaleMatrix, row, col);
                    continue;
                }

            }
            else
            {
                firstRow = ceil(row / scale) - 3;
                firstCol = ceil(col / scale) - 3;
                
                //because their type is std::size_t, they are allway > 0
                //and if they are < 0, they will be overflow
                firstRow = (firstRow > m_image.rows) ? 0 : firstRow;
                firstCol = (firstCol > m_image.cols) ? 0 : firstCol;

            }

            __generateColor(scaleMatrix, row, col, firstRow, firstCol, scale);
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


uchar ImageScaler::__getColor(cv::Mat_<uchar> colors, std::size_t row, std::size_t col, std::size_t firstRow, std::size_t firstCol, double scale)
{
    cv::Mat_<double> colColors(1, 4);

    for(std::size_t _row = 0; _row < 4; ++_row)
    {
        std::vector<double> xSet;

        xSet.push_back(0);
        xSet.push_back(1);
        xSet.push_back(2);
        xSet.push_back(3);

        std::vector<double> ySet;

        ySet.push_back(colors.at<uchar>(_row, 0));
        ySet.push_back(colors.at<uchar>(_row, 1));
        ySet.push_back(colors.at<uchar>(_row, 2));
        ySet.push_back(colors.at<uchar>(_row, 3));

        double position = (row - firstRow * scale) / scale;
        Lagrange lagrange(xSet, ySet);
        
        double value = lagrange.getValue(position);
        colColors.at<double>(0, _row) = value;
    }
    
    std::vector<double> xSet;

    xSet.push_back(0);
    xSet.push_back(1);
    xSet.push_back(2);
    xSet.push_back(3);

    std::vector<double> ySet;

    ySet.push_back(colColors.at<double>(0, 0));
    ySet.push_back(colColors.at<double>(0, 1));
    ySet.push_back(colColors.at<double>(0, 2));
    ySet.push_back(colColors.at<double>(0, 3));

    double position = (col - firstCol * scale) / scale;
    Lagrange lagrange(xSet, ySet);
    double value = lagrange.getValue(position);

    if(value < 0.0)
    {
        value = 0.0;
    }else if(value > 255.0)
    {
        value = 255.0;
    }

    return value;
}


void ImageScaler::__generateColor(cv::Mat& scaleMatrix, std::size_t row, std::size_t col, std::size_t firstRow, std::size_t firstCol, double scale)
{
        switch(m_image.channels())
            {
                case 1:
                    {
                        cv::Mat_<uchar> colors(m_image, cv::Rect(firstCol, firstRow, 4, 4));
                        uchar value = __getColor(colors, row, col, firstRow, firstCol, scale);
                        scaleMatrix.at<uchar>(row, col) = value;
                        break;
                    }
                case 2:
                    {
                        cv::Mat_<cv::Vec2b> _image = static_cast<cv::Mat_<cv::Vec2b>>(m_image);
                        for(std::size_t i = 0; i < 2; ++i)
                        {
                            cv::Mat_<uchar> colors(4, 4);
                            colors << _image.at<cv::Vec2b>(firstRow, firstCol)[i], 
                                   _image.at<cv::Vec2b>(firstRow, firstCol + 1)[i], 
                                   _image.at<cv::Vec2b>(firstRow, firstCol + 2)[i], 
                                   _image.at<cv::Vec2b>(firstRow, firstCol + 3)[i],  
                                   _image.at<cv::Vec2b>(firstRow + 1, firstCol)[i], 
                                   _image.at<cv::Vec2b>(firstRow + 1, firstCol + 1)[i], 
                                   _image.at<cv::Vec2b>(firstRow + 1, firstCol + 2)[i], 
                                   _image.at<cv::Vec2b>(firstRow + 1, firstCol + 3)[i],  
                                   _image.at<cv::Vec2b>(firstRow + 2, firstCol)[i], 
                                   _image.at<cv::Vec2b>(firstRow + 2, firstCol + 1)[i], 
                                   _image.at<cv::Vec2b>(firstRow + 2, firstCol + 2)[i], 
                                   _image.at<cv::Vec2b>(firstRow + 2, firstCol + 3)[i],  
                                    _image.at<cv::Vec2b>(firstRow + 3, firstCol)[i], 
                                   _image.at<cv::Vec2b>(firstRow + 3, firstCol + 1)[i], 
                                   _image.at<cv::Vec2b>(firstRow + 3, firstCol + 2)[i], 
                                   _image.at<cv::Vec2b>(firstRow + 3, firstCol + 3)[i];
                            uchar value = __getColor(colors, row, col, firstRow, firstCol, scale);
                            scaleMatrix.at<cv::Vec2b>(row, col)[i] = value;
                        }
                        break;
                    }
                case 3:
                    {

                        cv::Mat_<cv::Vec3b> _image = static_cast<cv::Mat_<cv::Vec3b>>(m_image);
                        for(std::size_t i = 0; i < 3; ++i)
                        {
                            cv::Mat_<uchar> colors(4, 4);
                            colors << _image.at<cv::Vec3b>(firstRow, firstCol)[i], 
                                   _image.at<cv::Vec3b>(firstRow, firstCol + 1)[i], 
                                   _image.at<cv::Vec3b>(firstRow, firstCol + 2)[i], 
                                   _image.at<cv::Vec3b>(firstRow, firstCol + 3)[i],  
                                   _image.at<cv::Vec3b>(firstRow + 1, firstCol)[i], 
                                   _image.at<cv::Vec3b>(firstRow + 1, firstCol + 1)[i], 
                                   _image.at<cv::Vec3b>(firstRow + 1, firstCol + 2)[i], 
                                   _image.at<cv::Vec3b>(firstRow + 1, firstCol + 3)[i],  
                                   _image.at<cv::Vec3b>(firstRow + 2, firstCol)[i], 
                                   _image.at<cv::Vec3b>(firstRow + 2, firstCol + 1)[i], 
                                   _image.at<cv::Vec3b>(firstRow + 2, firstCol + 2)[i], 
                                   _image.at<cv::Vec3b>(firstRow + 2, firstCol + 3)[i],  
                                    _image.at<cv::Vec3b>(firstRow + 3, firstCol)[i], 
                                   _image.at<cv::Vec3b>(firstRow + 3, firstCol + 1)[i], 
                                   _image.at<cv::Vec3b>(firstRow + 3, firstCol + 2)[i], 
                                   _image.at<cv::Vec3b>(firstRow + 3, firstCol + 3)[i];
                            uchar value = __getColor(colors, row, col, firstRow, firstCol, scale);
                            scaleMatrix.at<cv::Vec3b>(row, col)[i] = value;
                        }
                        break;
                    }
            }
}
