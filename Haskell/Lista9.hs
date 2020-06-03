{- Dominik Hawryluk -}
import Data.List

--Zadanie 1
data Tree a = Leaf a | Node (Tree a) (Tree a)
  deriving (Eq,Ord,Show,Read)

nrOfLeaves:: Tree a -> Int
nrOfLeaves (Leaf _) = 1
nrOfLeaves(Node r l) =  nrOfLeaves l + nrOfLeaves r

isBalanced::Tree a -> Bool
isBalanced tree = aux tree where
  aux (Leaf _) = True
  aux (Node left right) = isBalanced left && isBalanced right
                          && abs(nrOfLeaves left - nrOfLeaves right) <= 1
  

tr = Node (Node (Leaf 5) (Node (Leaf 3) (Leaf 4))) (Leaf 1)
tr2 = Node (Node (Node (Leaf 3) (Leaf 4)) (Leaf 5)) (Node (Leaf 1) (Leaf 2))
yr1 = isBalanced tr
yr2 = isBalanced tr2

--Zadanie 2

balance::[a] -> Tree a
balance (x:[]) = Leaf x
balance xs = Node (balance firstHalf) (balance secondHalf) where
  (firstHalf, secondHalf) = splitAt ((length xs) `div` 2) xs

t1 = balance [1,2,3,4,5]
t2 = balance [1,2,3,4,5,6,7,8,9,10]
y1 = isBalanced t1
y2 = isBalanced t2

--Zadanie 3

data BTree a = BLeaf | BNode (BTree a) a (BTree a)
             deriving (Eq,Ord,Show,Read)

btree = BNode (BNode BLeaf 1 BLeaf) 5 (BNode (BNode BLeaf 7 BLeaf) 9 (BNode BLeaf 11 BLeaf))
emptybt = BLeaf

bTreeIn::BTree a -> Int
bTreeIn tree = aux tree 0 where
  aux BLeaf _ = 0
  aux (BNode  left _ right)  numb = numb + aux left (numb+1) + aux right (numb+1)

inpath = bTreeIn btree
inpath2 = bTreeIn emptybt

bTreeOut::BTree a -> Int
bTreeOut tree = aux tree 0 where
  aux BLeaf numb = numb
  aux (BNode  left _ right)  numb = aux left (numb+1) + aux right (numb+1)

outpath = bTreeOut btree
outpath2 = bTreeOut emptybt

--Zadanie 4
data MtreeL a = MTL a [MtreeL a]
              deriving (Eq,Ord,Show,Read)

--a
preRoute::MtreeL a -> [a]
preRoute tree = reverse (aux tree [] []) where
  aux (MTL a []) accu [] = a:accu
  aux (MTL a (hd:tl)) accu ls = aux hd (a:accu) (tl++ls)
  aux (MTL a []) accu (hd:tl) = aux hd (a:accu) tl 


mtr = MTL 5 [(MTL 3 [(MTL 6 []), (MTL 7 [])]), (MTL 10 [])]
mtr2 = MTL 5 []
mtr3 = MTL 5 [(MTL 3 [(MTL 6 [(MTL 7 []), (MTL 8 [])]), (MTL 10 [])]), (MTL 13 []), (MTL 15 [(MTL 18 []), (MTL 20 [])])]

preR = preRoute mtr
preR2 = preRoute mtr2
preR3 = preRoute mtr3

--b
breadthRoute::MtreeL a ->[a]
breadthRoute tree = reverse (aux tree [] []) where
  aux (MTL a []) accu [] = a:accu
  aux (MTL a (hd:tl)) accu [] = aux hd (a:accu) tl 
  aux (MTL a ls) accu (hd:tl) = aux hd (a:accu) (tl++ls)

bR = breadthRoute mtr
bR2 = breadthRoute mtr2
bR3 = breadthRoute mtr3
