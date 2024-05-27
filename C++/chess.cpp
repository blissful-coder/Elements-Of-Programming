#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

const int BOARD_SIZE = 8;

enum Piece {
    EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
};

enum Color {
    NONE, WHITE, BLACK
};

struct Square {
    Piece piece;
    Color color;
};

class ChessBoard {
private:
    Square board[BOARD_SIZE][BOARD_SIZE];

public:
    ChessBoard() {
        setupBoard();
    }

    void setupBoard() {
        // Initialize empty squares
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                board[i][j].piece = EMPTY;
                board[i][j].color = NONE;
            }
        }

        // Place pawns
        for (int i = 0; i < BOARD_SIZE; i++) {
            board[1][i].piece = PAWN;
            board[1][i].color = WHITE;
            board[6][i].piece = PAWN;
            board[6][i].color = BLACK;
        }

        // Place other pieces
        int backRank[8] = { ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK };
        for (int i = 0; i < BOARD_SIZE; i++) {
            board[0][i].piece = (Piece)backRank[i];
            board[0][i].color = WHITE;
            board[7][i].piece = (Piece)backRank[i];
            board[7][i].color = BLACK;
        }
    }

    void printBoard() {
        for (int i = BOARD_SIZE - 1; i >= 0; i--) {
            cout << i + 1 << " ";
            for (int j = 0; j < BOARD_SIZE; j++) {
                string pieceStr = getPieceString(board[i][j].piece, board[i][j].color);
                cout << pieceStr << " ";
            }
            cout << endl;
        }
        cout << "  a b c d e f g h" << endl;
    }

    bool movePiece(string from, string to) {
        int fromX = from[1] - '1';
        int fromY = from[0] - 'a';
        int toX = to[1] - '1';
        int toY = to[0] - 'a';

        if (isValidMove(fromX, fromY, toX, toY)) {
            board[toX][toY] = board[fromX][fromY];
            board[fromX][fromY].piece = EMPTY;
            board[fromX][fromY].color = NONE;
            return true;
        }
        return false;
    }

private:
    bool isValidMove(int fromX, int fromY, int toX, int toY) {
        // Basic bounds checking
        if (fromX < 0 || fromX >= BOARD_SIZE || fromY < 0 || fromY >= BOARD_SIZE ||
            toX < 0 || toX >= BOARD_SIZE || toY < 0 || toY >= BOARD_SIZE) {
            return false;
        }

        // Check if moving to the same square
        if (fromX == toX && fromY == toY) {
            return false;
        }

        // Check if there is a piece to move
        if (board[fromX][fromY].piece == EMPTY) {
            return false;
        }

        // More movement rules can be added here...

        return true;
    }

    string getPieceString(Piece piece, Color color) {
        switch (piece) {
            case PAWN: return (color == WHITE) ? "♙" : "♟";
            case ROOK: return (color == WHITE) ? "♖" : "♜";
            case KNIGHT: return (color == WHITE) ? "♘" : "♞";
            case BISHOP: return (color == WHITE) ? "♗" : "♝";
            case QUEEN: return (color == WHITE) ? "♕" : "♛";
            case KING: return (color == WHITE) ? "♔" : "♚";
            default: return ".";
        }
    }
};

int main() {
    ChessBoard chessBoard;
    chessBoard.printBoard();

    string from, to;
    while (true) {
        cout << "Enter move (e.g., e2 e4): ";
        cin >> from >> to;
        if (chessBoard.movePiece(from, to)) {
            chessBoard.printBoard();
        } else {
            cout << "Invalid move. Try again." << endl;
        }
    }

    return 0;
}
