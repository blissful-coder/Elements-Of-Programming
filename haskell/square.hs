import Control.Monad (guard)

findPairs :: [(Integer, Integer, Integer, Integer)]
findPairs = do
    a <- [1..1000]  -- Assuming positive integers up to 1000
    b <- [1..1000]
    c <- [1..1000]
    d <- [1..1000]
    guard $ a /= b && a /= c && a /= d && b /= c && b /= d && c /= d  -- Ensure all numbers are unique
    guard $ a^2 + b^2 == c^2 + d^2
    return (a, b, c, d)

main :: IO ()
main = do
    let pairs = findPairs
    mapM_ print pairs
