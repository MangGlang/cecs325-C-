#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <random> // cplusplus.com --> utilizing random_device, mt19937, and uniform_int_distribution

using namespace std;

int globalSwapCount = 0;
 
// Implementing "Bucket" class
class Bucket {
    private: 
        vector<int> v;
    public:
        Bucket();
        void generate(int size, int min, int max);
        void sort(); // Use the bubble sort from Prog3 and Prog4

        // const member functions: value does not change
        int size() const;
        int atIndex(int) const;

        int merge(Bucket b); // merge b into this
};

// Implementing and Defining methods of the "Bucket" class.

// Def. Constructor
Bucket::Bucket() {}

// Generate Member Function
void Bucket::generate(int size, int min, int max)
{
    // "Clean" vector & reserve "size" elements
    v.clear();
    v.reserve(size);

    // Random Number Generation
    std::random_device ranNum;  // obtain seed for random num engine
    std::mt19937 gen(ranNum()); // Mersenne Twister: Modern randomizer
    std::uniform_int_distribution<int> distr(min, max);

    // Generate randomNumbers and append to vector
    for (int i = 0; i < size; ++i)
    {
        v.push_back(distr(gen));
    }
}

void Bucket::sort()
{
    int size = v.size();

    // Bubble sort function from prog3 and prog4
    for (int i = 0; i < size - 1; ++i)
    {
        bool flag = false;
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (v[j] > v[j + 1])
            {
                // Swap v[j] and v[j+1]
                std::swap(v[j], v[j + 1]);
                flag = true;
                ++globalSwapCount; // increment globalswapcount to return at end of main.cpp
            }
        }
        if (!flag)
        {
            break;
        }
    }
}

int Bucket::size() const
{
    return v.size();
}

int Bucket::atIndex(int index) const
{
    // Edge case for if index is out of range.
    if (index < 0 || index >= size())
    {
        return -1;
    }
    // Otherwise, return index as normal.
    return v[index];
}

int Bucket::merge(Bucket b)
{
    // Merging bucket b
    for (int num : b.v)
    {
        v.push_back(num);
    }
    sort();
    return size();
}

int main(int argc, char *argv[])
{
    srand(time(0));

    int bucketCount = stoi(argv[1]);
    int bucketSize = stoi(argv[2]);
    int bucketMin = stoi(argv[3]);
    int bucketMax = stoi(argv[4]);
    cout << "Bucket Count:" << bucketCount << endl;
    cout << "Bucket Size:" << bucketSize << endl;
    cout << "Bucket Min Value:" << bucketMin << endl;
    cout << "Bucket Max value:" << bucketMax << endl;

    vector<Bucket> list; // create empty Bucket vector

    Bucket *bptr;

    for (int i = 0; i < bucketCount; i++) // creating bucketCount Buckets
    {
        bptr = new Bucket; // allocating new Bucket
        bptr->generate(bucketSize, bucketMin, bucketMax);
        // Bucket::generate(int,int,int,int)
        list.push_back(*bptr); // pushing Bucket onto list
    }

    for (auto it = list.begin(); it != list.end(); it++)
    {
        it->sort(); // Bucket::sort
    }

    Bucket endGame;         // create empty Bucket to merge ALL buckets

    while (list.size() > 0) // vector<Bucket>::size()
    {
        endGame.merge(list[0]); // merge first bucket in list into endGame
        list.erase(list.begin()); // erase the first bucket in the list
    }

    // write all the numbers in endGame bucket to a file
    fstream out("bucketList.out", ios::out);

    for (int i = 0; i < endGame.size(); i++) // Bucket::size()
        out << endGame.atIndex(i) << endl;   // Bucket::atIndex(int)
    
    cout << "Global Swap Count:" << globalSwapCount << endl;
    cout << "\nbucketList.out has " << bucketCount * bucketSize << " sorted numbers\n ";
        return 0;
}