#ifndef UTILS_HPP
#define UTILS_HPP

/*
 * find n that (1 << n) == lowbit(x)
 */
template <typename T> int log2_lowbit(T x)
{
    T lowbit = x & -x;
    int lb = 0, rb = sizeof(T) * 8;
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
