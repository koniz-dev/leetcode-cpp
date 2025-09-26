class Solution {
    public:
        bool isValidSudoku(vector<vector<char>>& board) {
            for (int row = 0; row < board.size(); row++) {
                bool seen[10] = {};
                for (int col = 0; col < board[row].size(); col++) {
                    if (board[row][col] == '.') continue;
    
                    int number = board[row][col] - '0';
                    if (seen[number]) {
                        return false;
                    }
                    seen[number] = true;
                }
            }
    
            for (int col = 0; col < board.size(); col++) {
                bool seen[10] = {};
                for (int row = 0; row < board[col].size(); row++) {
                    if (board[row][col] == '.') continue;
    
                    int number = board[row][col] - '0';
                    if (seen[number]) {
                        return false;
                    }
                    seen[number] = true;
                }
            }
    
            for (int parent_row = 0; parent_row < board.size(); parent_row += 3) {
                for (int parent_col = 0; parent_col < board[parent_row].size(); parent_col += 3) {
                    bool seen[10] = {};
                    for (int child_row = parent_row; child_row < parent_row + 3; child_row++) {
                        for (int child_col = parent_col; child_col < parent_col + 3; child_col++) {
                            if (board[child_row][child_col] == '.') continue;
    
                            int number = board[child_row][child_col] - '0';
                            if (seen[number]) {
                                return false;
                            }
                            seen[number] = true;
                        }
                    }
                }
            }
    
            return true;
        }
    };