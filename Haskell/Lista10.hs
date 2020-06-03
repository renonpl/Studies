{- Dominik Hawryluk -}
import System.Random
import System.IO

randomInts :: Int -> (Int, Int) -> Int -> [Int]
randomInts n (lo, hi) zarodek = take n (randomRs (lo, hi) (mkStdGen zarodek))

randomIntIO :: (Int, Int) -> IO Int
randomIntIO (lo, hi) = randomRIO (lo, hi)

takeStones :: [Int] -> Int -> Int -> [Int]
takeStones ls index count = aux ls index count where
  aux (hd:tl) 0 count = if hd-count <= 0 then tl else  (hd-count):tl
  aux (hd:tl) index count =hd:(aux tl (index-1) count)
  aux ls _ _ = ls


randomBoard :: Int -> IO [Int]
randomBoard n = do
  {
    seed <- (randomIntIO (1, 10000));
    return (randomInts n (1,n) seed)
  }

printStones ::  [Int] -> IO()
printStones ls = aux ls 0 where
  aux [] _ = putStrLn ""
  aux (hd:tl) index = do
    {
      putStr ((show index) ++ ". ");
      putStrLn (replicate hd '*');
      aux tl (index+1)
    }

game :: [Int] -> Int -> IO()
game board player  = do
  {
    if board == [] then
      if player == 0 then
        putStr "Gratulacje! Wygrales!"
      else
        do  putStr "Przegrales!";
    else do
      {
        printStones board;
        if player == 1 then do
          {
            putStr "Podaj numer stosu  ";
            fstline <- getLine;
            putStr "Podaj ilosc kamieni  ";
            secline <- getLine;
            let index = read fstline :: Int
                count = read secline :: Int
            in let newBoard = takeStones board index count
            in game newBoard ((player+1) `mod` 2);
           }
        else do
          {
            putStrLn "Teraz moj ruch";
            seed <- randomIntIO (1,100000);
            let randomList = randomInts 2 (0, (length board - 1)) seed in
              let fst:sec:_ = randomList in
                do
                  putStrLn ("Zabieram  " ++ (show (minimum((sec + 2):[(board !! fst)]))) ++ " kamieni. Stos numer " ++ (show fst));
                  game (takeStones board fst  (sec+2)) ((player+1) `mod` 2);
         }
        }
}

startGame :: IO()
startGame = do
  {
    putStr "Witaj. Podaj ilosc stosow  ";
    linia <- getLine;
    seed <- randomIntIO (1,10000);
    player <- randomIntIO (1,2);
    let ilosc =  read linia :: Int
    in let stosy =  randomInts ilosc (1,ilosc) seed
    in game stosy player
  }
