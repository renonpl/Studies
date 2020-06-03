{- Dominik Hawryluk -}
import Data.List
--Zadanie 1

lrepeat :: (Int -> Int) -> [a]-> [a]
lrepeat f ls = aux ls 1 (f 0) where
  aux [] _ _ = []
  aux (_:tl) index 0 = aux tl (index + 1) (f index)
  aux (hd:tl) index count = hd : (aux (hd:tl) index (count - 1))
  
z = lrepeat (\x -> x) [1,2,4,8,16]
x = take 10 (lrepeat (\x -> x) [30..])
y = take 15 (lrepeat (\x -> 2*x) [0..])


--Zadanie 2

lsublist :: [Int] -> [a] -> [a]
lsublist xs ll = aux (sort xs) ll 0 where
  aux _ [] _ = []
  aux [] ll _ = ll
  aux (a:xtl) (hd:tl) index |index==a = aux xtl tl (index + 1)
                            |otherwise =  hd:(aux (a:xtl) tl (index+1))
  
x1 = lsublist [1,3,5] [0, 1,2,3,4,5,6,7,8]
x2 = take 10 (lsublist [1,2,3,4] [30..])
x3 = lsublist [0,1,3,2] [9,8,7,6,5,4,3,2,1,0]

--Zadanie 3

root3 :: Double -> Double
root3 x =
    aux (if x > 1 then x/3 else x) where
    aux next =
      if abs(next**3 - x) <= 10e-5 * abs(x) then next
      else aux (next + ((x/(next*next) - next)/3))

y1 = root3 8
y2 = root3 (-8)
y3 = root3 3.375
y4 = root3 1
y5 = root3 (-0.125)
y6 = root3 (0.61*0.61*0.61)


root3l :: Double -> Double
root3l x =
    aux x (iterate (\a -> a + ((x/(a*a) - a)/3)) x) where
    aux next (hd:tl) |abs(next**3 - x) <= 10e-5 * abs(x) = next
                     |otherwise = aux hd tl


z1 = root3l 8
z2 = root3l (-8)
z3 = root3l 3.375
z4 = root3l 1
z5 = root3l (-0.125)
z6 = root3l (0.61*0.61*0.61)
