#ifndef LAGRANGE_HPP
    #define LAGRANGE_HPP

#include<vector>

class Lagrange
{
public:
    Lagrange(std::vector<double> xSet, std::vector<double> ySet);
    Lagrange(Lagrange& lagrange);
    Lagrange& operator=(Lagrange& lagrange);
    ~Lagrange();

    double getValue(double x);

private:

    double __lagrange(std::size_t index, double x);

    std::vector<double> m_xSet;
    std::vector<double> m_ySet;
};

#endif //LAGRANGE_HPP
