// Bundle up identical numbers into single items with weight and cost.
struct Number {
    int occurances = 0;
    int totalValue = 0;
};

// Tracks total values and indexes of itesm in knapsack.
struct KnapsackElement {
    int64_t value = -1;
    std::vector<long int> indexes;
};

// 0-1 recursive knapsack with memoization.
// Return KnapsackElement containing sum and indexes of elements.
KnapsackElement knapsack(long int W, std::vector<int> wt,
                            std::vector<int> val,
                            long int n, std::unordered_map<long int, std::unordered_map<long int, KnapsackElement>>& dp);

// Check if sum A > sumTarget
// sumTarget is half of sum arr
bool checkSum(int64_t sumTarget, std::vector<int> a);

void writeResults(std::vector<int>::iterator iter, const std::vector<int>::iterator& end);

// Given arr, return A
std::vector<int> subsetA(std::vector<int> arr);
