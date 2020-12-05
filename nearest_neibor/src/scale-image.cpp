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


cv::Mat ImageScaler::__scaleMatrix(double scale)
{
    double scaleRows = m_image.rows * scale;
    double scaleCols = m_image.cols * scale;

    return cv::Mat::zeros(scaleRows, scaleCols, m_image.type()); 
}

cv::Mat_<bool> ImageScaler::__setPositionForOldColor(cv::Mat& scaleMatrix, double scale)
{
    cv::Mat_<bool> colored(scaleMatrix.rows, scaleMatrix.cols, false);
    int channels = m_image.channels();

    for(std::size_t row = 0; row < m_image.rows; ++row)
    {

        for(std::size_t col = 0; col < m_image.cols; ++col)
        {
            switch(channels)
            {
                case 1:
                    {
                        scaleMatrix.at<uchar>(row * scale, col * scale) = m_image.at<uchar>(row, col);
                        break;
                    }
                case 2:
                    {
                        cv::Mat_<cv::Vec2b> _scaleMatrix = static_cast<cv::Mat_<cv::Vec2b>>(scaleMatrix);
                        _scaleMatrix(row * scale, col * scale)[0] = m_image.at<cv::Vec2b>(row, col)[0];
                        _scaleMatrix(row * scale, col * scale)[1] = m_image.at<cv::Vec2b>(row, col)[1];
                        break;
                    }
                case 3:
                    {
                        cv::Mat_<cv::Vec3b> _scaleMatrix = static_cast<cv::Mat_<cv::Vec3b>>(scaleMatrix);
                        _scaleMatrix(row * scale, col * scale)[0] = m_image.at<cv::Vec3b>(row, col)[0];
                        _scaleMatrix(row * scale, col * scale)[1] = m_image.at<cv::Vec3b>(row, col)[1];
                        _scaleMatrix(row * scale, col * scale)[2] = m_image.at<cv::Vec3b>(row, col)[2];
                        break;
                    }
            }
            colored.at<bool>(row * scale, col * scale) = true;
        }
    }

    return colored;
}

std::array<std::size_t, 2> ImageScaler::__nearestNeigbor(cv::Mat& matrix, std::size_t x, std::size_t y, cv::Mat_<bool>& colored, double scale)
{
    if(colored.at<bool>(x, y))
        return {x, y};

    const std::size_t MIN_X = (x - scale) >= 0 ? x - scale : 0;
    const std::size_t MAX_X = (x + scale) <= matrix.cols - 1  ? x + scale : matrix.cols - 1;
    const std::size_t MIN_Y = (y - scale) >= 0 ? y - scale : 0;
    const std::size_t MAX_Y = (y + scale) <= matrix.rows - 1 ? y + scale: matrix.rows - 1;

    std::size_t nearX = 0;
    std::size_t nearY = 0;
    unsigned long long int minDistance = std::numeric_limits<unsigned long long int>::max(); 

    for(std::size_t surroundY = MIN_Y; surroundY <= MAX_Y; ++surroundY)
    {
        for(std::size_t surroundX = MIN_X; surroundX < MAX_X; ++surroundX)
        {
            if(!colored.at<bool>(surroundX, surroundY))
                continue;
        

            std::size_t distanceX = surroundX - x > 0 ? surroundX - x : x - surroundX;
            std::size_t distanceY = surroundY - y > 0 ? surroundY - y : y - surroundY;
            unsigned long long int distance = distanceX * distanceX + distanceY * distanceY;

            if(distance < minDistance)
            {
                nearX = surroundX;
                nearY = surroundY;

                minDistance = distance;
            }
        
        }
    }

    return {nearX, nearY};
}

cv::Mat ImageScaler::scaleImage(double scale)
{
    cv::Mat scaleMat = __scaleMatrix(scale);
    cv::Mat_<bool> colored = __setPositionForOldColor(scaleMat, scale);
    //foe each non-color emlement find it neareast neighbor
    for(std::size_t y = 0; y < scaleMat.rows; ++y)
    {
        for(std::size_t x = 0; x < scaleMat.cols; ++x)
        {
            std::array<std::size_t, 2> neareastPoint = __nearestNeigbor(scaleMat, x, y, colored, scale);

            int channels = scaleMat.channels();
            
            switch(channels)
            {
                case 1:
                    {
                        scaleMat.at<uchar>(x, y) = scaleMat.at<uchar>(neareastPoint[0], neareastPoint[1]);
                        break;
                    }
                case 2:
                    {
                        cv::Mat_<cv::Vec2b> _scaleMat = static_cast<cv::Mat_<cv::Vec2b>>(scaleMat);
                        _scaleMat.at<cv::Vec2b>(x, y)[0] = _scaleMat.at<cv::Vec2b>(neareastPoint[0], neareastPoint[1])[0];
                        _scaleMat.at<cv::Vec2b>(x, y)[1] = _scaleMat.at<cv::Vec2b>(neareastPoint[0], neareastPoint[1])[1];
                        break;
                    }
                case 3:
                    {
                        cv::Mat_<cv::Vec3b> _scaleMat = static_cast<cv::Mat_<cv::Vec3b>>(scaleMat);
                        _scaleMat.at<cv::Vec3b>(x, y)[0] = _scaleMat.at<cv::Vec3b>(neareastPoint[0], neareastPoint[1])[0];
                        _scaleMat.at<cv::Vec3b>(x, y)[1] = _scaleMat.at<cv::Vec3b>(neareastPoint[0], neareastPoint[1])[1];
                        _scaleMat.at<cv::Vec3b>(x, y)[2] = _scaleMat.at<cv::Vec3b>(neareastPoint[0], neareastPoint[1])[2];
                        break;
                    }
            }
        }
    }
    
    return scaleMat;
}
