#include "arraySubsets.cpp"

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