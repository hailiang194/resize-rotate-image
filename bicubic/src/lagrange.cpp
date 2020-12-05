#include"lagrange.hpp"

Lagrange::Lagrange(std::vector<double> xSet, std::vector<double> ySet)
    :m_xSet(xSet), m_ySet(ySet)
{

}

Lagrange::Lagrange(Lagrange& lagrange)
    :m_xSet(lagrange.m_xSet), m_ySet(lagrange.m_ySet)
{

}

Lagrange& Lagrange::operator=(Lagrange& lagrange)
{
    m_xSet = lagrange.m_xSet;
    m_ySet = lagrange.m_ySet;

    return (*this);
}

Lagrange::~Lagrange()
{

}

double Lagrange::getValue(double x)
{
    double value = 0.0;

    for(std::size_t j = 0; j < m_ySet.size(); ++j)
    {
        value += m_ySet[j] * __lagrange(j, x);
    }

    return value;
}

double Lagrange::__lagrange(std::size_t index, double x)
{
    double value = 1.0;

    for(std::size_t j = 0; j < m_ySet.size(); ++j)
    {
        if(j == index)
        {
            continue;
        }

        value *= ((x - m_xSet[j]) / (m_xSet[index] - m_xSet[j]));
    }

    return value;
}
