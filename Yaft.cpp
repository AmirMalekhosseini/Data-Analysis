#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

bool is_within_bounds(int row, int col, int total_rows, int total_cols) {
    return row >= 0 && row < total_rows && col >= 0 && col < total_cols;
}

bool search_word(const vector<vector<char>>& board, const string& word, int current_index, int row, int col, vector<vector<bool>>& visited) {
    if (current_index == word.size()) {
        return true;
    }

    static vector<pair<int, int>> adjacent_moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    for (const auto& move : adjacent_moves) {
        int new_row = row + move.first;
        int new_col = col + move.second;

        if (is_within_bounds(new_row, new_col, board.size(), board[0].size()) &&
            !visited[new_row][new_col] && 
            board[new_row][new_col] == word[current_index]) {

            visited[new_row][new_col] = true;
            if (search_word(board, word, current_index + 1, new_row, new_col, visited)) {
                return true;
            }
            visited[new_row][new_col] = false;  // Backtrack
        }
    }

    return false;
}

bool can_construct_word(const vector<vector<char>>& board, const string& word) {
    int total_rows = board.size();
    int total_cols = board[0].size();

    if (word.size() > total_rows * total_cols) {
        return false;
    }

    unordered_map<char, int> char_count;
    for (const auto& row : board) {
        for (char ch : row) {
            char_count[ch]++;
        }
    }

    for (char ch : word) {
        if (char_count[ch]-- <= 0) {
            return false;
        }
    }

    vector<vector<bool>> visited(total_rows, vector<bool>(total_cols, false));

    for (int r = 0; r < total_rows; r++) {
        for (int c = 0; c < total_cols; c++) {
            if (board[r][c] == word[0]) {
                visited[r][c] = true;
                if (search_word(board, word, 1, r, c, visited)) {
                    return true;
                }
                visited[r][c] = false;
            }
        }
    }
    return false;
}

void read_grid(vector<vector<char>>& grid) {
    int rows, cols;
    cin >> rows >> cols;
    grid.resize(rows, vector<char>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> grid[i][j];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<char>> grid;
    read_grid(grid);
    string word_to_find;
    cin >> word_to_find;

    if (can_construct_word(grid, word_to_find)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
