(*Dominik Hawryluk*)
    type 'a t = {mutable first : int; mutable last : int; size : int; mutable arr : 'a option array }
    exception Empty of string
    exception Full of string
    let create(n) =  {first = 0; last = 0 ; size = n; arr = Array.make n None }
    let isFull(q) =
      if q.first = q.last then match q.arr.(q.first) with
                                 Some _ -> true
                               | None -> false
      else false;;
    let isEmpty q =
      if q.arr.(q.first) = None then true
      else false;;  
    let next(i,size) =
      if i + 1  = size then 0
      else i + 1
    let enqueue(elem, q) =
      begin
        if isFull q then raise (Full "module QueueMut: enqueue");
        q.arr.(q.last) <- Some elem;
        q.last <- next(q.last, q.size)
      end
    let dequeue q =
      begin
        if not(isEmpty q) then 
          begin
            q.arr.(q.first) <- None;
            q.first <- next(q.first, q.size)
          end
      end
    let first q =
      match  q.arr.(q.first) with
        Some x -> x
      | None ->  raise (Empty "module QueueMut: first")



(*
let q = QueueMut.create(5);;
QueueMut.isEmpty q;;
QueueMut.first q;;
QueueMut.enqueue(1, q);;
QueueMut.enqueue(2,q);;
QueueMut.enqueue(3, q);;
QueueMut.enqueue(42,q);;
QueueMut.enqueue(51, q);;
QueueMut.enqueue(62,q);;
QueueMut.isEmpty q;;
QueueMut.isFull q;;
QueueMut.first q;;
QueueMut.dequeue q;;
QueueMut.first q;;
QueueMut.isFull q;;
QueueMut.dequeue q;;
QueueMut.dequeue q;;
QueueMut.dequeue q;;
QueueMut.first q;;
QueueMut.dequeue q;;
QueueMut.first q;;*)
