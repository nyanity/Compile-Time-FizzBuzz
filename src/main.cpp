#include<iostream>
#include"fizzbuzz_ct.hpp"

int main()
{
    constexpr auto v = fizzbuzz<50>;
    constexpr auto _v = fizzbuzz_interval<51, 99>;
    constexpr auto __v = fizzbuzz_at<100>;
    std::cout << v << _v << __v;
    return 0;
}
