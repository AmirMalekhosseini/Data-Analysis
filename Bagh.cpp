#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> reduce_to_unique_sequence(const vector<int>& arr) {
    vector<int> reduced;
    reduced.push_back(arr[0]);
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] != arr[i - 1]) {
            reduced.push_back(arr[i]);
        }
    }
    return reduced;
}

int longest_palindromic_subsequence(const vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Base case: single elements are palindromes of length 1
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (arr[i] == arr[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;
    vector<int> arr(m);
    for (int i = 0; i < m; ++i) {
        cin >> arr[i];
    }

    vector<int> reduced_arr = reduce_to_unique_sequence(arr);

    int len_reduced = reduced_arr.size();

    int len_longest_pal = longest_palindromic_subsequence(reduced_arr);

    int result = len_reduced - len_longest_pal / 2 - 1;

    cout << result << '\n';

    return 0;
}
