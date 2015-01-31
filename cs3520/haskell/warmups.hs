module Main where

sumList :: [Integer]->Integer
sumList [] = 0
sumList (h:t) = h + (sumList t)

--sumList [1,2,3,4,5]


sumList2 :: [Integer]->Integer
sumList2 lst = foldl (+) 0 lst

--sumList2 [1,2,3,4,5]

productList :: [Integer] -> Integer
productList [] = 0
productList lst = foldr (*) 1 lst

--productList [1,2,3,4,5]
--productList [1,2,3,4,5,0]

appendList :: [a] -> [a] -> [a]
appendList [] []=[]
appendList lst1 lst2= foldr (:) lst2 lst1

--appendList [1,2,3,4,5] [6,7,8,9,10]


quicksort :: Ord a => [a] -> [a]
quicksort [] = []
quicksort (h:t) = (quicksort low) ++ [h] ++ (quicksort high)
    where
        low = filter (< h) t
        high = filter (>= h) t

--quicksort [1,3,2,5,4,6,5,8,7,0]


dropN :: [a] -> Integer -> [a]
dropN lst n = [val | (key, val)<-zip [1..] lst, key /= n]

--dropN [1,3,5,7,9,2,4,6,8,10] 5 

compress :: Eq a => [a] -> [(Integer,a)]
compress = foldr skip []
	where 
		skip x [] = [(1,x)]
		skip x ((c, val):t)
			| x == val = (c+1, val):t
			| otherwise = (1,x) : ((c, val):t)

--compress [1,1,1,2,2,2,3,4,5,1,1,7,3,3]






--data Tree a = Leaf | Branch a (Tree a) (Tree a) deriving (Show, Eq)

--treetolist :: (Ord a) => Tree a -> [a]
--treetolist Leaf [] = []
--treetolist (Leaf a left right) = treetolist left ++ [a] ++ treetolist right

--listorder :: Ord a => [a] -> bool
--listorder [] = True
--listorder treetolist (h:t)
--	| t = listorder (t)
--	| h < t = True

--inorder :: Ord a => Tree a -> bool
--inorder elt Leaf = True
--	where
--		| elt = _
--		| elt > inorder left
--		| elt < inorder right

--atlevel :: Tree a -> Integer -> [a]
--atlevel _ Leaf = []

--Talon notes

--map func (filter func (map func (filter function list)))
--is the same as--
--map func ! filter func $ map func $ filter function list


--Prelude> zip [1..10] [11..20]
--Prelude> zip [1..10] "Hello, my darling"
--Prelude> [x | (key, val)<-zip [1..] "Hello, my darling", key `mod` 3 /= 0]

--naked expresion doesn't have an eqaul sign

