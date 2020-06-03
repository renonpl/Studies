(*Dominik Hawryluk*)

type 'a llist = LNil | LCons of 'a * (unit -> 'a llist);;
type 'a lBT = LEmpty | LNode of 'a * ('a lBT Lazy.t) * ('a lBT Lazy.t);;

let lhd = function
    LNil -> failwith "lhd"
  | LCons (x, _) -> x;;

let ltl = function
    LNil-> failwith "ltl"
  | LCons (_, xf) -> xf();;

let rec ltake = function
    (0, _) -> []
  | (_, LNil) -> []
  | (n, LCons(x,xf)) -> x::ltake(n-1, xf());;


let rec toLazyList = function
    [] -> LNil
  | x::xs -> LCons(x, function() -> toLazyList xs);;

(*Zadanie 1*)

let lFib =
  let rec fibb current next =
    LCons(current, function() -> fibb next (current+next))
  in
  fibb 0 1;;

ltake(0,lFib);;
ltake(5,lFib);;
ltake(15,lFib);;
ltake(30,lFib);;

(*Zadanie 2*)

let lrepeat f llist =
  let rec aux  = function
      (0, LCons(_, lnext)) -> let ls = lnext() in
                              LCons(lhd ls, function() -> aux (f(lhd ls) - 1, ls))
    | (count, ls) -> LCons(lhd ls, function() -> aux (count-1, ls))
  in aux (f(lhd llist), llist);;
                   
let test = lrepeat (fun i -> i+1) lFib;;
ltake(19,test);;
let test2 = lrepeat(fun i -> 2) lFib;;
ltake(20,test2);;
ltake(1,lFib);;
ltake(0,lFib);;

let ls = toLazyList [2;4;8;16;32];;
ltake(25, lrepeat(fun i -> i/2) ls);;
