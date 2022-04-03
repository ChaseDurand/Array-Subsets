#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <map>
#include <algorithm>

struct Number {
    int occurances = 0;
    int totalValue = 0;
};

// Recursive 0-1 knapsack.
// Store indexes of items in indexes.
int64_t knapsack(int weight, const std::vector<int> wts, const std::vector<int> val, int n,
    std::vector<int>& indexes) {    
    
    if ((n < 0) || (weight == 0)) {
        return 0;
    }

    std::vector<int> tmp1i = indexes;
    std::vector<int> tmp2i = indexes;

    // Nth element is excluded.
    int64_t exclude = knapsack(weight, wts, val, n-1, tmp1i);

    // Nth element is included.
    int64_t include = 0;
    if (weight >= wts[n]) {
        tmp2i.push_back(n);
        include = knapsack(weight - wts[n], wts, val, n-1, tmp2i) + val[n];
    }

    if (include >= exclude) {
        indexes = tmp2i;
    }
    else {
        indexes = tmp1i;
    }

    return  std::max(include, exclude);
}

// Check if solution meets:
// * The intersection of A and B is null.
// * The union A and B is equal to the original array.
// * The sum of A's elements is greater than the sum of B's elements.
// Does not check if number of elements in A is minimal.
bool checkSolution(std::vector<int> arr, std::vector<int> a) {
    // Create b
    std::vector<int> b = arr;

    b.erase( std::remove_if( b.begin(), b.end(),
    [&](auto x){return find( a.begin(), a.end(), x) != end(a);}), end(b) );

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    // Check intersection
    std::vector<int> intersection;
    std::set_intersection(a.begin(),a.end(),
                        b.begin(),b.end(),
                        std::back_inserter(intersection));
    if(intersection.size()) {
        return false;
    }

    // Check union
    std::vector<int> arrUnion;
    std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(arrUnion));
    if (arr != arrUnion) {
        return false;
    }

    // Check sum
    int64_t sumA = std::accumulate(a.begin(), a.end(), (int64_t)0);
    int64_t sumB = std::accumulate(b.begin(), b.end(), (int64_t)0);
    if (sumA <= sumB) {
        // Sum A is not greater than sum B
        return false;
    }

    return true;    
}

// Given arr, return A
std::vector<int> subsetA(std::vector<int> arr) {
    std::sort(arr.begin(), arr.end());
    // Create map of <number> to <sum, occurances>
    std::map<int, Number> m;

    for (auto iter = arr.begin(); iter != arr.end(); ++iter) {
        if(m.count(*iter)) {
            // Number is already in map
            m[*iter].occurances += 1;
            m[*iter].totalValue += *iter;
        }
        else {
            // Number is not in map
            m.insert(std::make_pair(*iter, Number()));
            m[*iter].occurances += 1;
            m[*iter].totalValue += *iter;
        }
    }

    std::vector<int> number, values, weights;

    int n = 0;
    for (auto iter = m.begin(); iter != m.end(); ++iter) {
        number.push_back(iter->first);
        values.push_back(iter->second.totalValue);
        weights.push_back(iter->second.occurances);
        n++;
    }

    // Run 0-1 knapsack for different sizes of A.
    // Start with size 1.
    // 0-1 knapsack.
    // Check if solution for A is valid.
    // If so, we're done.
    // If not, increase size of A.
    std::vector<int> a;
    int sizeA = 0;
    do
    {
        sizeA++;
        std::cout << "Trying size: " << sizeA << std::endl;
        a.clear();
        std::vector<int> indexes;
        knapsack(sizeA, weights, values, n-1, indexes);
        for (auto iter = indexes.begin(); iter != indexes.end(); ++iter) {
            int num = number[*iter];
            for(int i = 0; i < m[num].occurances; ++i) {
                a.push_back(num);
            }
        }
    } while (!checkSolution(arr, a));

    reverse(a.begin(), a.end());
    return a;
}

int main(int argc, char *argv[]) {
    // Get path to input as argument.
    if (argc != 2) {
        std::cout << "Error: Pass path of input.txt as argument." << std::endl;
        exit(1);
    }
    std::ifstream input(argv[1]);

    // Get n (number of elements).
    std::string line;
    std::getline(input, line);
    int n = std::stoi(line);

    // Get arr (all other elements).
    std::vector<int> arr;
    arr.reserve(n);
    int counter = 0;
    for (std::string line; std::getline(input, line); ++counter) {
        arr.push_back(std::stoi(line));
    }

    // Check that first value n equals length of arr.
    // No additional error checking is done.
    if (n != counter) {
        std::cout << "Error: Input size mismatch! Expected "
            << n << " but found " << counter << std::endl;
        exit(1);
    }

    std::cout << "Input size n=" << n << std::endl;

    // Pass arr to subsetA()
    auto A = subsetA(arr);

    // Print answer
    for (auto iter = A.begin(); iter != A.end(); ++iter) {
        std::cout << *iter << std::endl;
    }

    return 0;
}