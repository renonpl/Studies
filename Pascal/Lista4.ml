(*Dominik Hawryluk*)
type 'a bt = Empty | Node of 'a * 'a bt * 'a bt;;

(*Zadanie 1*)
let rec sumBT  = function
    Empty -> 0
  | Node(a,t1,t2) -> a + sumBT t1 + sumBT t2;;

let t = Node(1,Node(2,Empty,Node(3,Empty,Empty)),Empty);;
sumBT(t);;
let t1 = Empty;;
sumBT(t1);;
let t2 = Node(-5,Node(-3,Node(-2,Empty,Empty),Empty),Node(-4,Empty,Empty));;
sumBT(t2);;

(*Zadanie 2*)

let rec foldBT f acc t =
  match t with
    Empty -> acc
  | Node(a,t1,t2) -> f a (foldBT f acc t1 , foldBT f  acc t2);;

(*Zadanie 3*)
let sumBT2 t = foldBT (fun a (b,c) -> a+b+c) 0 t;;
let t = Node(1,Node(2,Empty,Node(3,Empty,Empty)),Empty);;
sumBT2 t;;
let t1 = Empty;;
sumBT2 t1;;
let t2 = Node(-5,Node(-3,Node(-2,Empty,Empty),Empty),Node(-4,Empty,Empty));;
sumBT2 t2;;

let inorderBTfold t= foldBT (fun a (b,c) ->b @ a::c) [] t;;
inorderBTfold t;;
inorderBTfold t1;;
inorderBTfold t2;;

let preorderBTfold t= foldBT (fun a (b,c) ->a::b @ c) [] t;;
preorderBTfold t;;
preorderBTfold t1;;
preorderBTfold t2;;

let postorderBTfold t= foldBT (fun a (b,c) ->b@c @[a]) [] t;;
postorderBTfold t;;
postorderBTfold t1;;
postorderBTfold t2;;


(*Zadanie 4*)

let mapBT f t =
  foldBT (fun a (b,c) -> Node(f a,b,c)) Empty t;;
      
mapBT (fun v -> 2*v) t;;
mapBT (fun v -> 2*v) t1;;
mapBT (fun v -> -1*v) t2;;


(*Zadanie 5*)

type 'a tree = L of 'a | N of 'a tree * 'a tree;;

let tr = N(N(N(L(1),L(2)),L(7)),L(5));;

let rec store tree =
  match tree with
    L a  -> [Some a]
  | N(t1,t2) -> store(t1) @ store(t2) @ [None];;

store tr;;
let tr2 = N(L 1,L 4);;
store tr2;;
let tr3 = L 1;;
store tr3;;


(*Zadanie 6*)
(*Do poprawienia*)
let load list =
  let rec aux ls accu =
  match ls with
    [] -> List.hd(accu)
  | hd::t -> match hd with
              Some a -> aux t (L a :: accu)
             | None ->
                if accu = [] || List.tl accu  = [] then invalid_arg "not tree"
                else
                aux t (N(List.hd(List.tl accu), List.hd(accu)) :: List.tl(List.tl accu))
  in
  aux list [];;

load(store(tr));;
load(store(tr2));;
load(store(tr2)) = tr2;;
load(store(tr3));;
load([Some 1; None; Some 3]);;
