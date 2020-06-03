(*Dominik Hawryluk*)

(*Zadanie 1*)

let rec fibo x =
  if x = 0 || x = 1 then x
  else fibo(x-2) + fibo(x-1);;

let rec fibo_og x =
  let rec aux aktualna nastepna licznik  =
    if licznik = 0 then aktualna
    else aux nastepna (aktualna+nastepna) (licznik-1)
  in
  aux 0 1 x;;

let time f x =
  let t = Sys.time()
  and fx = f x
  in let _ = Printf.printf "Czas wykonania: %fs\n" (Sys.time() -. t)
     in fx;;


time fibo(42);;
time fibo_og(42);;
fibo 6;;
fibo_og 6;;

(*Zadanie 2*)

let root3 x =
  let epsilon = 10e-15 in
  let rec aux(next) =
    if abs_float(next**3. -. x) <= epsilon *.abs_float(x)
    then next
    else aux(next +. ((x/.(next*.next) -. next)/.3.))
  in
  aux(if x > 1. then aux(x/.3.) else x);;


root3(8.);;
root3(-8.);;
root3(3.375);;
root3(1.);;
root3(-0.125);;
root3(0.61*.0.61*.0.61);;

(*Zadanie 3*)

let (<->) x y =
  let (x1,y1,z1) = x in
  let (x2,y2,z2) = y in
  let square c = c *. c in
  sqrt(square((x1-.x2)) +. (square(y1-.y2)) +. (square(z1-.z2)));;

let x = (1.,1.,1.);;
let y = (1.,1.,0.);;
x<->y;;
(4.,5.,12.)<->(4.,0.,0.);;
(8.,10.,7.)<->(3.,6.,4.);;


(*Zadanie 4*)

let rec (<--) xs el =
    match xs with
      [] -> [el]
    | hd::tl when hd < el -> hd::(tl <-- el)
    | _::_ -> el::xs;;


[1;3;5;7] <-- 3;;

[1;2;4;8;16;] <-- 5;;
[1;2;4;5;8] <-- 0;;
["a";"b";"c";"de"] <-- "baaa";;
[1;2;4;8] <-- 16;;



(*Zadanie 5*)

let rec take ind xs =
    match (ind,xs) with
      (_,[]) -> []
    | (a,_) when a <= 0 -> []
    | (b,hd::tl) -> hd::take (b-1) tl;;

take 2 [1;2;3;5;6];;
take (-2) [1;2;3;5;6];;
take 8 [1;2;3;5;6];;
take 4 ['a';'b';'c';'d';'e'];;


(*Zadanie 6*)
let rec drop ind xs =
    match (ind,xs) with
      (_,[]) -> []
     |(a,_) when a <= 0 -> xs
     |(b,hd::tl) -> drop (b-1) tl;;

drop 2 [1;2;3;5;6];;
drop (-2) [1;2;3;5;6];;
drop 8 [1;2;3;5;6];;
drop 4 ['a';'b';'c';'d';'e'];;



(*Zadanie 7*)

let  replicate xs =
  let rec multicate el count =
    if count = 0 then []
    else el::multicate el (count-1)
  and aux ys =
  match ys with
    [] -> []
  | hd::tl when hd <= 0 -> aux tl
  | hd::tl -> (multicate hd hd)@(aux tl)
  in aux xs;;

replicate [1;0;4;-2;3];;
