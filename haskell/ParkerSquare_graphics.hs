import Data.List (nub, sort, group)
import Data.Maybe (listToMaybe, catMaybes)
import System.Console.ANSI (setSGR, SGR(..), ConsoleLayer(..), Color(..), ColorIntensity(..), ConsoleIntensity(..), hSetSGR, ConsoleIntensity(BoldIntensity), clearScreen)

-- Generate all perfect squares up to a certain limit
perfectSquares :: Int -> [Int]
perfectSquares limit = takeWhile (<= limit) [n^2 | n <- [1..]]

-- Check if a 3x3 grid forms a magic square
isMagicSquare :: [Int] -> Bool
isMagicSquare [a, b, c, d, e, f, g, h, i] =
    let s = a + b + c
    in  all (== s) [a + b + c, d + e + f, g + h + i, a + d + g, b + e + h, c + f + i, a + e + i, c + e + g]
isMagicSquare _ = False

-- Calculate the sums of rows, columns, and diagonals for a partial grid
calculateSums :: [Int] -> ([Int], [Int], [Int])
calculateSums partial = (rowSums, colSums, diagSums)
  where
    rows = [[0,1,2], [3,4,5], [6,7,8]]
    cols = [[0,3,6], [1,4,7], [2,5,8]]
    diags = [[0,4,8], [2,4,6]]
    sums indices = [sum $ map (partial !!) idx | idx <- indices, all (< length partial) idx]
    rowSums = sums rows
    colSums = sums cols
    diagSums = sums diags

-- Check if at least 3 sums are the same
atLeast3SameSums :: [Int] -> [Int] -> [Int] -> Bool
atLeast3SameSums rowSums colSums diagSums =
    let allSums = rowSums ++ colSums ++ diagSums
        groupedSums = map length $ group $ sort allSums
    in any (>= 3) groupedSums

-- Print a square with colors and sums
printSquare :: [Int] -> IO ()
printSquare squares = do
    let (rowSums, colSums, diagSums) = calculateSums squares
    setSGR [SetColor Foreground Vivid Yellow]
    putStrLn "Current Square: "
    putStrLn $ formatSquare squares
    setSGR [Reset]

    if atLeast3SameSums rowSums colSums diagSums
        then do
            setSGR [SetColor Foreground Vivid Green]
            putStrLn $ "Row sums: " ++ show rowSums
            putStrLn $ "Col sums: " ++ show colSums
            putStrLn $ "Diag sums: " ++ show diagSums
            setSGR [Reset]
        else return ()

    putStrLn ""
  where
    formatSquare :: [Int] -> String
    formatSquare sq = unlines [formatRow (take 3 sq), formatRow (take 3 $ drop 3 sq), formatRow (take 3 $ drop 6 sq)]

    formatRow :: [Int] -> String
    formatRow = unwords . map show

-- Try to build a Parker Square using backtracking
findParkerSquare :: [Int] -> [Int] -> IO (Maybe [Int])
findParkerSquare squares partial
    | length partial > 9 = return Nothing  -- Abort if partial has more than 9 elements
    | length partial == 9 = do
        printSquare partial
        return $ if isMagicSquare partial then Just partial else Nothing
    | otherwise = do
        printSquare partial
        results <- mapM (tryNextSquare partial) (filter (`notElem` partial) squares)
        return $ listToMaybe (catMaybes results)
  where
    tryNextSquare :: [Int] -> Int -> IO (Maybe [Int])
    tryNextSquare partial nextSquare = findParkerSquare squares (partial ++ [nextSquare])

main :: IO ()
main = do
    let limit = 1000000
    let squares = take 9 $ perfectSquares limit
    result <- findParkerSquare squares []
    case result of
        Just parkerSquare -> do
            putStrLn "Parker Square found:"
            setSGR [SetColor Foreground Vivid Green]
            putStrLn $ formatSquare parkerSquare
            setSGR [Reset]
        Nothing -> putStrLn "No Parker Square found."

    where
      formatSquare :: [Int] -> String
      formatSquare sq = unlines [formatRow (take 3 sq), formatRow (take 3 $ drop 3 sq), formatRow (take 3 $ drop 6 sq)]

      formatRow :: [Int] -> String
      formatRow = unwords . map show
