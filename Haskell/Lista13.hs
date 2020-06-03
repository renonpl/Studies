{- Dominik Hawryluk -}
import Control.Monad.State
  
--Zadanie 1

data Tree a = Leaf a | Branch (Tree a) (Tree a)
           deriving (Eq, Ord, Show, Read)


label::Tree a -> Tree (a, Int)
label tree = fst(aux tree 0) where
  aux (Leaf a) count = (Leaf (a, count), count+1)
  aux (Branch left right) count =
    let (newLeft, rightCount) = aux left count
    in let (newRight, newCount) = aux right rightCount
       in (Branch newLeft newRight, newCount)
                            
  
  
test = let t = Branch (Leaf 'a') (Leaf 'b')
       in label (Branch t t)

tree2 = Branch (Leaf 'a') (Branch (Branch (Leaf 'b') (Leaf 'c')) (Leaf 'd'))
test2 = label tree2

tree3 = Branch (Leaf 'a') (Branch (Leaf 'b') (Branch (Branch (Branch (Leaf 'c') (Leaf 'd')) (Leaf 'e')) (Leaf 'f')))

test3 = label tree3

  
