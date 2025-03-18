#ifndef FPUTILS_H_85C012829938449F
#define FPUTILS_H_85C012829938449F

#include <limits>
#include <random>


namespace FPUtils
{
    inline double NaN() { return std::numeric_limits<double>::quiet_NaN(); }

    inline double infinity() { return std::numeric_limits<double>::infinity(); }

    static std::mt19937 gen(std::random_device{}());

    inline double random_uniform(double min = -1.0, double max = 1.0)
    {
        std::uniform_real_distribution<double> dis(min, max);
        return dis(FPUtils::gen);
    }

    inline double random_normal(double mu = 0.0, double stddev = 1.0)
    {
        std::normal_distribution<double> dis(mu, stddev);
        return dis(FPUtils::gen);
    }
}


#endif // FPUTILS_H_85C012829938449F
