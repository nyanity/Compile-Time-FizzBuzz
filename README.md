# FizzBuzz in Compile-Time.
Do all want create array of FizzBuzz elements in compile-time? Who not?

## Limitations
The amount of FizzBuzz elements in array depends on your amount of RAM during compile.\
Also, big amount of elements cause very long compilation.

## Supported Compilers
**MSVC/GCC/CLANG**

## Requirements
**>= C++17**

## Usage
```cpp
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
```

## Documentation
Generating first 50 elements FizzBuzz array.
```cpp
constexpr std::size_t N = 50;
constexpr auto fizzbizz_v = fizzbuzz<N>; 
```
Generating from 51 element to 99 element FizzBuzz array.
```cpp
constexpr std::size_t From = 51;
constexpr std::size_t To = 99;
constexpr auto fizzbuzz_from_to = fizzbuzz_interval<From, To>;
```
Generating only 100 element FizzBuzz array.
```cpp
constexpr std::size_t Index = 100;
constexpr auto fizzbuzz_index = fizzbuzz_at<Index>;
```
To get FizzBuzz array you can use
```cpp
constexpr auto _v = fizzbuzz<...>.value;
                    fizzbuzz_interval<...>.value;
                    fizzbuzz_at<...>.value;
```

## Why?
1. For fun and experiments.
2. For experience with templates and understanding how constexpr works.
3. For work with C++17 and C++20.
4. #LessRuntimeInCode :)
