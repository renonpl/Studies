{-# LANGUAGE DeriveFunctor #-}
{-# LANGUAGE  DeriveFoldable#-}
{- Dominik Hawryluk -}
import Data.Monoid
import Data.Foldable

data MtreeL a = MTL a [MtreeL a]
              deriving (Eq, Ord, Show, Read)

mt1 = MTL 1 [MTL 2 [], MTL 3 [], MTL 4[]]
mt2 = MTL 5 [MTL 6 [], MTL 7 [MTL 11 [MTL 12 [], MTL 13 [], MTL 14 []]], MTL 8 []]
mt3 = MTL 10 [mt1, mt2]

--Zadanie 1

--a
foldMtL ::Monoid a => MtreeL a -> a
foldMtL (MTL a []) = a
foldMtL (MTL a ls) =
   a <> foldMap foldMtL ls 

test1 = foldMtL $ MTL (Product 1) [MTL (Product 2) [], MTL (Product 3) [], MTL (Product 4) []]
test2 = foldMtL $ MTL (Sum 5) [MTL (Sum 6) [], MTL (Sum 7) [MTL (Sum 11) [MTL (Sum 12) [], MTL (Sum 13) [], MTL (Sum 14) []]], MTL (Sum 8) []]

--b
foldMtLMap ::Monoid a => (t -> a) ->  MtreeL t -> a
foldMtLMap toMonoid (MTL a []) = toMonoid a
foldMtLMap toMonoid (MTL a ls) =
   toMonoid a <> foldMap (foldMtLMap toMonoid) ls

x1 = foldMtLMap Sum mt1
x2 = foldMtLMap Product  mt2
x3 = getSum $ foldMtLMap Sum mt3
x4 = getAll $ foldMtLMap  (All. (>5)) mt3
x5 = getAny $ foldMtLMap (Any. (==10)) mt3



--Zadanie 2


instance Functor MtreeL where
   fmap f (MTL a []) = MTL (f a) []
   fmap f (MTL a ls) = MTL (f a) (map (fmap f) ls)


y1 = ((+1) <$> mt1) == MTL 2 [MTL 3 [], MTL 4 [], MTL 5 []]
y2 = ((*2) <$> mt2)
y3 = ((*(-1)) <$> mt3)

--Zadanie 3

instance Foldable MtreeL where
  foldMap toMonoid (MTL a []) = toMonoid a
  foldMap toMonoid (MTL a ls) =
    toMonoid a <> foldMap (foldMap toMonoid) ls 


z1 = sum mt1 == 10
z2 = sum mt3 == 96
z3 = maximum mt2
z4 = toList mt1




--deriving functor foldable
data MtreeL' a = MTL' a [MtreeL' a]
              deriving (Eq, Ord, Show, Read, Functor, Foldable)

mt1' = MTL' 1 [MTL' 2 [], MTL' 3 [], MTL' 4[]]
mt2' = MTL' 5 [MTL' 6 [], MTL' 7 [MTL' 11 [MTL' 12 [], MTL' 13 [], MTL' 14 []]], MTL' 8 []]
mt3' = MTL' 10 [mt1', mt2']


y1' = ((+1) <$> mt1') == MTL' 2 [MTL' 3 [], MTL' 4 [], MTL' 5 []]
y2' = ((*2) <$> mt2')
y3' = ((*(-1)) <$> mt3')

z1' = sum mt1' == 10
z2' = sum mt3' == 96
z3' = maximum mt2'
z4' = toList mt1'
z5' = toList mt3
