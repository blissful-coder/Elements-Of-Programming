package main

import "fmt"

func main() {
	N := 8 // Change N to the desired size of the chessboard
	solveNQueens(N)
}

func solveNQueens(N int) {
	board := make([][]bool, N)
	for i := range board {
		board[i] = make([]bool, N)
	}

	solutions := [][]string{}
	backtrack(board, 0, &solutions)
	printSolutions(solutions)
}

func backtrack(board [][]bool, col int, solutions *[][]string) {
	N := len(board)
	if col == N {
		*solutions = append(*solutions, convertToStrings(board))
		return
	}

	for row := 0; row < N; row++ {
		if isSafe(board, row, col) {
			board[row][col] = true
			backtrack(board, col+1, solutions)
			board[row][col] = false
		}
	}
}

func isSafe(board [][]bool, row, col int) bool {
	N := len(board)

	// Check if there is a queen in the same row
	for i := 0; i < col; i++ {
		if board[row][i] {
			return false
		}
	}

	// Check if there is a queen in the upper diagonal
	for i, j := row, col; i >= 0 && j >= 0; i, j = i-1, j-1 {
		if board[i][j] {
			return false
		}
	}

	// Check if there is a queen in the lower diagonal
	for i, j := row, col; i < N && j >= 0; i, j = i+1, j-1 {
		if board[i][j] {
			return false
		}
	}

	return true
}

func convertToStrings(board [][]bool) []string {
	N := len(board)
	result := make([]string, N)
	for i := 0; i < N; i++ {
		for j := 0; j < N; j++ {
			if board[i][j] {
				result[i] += "Q"
			} else {
				result[i] += "."
			}
		}
	}
	return result
}

func printSolutions(solutions [][]string) {
	for i, sol := range solutions {
		fmt.Printf("Solution %d:\n", i+1)
		for _, row := range sol {
			fmt.Println(row)
		}
		fmt.Println()
	}
}
