
(* Dominik Hawryluk*)

(*Zadanie 1*)

let curry3 f x y z = f (x,y,z);;
let uncurry3 f(x,y,z) = f x y z;;

let curry3a = function f -> function x -> function y ->
                                           function z -> f(x,y,z);;

let uncurry3a = function f -> function (x,y,z) -> f x y z;;

(*Zadanie 2*)
let rec czyIstniejea p xs =
  match xs with
  | [] -> false
  | hd::tl ->  p hd || czyIstniejea p tl;;

let t = [1;2;3;5];;
let t2 = ["abc";"ba";"af";"hag";"p"];;
czyIstniejea (function x -> x=2) t;;
czyIstniejea (function x -> x>10) t;;
czyIstniejea (function s -> String.length s > 3) t2;;
czyIstniejea (function s -> String.length s = 3) t2;;
czyIstniejea (function s -> String.length s = 3) [];;

let czyIstniejeb p xs =
  List.fold_left (fun q x -> q || p x) false xs;;

czyIstniejeb (function x -> x=2) t;;
czyIstniejeb (function x -> x>10) t;;
czyIstniejeb (function s -> String.length s > 3) t2;;
czyIstniejeb (function s -> String.length s = 3) t2;;
czyIstniejeb (function s -> String.length s = 3) [];;

let czyIstniejec p xs =
  List.fold_right (fun x q -> q || p x) xs false;;

czyIstniejec (function x -> x=2) t;;
czyIstniejec (function x -> x>10) t;;
czyIstniejec (function s -> String.length s > 3) t2;;
czyIstniejec (function s -> String.length s = 3) t2;;
czyIstniejec (function s -> String.length s = 3) [];;


(*Zadanie 3*)

let filter pred xs =
  List.fold_right (fun x ys  -> if pred x then x::ys else ys) xs [];;


let l = [1;2;4;2;5];;
filter(function x -> x = 2) l;;
let l2 = [-5;0;4;5;2;-4;2;-8];;
filter(function x -> x > 0) l2;;
filter(function x -> x > 10) l2;;
let l3 = ['a';'b';'h';'o';'c';'z'];;
filter (function x -> x > 'd') l3;;
filter (function x -> x > 'd') [];;


(*Zadanie 4*)

let rec usun1a pred xs =
  match xs with
  | [] -> []
  | hd::tl -> if pred hd then tl else hd:: usun1a pred tl;;

let usun1b pred xs =
  let rec aux accu ys =
    match ys with
    | [] -> List.rev accu
    | hd::tl -> if pred hd then List.rev_append accu tl else aux (hd::accu) tl in
  aux [] xs;;

let l = [1;2;3;2;5];;
usun1a (function x -> x=2) l;;
usun1b (function x -> x=2) l;;
let l2 = [1;4;6;2;8;3;8;8;8;8];;
usun1a (function x -> x=8) l2;;
usun1b (function x -> x=8) l2;;
let l3 = ['a';'y';'b';'b';'c';'y'];;
usun1a (function x -> x > 'w') l3;;
usun1b (function x -> x > 'w') l3;;

usun1b (function x -> false) l3;;
usun1a (function x -> x > 'w') [];;
usun1b (function x -> x > 'w') [];;


(*Zadanie 5*)
let rec take ind xs =
    match (ind,xs) with
      (_,[]) -> []
    | (a,_) when a <= 0 -> []
    | (b,hd::tl) -> hd::take (b-1) tl;;

let rec drop ind xs =
    match (ind,xs) with
      (_,[]) -> []
     |(a,_) when a <= 0 -> xs
     |(b,hd::tl) -> drop (b-1) tl;;



let  mergesort f xs =
  let rec sort ys  =
    if List.tl(ys) != [] then
      let len = List.length(ys)/2 in
      let ls = sort (take len ys) in
      let  ms = sort(drop len ys) in
      merge(ms,ls)
    else ys
    and  merge(ms,ns) =
    match (ms,ns) with
    | ([],_) -> ns
    | (_,[]) -> ms
    | (h1::t1,h2::t2) -> if f h1 h2 then h1::merge(t1,ns) else  h2::merge(ms,t2)
in sort xs;;
  
let s = [1;2;3;5;4;6;0];;
mergesort (>) s;;
mergesort (<) s;;
let s2 = [(1,2);(1,3);(1,1);(2,5);(0,1)];;
mergesort (fun x y -> fst(x) > fst(y)) s2;;
