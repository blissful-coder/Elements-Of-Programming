#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxCost(vector<vector<int>>& matrix, vector<int>& path) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Create a 2D DP table to store the maximum cost at each cell
    vector<vector<int>> dp(rows, vector<int>(cols, 0));

    // Create a 2D table to store the path at each cell
    vector<vector<pair<int, int>>> pathTable(rows, vector<pair<int, int>>(cols, make_pair(0, 0)));

    // Base case: the maximum cost at the starting cell is the value at that cell
    dp[0][0] = matrix[0][0];

    // Calculate the maximum cost and the path for each cell in the matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Update the maximum cost for the current cell by considering the maximum of the costs from the previous cells
            if (i > 0 && dp[i][j] < dp[i-1][j] + matrix[i][j]) {
                dp[i][j] = dp[i-1][j] + matrix[i][j];
                pathTable[i][j] = make_pair(i-1, j);
            }
            if (j > 0 && dp[i][j] < dp[i][j-1] + matrix[i][j]) {
                dp[i][j] = dp[i][j-1] + matrix[i][j];
                pathTable[i][j] = make_pair(i, j-1);
            }
        }
    }

    // Traverse the path from the bottom-right cell to the top-left cell
    int i = rows - 1;
    int j = cols - 1;
    while (i != 0 || j != 0) {
        path.push_back(matrix[i][j]);
        int prev_i = pathTable[i][j].first;
        int prev_j = pathTable[i][j].second;
        i = prev_i;
        j = prev_j;
    }
    path.push_back(matrix[0][0]);

    // Reverse the path to get the correct order
    reverse(path.begin(), path.end());

    // Return the maximum cost at the bottom-right cell
    return dp[rows-1][cols-1];
}

int main() {
    int sz = 3;
    vector<vector<int>> maze = {
        {1, 4, 13},
        {4, 5, 6},
        {7, 8, 9}
    };

    vector<int> path;
    int max_cost = maxCost(maze, path);
    cout << "Maximum Cost: " << max_cost << endl;

    cout << "Path: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) {
            cout << "->";
        }
    }
    cout << endl;

    return 0;
}