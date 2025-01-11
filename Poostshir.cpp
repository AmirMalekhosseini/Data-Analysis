#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main() {
    fast_io();

    int size;
    cin >> size;

    vector<int> numbers(size);

    for (int i = 0; i < size; ++i) {
        cin >> numbers[i];
    }

    // Map to store divisor counts
    unordered_map<int, int> divisor_count;

    // Calculate the divisors for each number in the list
    for (int i = 0; i < size; ++i) {
        for (int d = 1; d * d <= numbers[i]; ++d) {
            if (numbers[i] % d == 0) {
                divisor_count[d]++;
                if (d != numbers[i] / d) {
                    divisor_count[numbers[i] / d]++;
                }
            }
        }
    }

    int minimum_frequency = size / 2;
    int largest_divisor = -1;
    for (unordered_map<int, int>::iterator itr = divisor_count.begin(); itr != divisor_count.end(); ++itr) {
        if (itr->second >= minimum_frequency) {
            largest_divisor = max(largest_divisor, itr->first);
        }
    }

    // Output the result
    cout << largest_divisor << "\n";

    return 0;
}