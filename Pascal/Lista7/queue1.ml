(*Dominik Hawryluk*)
module type QUEUE_FUN =
sig
  (* Module [QueueFun]: first-in first-out queues *)
  (* This module implements queues (FIFOs)in a functional way. *)
  type 'a t
        (* The type of queues containing elements of type ['a]. *)
  exception Empty of string
        (* Raised when [first] is applied to an empty queue. *)
  val create: unit -> 'a t
        (* Return a new queue, initially empty. *)
  val enqueue: 'a * 'a t -> 'a t
        (* [enqueue x q] adds the element [x] at the end of queue [q]. *)
  val dequeue: 'a t -> 'a t
        (* [dequeue q] removes the first element in queue [q] *)        
  val first: 'a t -> 'a
        (* [first q] returns the first element in queue [q] without removing  
           it from the queue, or raises [Empty] if the queue is empty.*) 
  val isEmpty: 'a t -> bool
        (* [isEmpty q] returns [true] if queue [q] is empty, 
           otherwise returns [false]. *)
end;;
(*a*)
module Queue : QUEUE_FUN =
  struct
    type 'a t = EmptyQueue | Enqueue of 'a * 'a t
    exception Empty of string
    let create() = EmptyQueue
    let rec enqueue = function
        (value, EmptyQueue) -> Enqueue(value,EmptyQueue)
      | (value, Enqueue(elem,tail)) -> Enqueue(elem, enqueue(value, tail))
    let dequeue = function
        Enqueue(_,tail) -> tail
      | EmptyQueue -> EmptyQueue
    let first = function
        Enqueue(value,_) -> value
      | EmptyQueue -> raise (Empty "module Queue: first")
    let isEmpty = function
        Enqueue(_,_) -> false
      | EmptyQueue -> true
  end;;
                                              

let q = Queue.create();;
Queue.isEmpty q;;
Queue.first q;;
let p = Queue.(enqueue(5, enqueue(3, enqueue(1, create()))));;
Queue.isEmpty p;;
Queue.first p;;
let s = Queue.dequeue p;;
Queue.first s;;
Queue.(dequeue(dequeue s));;


(*b*)
module Queue2 : QUEUE_FUN =
  struct
    type 'a t = 'a list
    exception Empty of string
    let create() = []
    let rec enqueue = function
        (value, xs) -> xs@[value]
    let dequeue = function
        _::tl -> tl
      | [] -> []
    let first = function
        hd::_ -> hd
      | [] -> raise (Empty "module Queue2: first");;
    let isEmpty = function
        hd::_ -> false
      | [] -> true
  end;;
                                              


let q = Queue2.create();;
Queue2.isEmpty q;;
Queue2.first q;;
let p = Queue2.(enqueue(5, enqueue(3, enqueue(1, create()))));;
Queue2.isEmpty p;;
Queue2.first p;;
let s = Queue2.dequeue p;;
Queue2.first s;;
Queue2.(first(dequeue(dequeue s)));;


(*c*)
module Queue3 : QUEUE_FUN =
  struct
    type 'a t = 'a list * 'a list
    exception Empty of string
    let create() = ([],[])
    let enqueue = function
        (value, ([],[])) -> ([value],[])
      | (value, (xs,ys)) ->(xs,value::ys)
    let dequeue = function
        (_::sc::tl,ys) -> (sc::tl,ys)
      | (_::[],ys) -> (List.rev ys, [])
      | (_,_) -> ([],[])
    let first = function
        (hd::_,_) -> hd
      | ([],_) -> raise (Empty "module Queue3: first")
    let isEmpty = function
        ([],_) -> true
      | (_,_) -> false
  end;;
                                              

let q = Queue3.create();;
Queue3.isEmpty q;;
Queue3.first q;;
let p = Queue3.(enqueue(5, enqueue(3, enqueue(1, create()))));;
Queue3.isEmpty p;;
Queue3.first p;;
let s = Queue3.dequeue p;;
Queue3.first s;;
Queue3.(first(dequeue(dequeue s)));;
