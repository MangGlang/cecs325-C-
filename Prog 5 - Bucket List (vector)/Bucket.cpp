// #include "Bucket.h"
// #include <algorithm> // utilizing bubble sort from Prog3 and Prog4
// #include <random>    // cplusplus.com --> utilizing random_device, mt19937, and uniform_int_distribution

// // Implementing and Defining methods of the "Bucket" class.
// // Def. Constructor
// Bucket::Bucket() {}

// // Generate Member Function
// void Bucket::generate(int size, int min, int max)
// {
//     // "Clean" vector & reserve "size" elements
//     v.clear();
//     v.reserve(size);

//     // Random Number Generation
//     std::random_device ranNum;  // obtain seed for random num engine
//     std::mt19937 gen(ranNum()); // Mersenne Twister: Modern randomizer
//     std::uniform_int_distribution<int> distr(min, max);

//     // Generate randomNumbers and append to vector
//     for (int i = 0; i < size; ++i)
//     {
//         v.push_back(distr(gen));
//     }
// }

// void Bucket::sort()
// {
//     int size = v.size();

//     // Bubble sort function from prog3 and prog4
//     for (int i = 0; i < size - 1; ++i)
//     {
//         bool flag = false;
//         for (int j = 0; j < size - i - 1; ++j)
//         {
//             if (v[j] > v[j + 1])
//             {
//                 // Swap v[j] and v[j+1]
//                 std::swap(v[j], v[j + 1]);
//                 flag = true;
//                 ++globalSwapCount; // increment globalswapcount to return at end of main.cpp
//             }
//         }
//         if (!flag)
//         {
//             break;
//         }
//     }
// }

// int Bucket::size() const
// {
//     return v.size();
// }

// int Bucket::atIndex(int index) const
// {
//     // Edge case for if index is out of range.
//     if (index < 0 || index >= size())
//     {
//         return -1;
//     }
//     // Otherwise, return index as normal.
//     return v[index];
// }

// int Bucket::merge(Bucket b)
// {
//     // Merging bucket b
//     for (int num : b.v)
//     {
//         v.push_back(num);
//     }
//     sort();
//     return size();
// }