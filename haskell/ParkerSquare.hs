import Data.List (nub, sort, group)
import Data.Maybe (listToMaybe, mapMaybe, catMaybes)
import System.Console.ANSI (setSGR, SGR(SetColor, Reset), ConsoleLayer(Foreground), Color(Green, Yellow), ColorIntensity(Vivid), ConsoleIntensity(BoldIntensity), hSetSGR)

-- ANSI Color Setup
yellow :: [SGR]
yellow = [SetColor Foreground Vivid Yellow]

green :: [SGR]
green = [SetColor Foreground Vivid Green]

reset :: [SGR]
reset = [Reset]

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
atLeast3SameSums :: [Int] -> Bool
atLeast3SameSums partial =
    let (rowSums, colSums, diagSums) = calculateSums partial
        allSums = rowSums ++ colSums ++ diagSums
        groupedSums = map length $ group $ sort allSums
    in not (null groupedSums) && maximum groupedSums >= 3

-- Try to build a Parker Square using backtracking
findParkerSquare :: [Int] -> [Int] -> IO (Maybe [Int])
findParkerSquare squares partial = do
    setSGR yellow
    -- putStrLn $ "Current square: " ++ show partial
    setSGR reset
    if atLeast3SameSums partial then do
        setSGR green
        let (rowSums, colSums, diagSums) = calculateSums partial
        putStrLn $ "Parker Square with at least 3 equal sums found: " ++ show partial ++
                   " | Row Sums: " ++ show rowSums ++
                   " | Col Sums: " ++ show colSums ++
                   " | Diag Sums: " ++ show diagSums
        setSGR reset
    else
        return ()
    if length partial == 9 then
        return $ if isMagicSquare partial then Just partial else Nothing
    else do
        results <- mapM tryNextSquare (filter (`notElem` partial) squares)
        return $ listToMaybe (catMaybes results)
  where
    tryNextSquare nextSquare = findParkerSquare squares (partial ++ [nextSquare])

main :: IO ()
main = do
    let limit = 1000000
    let squares = take 9 $ perfectSquares limit
    result <- findParkerSquare squares []
    case result of
        Just parkerSquare -> putStrLn $ "Parker Square found: " ++ show parkerSquare
        Nothing -> putStrLn "No Parker Square found."
