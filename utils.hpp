#ifndef UTILS_HPP
#define UTILS_HPP

#include <limits>

/*
 * find the position of the lowest 1 of x
 */
template <typename T> int lowbit(T x)
{
    T lowbit = x & -x;
    int lb = -1, rb = std::numeric_limits<T>::digits;
    while (lb + 1 < rb)
    {
        int mid = (lb + rb) >> 1;
        if (lowbit < (T(1) << mid))
        {
            rb = mid;
        }
        else
        {
            lb = mid;
        }
    }
    return lb;
}

#endif // !UTILS_HPP
