module Main where

data Tree a = Leaf | Node (Tree a, a, Tree a) deriving (Show)

look :: Ord a => a -> Tree a -> Bool
look _ Leaf = False
look elt (Node (left, item, right))
    | elt < item = look elt left
    | elt > item = look elt right
    | otherwise  = True

ins :: Ord a => a -> Tree a -> Tree a
ins elt Leaf = Node (Leaf, elt, Leaf)
ins elt t@(Node (left, item, right))
    | elt < item = Node (ins elt left, item, right)
    | elt > item = Node (left, item, ins elt right)
    | otherwise  = t

mmap :: (a -> b) -> [a] -> [b]
mmap f = foldr (\x y -> f x : y) []

fact :: Integer -> Integer
fact 0 = 1
fact x = x * fact (x - 1)

fact2 :: Integer -> Integer
fact2 x
    | x > 1 = x * fact2 (x-1)
    | otherwise = 1

isort :: Ord a => [a] -> [a]
isort lst = f lst []
    where
        f [] a = a
        f (x:xs) a = f xs (insertInOrder x a)

        insertInOrder x [] = [x]
        insertInOrder x lst@(y:ys)
            | x < y     = x : lst
            | otherwise = y : insertInOrder x ys
