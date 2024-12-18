#include <iostream>
#include <vector>
using namespace std;

const int MAX_NODES = 301;

bool validateGraph(const vector<vector<int>>& matrix, int nodeCount) {
    for (int i = 0; i < nodeCount; ++i) {
        for (int j = 0; j < nodeCount; ++j) {
            if (i == j && matrix[i][j] != 0) {
                return false;
            }
            if (matrix[i][j] != matrix[j][i]) {
                return false;
            }
        }
    }

    for (int k = 0; k < nodeCount; ++k) {
        for (int i = 0; i < nodeCount; ++i) {
            for (int j = 0; j < nodeCount; ++j) {
                if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                    return false; // Triangle inequality violated
                }
            }
        }
    }
    return true;
}

int computeEdgeCount(const vector<vector<int>>& matrix, int nodeCount) {
    int edgeCount = 0;

    for (int i = 0; i < nodeCount; ++i) {
        for (int j = i + 1; j < nodeCount; ++j) {
            bool isDirectEdge = true;

            for (int k = 0; k < nodeCount; ++k) {
                if (k != i && k != j && matrix[i][j] == matrix[i][k] + matrix[k][j]) {
                    isDirectEdge = false;
                    break;
                }
            }

            if (isDirectEdge) {
                edgeCount++;
            }
        }
    }

    return edgeCount;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> distMatrix(n, vector<int>(n));

    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            cin >> distMatrix[row][col];
        }
    }

    // Validate graph
    if (!validateGraph(distMatrix, n)) {
        cout << -1 << "\n";
        return 0;
    }

    cout << computeEdgeCount(distMatrix, n) << "\n";

    return 0;
}
