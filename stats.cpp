#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <limits>

/*
Exercise: Basic Statistics Calculator

Implement a Statistics calculator that can process a series of integers and compute basic statistics.

Requirements:
1. Complete the Stats class implementation below
2. The class should store the following statistics:
   - sum: The sum of all numbers
   - max: The maximum value
   - avg: The average (mean) value as a double
3. The program should handle standard input correctly in normal mode

Notes:
- Handle empty input appropriately
- Consider edge cases like negative numbers
- The calculate() method should process the input vector and update all statistics
*/

class Stats {
    public:
        Stats() = default;
        Stats(const std::vector<int>& data) {
            calculate(data);
        }

        void calculate(const std::vector<int>& data);

        int sum{0};
        int max{0};
        double avg{0.0};
};

void
Stats::calculate(const std::vector<int>& data) {
    if (data.empty()) return;

    max = std::numeric_limits<int>::min();
    for (int value : data) {
        sum += value;
        if (value > max) {
            max = value;
        }
    }

    avg = static_cast<double>(sum) / data.size();
}

// -------------------Testing-------------------

bool checkStats(const std::vector<int>& data,
    int expectedSum,
    int expectedMax,
    double expectedAvg)
{
    Stats s(data);

    bool match = true;
    if (s.sum != expectedSum) {
    match = false;
    }
    if (s.max != expectedMax) {
    match = false;
    }
    // Compare avg with some tolerance
    if (std::abs(s.avg - expectedAvg) > 1e-9) {
    match = false;
    }

    return match;
}

int runAllTests() {
    int totalTests = 3;
    int passCount = 0;

    // Test 1: empty input
    if (checkStats({}, 0, 0, 0.0)) {
        passCount++;
    }

    // Test 2: simple positive
    if (checkStats({1,2,3}, 6, 3, 2.0)) {
        passCount++;
    }

    // Test 3: mixed negative/positive
    if (checkStats({-5, 5}, 0, 5, 0.0)) {
        passCount++;
    }

    // Return number of failures
    return (totalTests - passCount);
}

// ------------------------------------------

int main(int argc, char** argv) {
    if (argc > 1 && std::strcmp(argv[1], "--test") == 0) {
        // Test mode
        int fails = runAllTests();
        if (fails == 0) {
            std::cout << "All tests passed!\n";
            return 0; 
        } else {
            std::cout << fails << " test(s) failed.\n";
            return 1;
        }
    } 
    
    // Normal mode
    std::vector<int> data;

    int val;
    while (std::cin >> val) {
        data.push_back(val);
    }

    // If the stream is not at EOF, it means invalid input
    if (!std::cin.eof()) {
        std::cerr << "Invalid input encountered. Exiting.\n";
        return 1; 
    }

    Stats s(data);
    
    std::cout << "Count: " << data.size() << std::endl;
    std::cout << "Sum:   " << s.sum << std::endl;
    std::cout << "Max:   " << s.max << std::endl;
    std::cout << "Avg:   " << std::fixed << std::setprecision(6)
              << s.avg << std::endl;
    
    return 0;
}
