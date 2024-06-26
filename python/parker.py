from itertools import permutations

# Generate all perfect squares up to a certain limit
def perfect_squares(limit):
    n = 1
    squares = []
    while n * n <= limit:
        squares.append(n * n)
        n += 1
    return squares

# Check if a 3x3 grid forms a magic square
def is_magic_square(square):
    if len(square) != 9:
        return False
    s = square[0] + square[1] + square[2]
    return all([
        square[0] + square[1] + square[2] == s,
        square[3] + square[4] + square[5] == s,
        square[6] + square[7] + square[8] == s,
        square[0] + square[3] + square[6] == s,
        square[1] + square[4] + square[7] == s,
        square[2] + square[5] + square[8] == s,
        square[0] + square[4] + square[8] == s,
        square[2] + square[4] + square[6] == s,
    ])

# Find all Parker Squares from a list of perfect squares
def find_parker_squares(squares):
    count = 0
    for perm in permutations(squares, 9):
        print(f"Analyzing square {count + 1}: {perm}")
        if is_magic_square(perm):
            print(f"Parker Square found: {perm}")
            return perm
        count += 1
        if count % 100000 == 0:
            print(f"Checked {count} permutations")
    return None

if __name__ == "__main__":
    limit = 1000000
    squares = perfect_squares(limit)[:9]
    parker_square = find_parker_squares(squares)
    if parker_square:
        print("Parker Square found:", parker_square)
    else:
        print("No Parker Square found.")
