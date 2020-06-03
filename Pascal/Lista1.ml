(* Dominik Hawryluk *)

(*Zadanie 1*)

let zad1a (x,y) =
  (x*x,y*y);;

let zad1b (x,y) =
   x *. y > 0.0;;

let rec zad1c (x,y)=
  if y = 0 then x else [];;

(*Zadanie 3*)

let rec isSorted x =
  if x = [] || List.tl(x) = [] then true
  else if List.hd(x) <= List.hd(List.tl(x))
  then isSorted (List.tl(x)) else false;;

isSorted [5;3;6;8];;
isSorted [5];;
isSorted [];;
isSorted [1;2;4;4;8;16];;
isSorted ['a'; 'b';'d'];;
isSorted ["aa"; "ac"; "ab"];;


(*Zadanie 2*)
let ends x =
  let rec ends_s y =
    if List.tl(y) = [] then List.hd(y) else ends_s(List.tl(y))
  in
  if x = [] then failwith "listapusta"
  else (List.hd(x),ends_s(x));;

ends [1;2;3;4;5];;
ends [1];;
ends [1;2];;
ends ['a';'b';'e'];;
ends [];;

(*Zadanie 4*)

let powers (x,y) =
  let rec  hp  z y =
    if y = 0 then [z] else z::hp (z*x) (y-1)
  in
  if y = 0 then [1]
  else  1:: hp x (y-1);;

powers(2,3);;
powers(3,5);;
powers(2,1);;
powers(2,0);;




(*Zadanie 5*)
let split (x,y) =
  let rec split_s(xs,a,b) =
    if xs = [] then [a]@[b]
    else if List.hd(xs) <= y
    then split_s(List.tl(xs),a@[List.hd(xs)],b)
    else split_s(List.tl(xs),a,b@[List.hd(xs)])
  in
  split_s (x,[],[]);;

split(['a';'s';'h';'g'],'g');;
split([1;3;5;12;10;6;6;21;72;732],10);;


(*Zadanie 6*)

let segments(x, k) =
  let rec seg_aux(xs, ys, c) =
    if xs = [] then [ys]
    else
      if c = k then ys::seg_aux(xs,[], 0)
      else seg_aux(List.tl(xs),ys@[List.hd(xs)],c+1)
  in
  seg_aux (x,[],0);;

segments([1;2;3;4;5;6;7;8;9], 2);;
segments(["ab";"cd";"ab";"heh";"uo";"haw";"hre"], 3);;


(*Zadanie 7*)
let swap (x,y) =
  let rec swap_s (num,xs, accu) =
    if num = 0 then xs@accu
    else swap_s ((num-1),(List.tl(xs)),accu@[List.hd(xs)])
  in
  swap_s ((y-1),List.tl(x),[List.hd(x)]);;

swap(["5";"6";"a";"b"],2);;
swap(["1";"5";"6";"a";"b"],3);;
swap([1;200;240;270],3);;
