#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>

#define sz 20
using namespace std;

void fill_board(vector<vector<char>> &board)
{
    for (int i = 0; i < sz; i++)
    {
        vector<char> row(sz, '-');
        board.push_back(row);
    }
}

void printBoard(vector<vector<char>> &board)
{
    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            if (board[i][j] == '*')
            {
                cout << "\033[1;32m" << board[i][j] << "\033[0m ";
            }
            else if (board[i][j] == '-')
            {
                cout << "\033[1;31m" << board[i][j] << "\033[0m ";
            }
            else
            {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void traverse_randomly(vector<vector<char>> &board)
{
    srand(time(0));
    int x = rand() % sz;
    int y = rand() % sz;
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    for (int count = 0; count < sz * sz; count++)
    {
        while (board[x][y] == '*')
        {
            int dir = rand() % 4;
            x = (x + dx[dir] + sz) % sz;
            y = (y + dy[dir] + sz) % sz;
        }
        board[x][y] = '*';
        printBoard(board);
        cout << endl;
        this_thread::sleep_for(chrono::milliseconds(25));
    }
}

int main()
{
    vector<vector<char>> board;
    fill_board(board);
    printBoard(board);
    cout << endl;
    traverse_randomly(board);
    return 0;
}