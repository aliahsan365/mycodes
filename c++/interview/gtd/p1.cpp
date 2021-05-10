#include <limits>
#include <iostream>

bool isLimit(double value)
{
	auto minim = std::numeric_limits<double>::min();
	auto maxim = std::numeric_limits<double>::max();

    return (value < minim or value > maxim);
}

#ifndef RunTests
int main()
{
    std::cout << isLimit(0.0);
}
#endif