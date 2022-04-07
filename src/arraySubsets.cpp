#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <map>
#include <algorithm>
#include "arraySubsets.hpp"

KnapsackElement knapsack(int W, std::vector<int> wt, std::vector<int> val,
                int n, std::vector<std::vector<KnapsackElement>>& cache)
{
    // base condition
    if (n < 0) {
        KnapsackElement baseCondition;
        baseCondition.value = 0;
        return baseCondition;
    }
    if (cache[n][W].value != -1) {
        return cache[n][W];
    }
    if (wt[n] > W) {
        // Store the value of function call
        // stack in table before return.
        cache[n][W] = knapsack(W, wt, 
                               val, n - 1,
                               cache);
        return cache[n][W];
    }
    else {
        // Store value in table before return.
        KnapsackElement element1 = knapsack(W - wt[n], wt, val, n - 1, cache);
        element1.value += val[n];
        element1.indexes.push_back(n);

        KnapsackElement element2 = knapsack(W, wt, val, n - 1, cache);

        if (element1.value > element2.value) {
             cache[n][W] = element1;
        }
        else {
             cache[n][W] = element2;
        }
        return cache[n][W];
    }
}

bool checkSum(int64_t sumTarget, std::vector<int> a){
    int64_t sumA = std::accumulate(a.begin(), a.end(), (int64_t)0);
    return(sumA > sumTarget);
}

std::vector<int> subsetA(std::vector<int> arr) {
    std::sort(arr.begin(), arr.end());
    int64_t sumTarget = std::accumulate(arr.begin(), arr.end(), (int64_t)0) / (int64_t)2;

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
    std::vector<int> a; // Holds answers
    // Memoization table
    std::vector<std::vector<KnapsackElement>> cache(n,
        std::vector<KnapsackElement>(1, KnapsackElement()));
    int sizeA = 0;
    do
    {
        sizeA++;
        // Increase memoization table size
        for (auto iter = cache.begin(); iter != cache.end(); ++iter) {
            iter->push_back(KnapsackElement());
        }
        std::cout << "Trying size: " << sizeA << std::endl;
        a.clear();
        std::vector<int> indexes = knapsack(sizeA, weights, values, n-1, cache).indexes;
        for (auto iter = indexes.begin(); iter != indexes.end(); ++iter) {
            int num = number[*iter];
            for(int i = 0; i < m[num].occurances; ++i) {
                a.push_back(num);
            }
        }
    } while (!checkSum(sumTarget, a));

    return a;
}