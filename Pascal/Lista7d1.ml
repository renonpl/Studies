(*Dominik Hawryluk*)
(*Zadanie 4*)
type ordering= LT| EQ | GT;;

module type ORDER =
  sig
    type t
    val compare: t -> t -> ordering
  end;;

module StringOrder: ORDER with type t = string=
  struct
    type t = string
    let compare s1 s2 = if s1<s2 then LT else
                          if s1>s2 then GT
                          else EQ
  end;;

module IntOrder: ORDER with type t = int =
  struct
    type t = int
    let compare s1 s2 = if s1<s2 then LT else
                          if s1>s2 then GT
                          else EQ
  end;;


module type DICTIONARY =
  sig
    type key(* type of keys *)
    type 'a t(* type of dictionaries *)
    exception DuplicatedKey of key      (* error in insert *)
    val empty: unit -> 'a t(* empty dictionary *)
    val lookup: 'a t->key -> 'a option
    val insert: 'a t -> key * 'a -> 'a t
    val delete: 'a t -> key -> 'a t
    val update: 'a t -> key * 'a -> 'a t(* not necessary *)
  end;;


module Dictionary (Key: ORDER) : DICTIONARY with type key = Key.t =
  struct
    type key =  Key.t
    type 'a t = (Key.t * 'a option) list
    exception DuplicatedKey of key
    let empty() = []
    let rec lookup dict key =
      match dict with 
        (keyDict,Some value)::tl ->
        (match Key.compare key keyDict with
           EQ -> Some value
         | GT -> lookup tl key
         | LT -> None)
      | _ -> None
    let rec insert dict (key, value) =
      match dict with
        [] -> [(key,Some value)]
      | (keyDict,_) as elem::tl ->
         match Key.compare key keyDict with
                     EQ -> raise(DuplicatedKey key)
         | LT -> (key,Some value)::dict
         | GT ->  elem::insert tl (key,value)
    let rec delete dict key =
      match dict with
        [] -> []
      | (keyDict,_)as elem::tl ->
         match Key.compare key keyDict with
           GT -> elem:: delete tl key
         | _ ->  tl
    let rec update dict (key,value) =
      match dict with
        [] -> [(key,Some value)]  
      | (keyDict,_) as elem::tl ->
         match Key.compare key keyDict with
           EQ -> (key,Some value)::tl
         | LT -> (key,Some value)::dict
         | GT ->  elem::insert tl (key,value)
  end;;


module StringDict = Dictionary(StringOrder);;
let ( <| ) d (k,x) = StringDict.update d (k,x);;
let dict = StringDict.empty();;
let dict = dict <| ("kot","cat")<| ("slon","elephant")<| ("pies","dog")<| ("ptak","bird");;
StringDict.lookup dict "pies";;
StringDict.lookup dict "papuga";;
let dict = dict <| ("papuga","parrot");;
StringDict.lookup dict "papuga";;

module IntDict = Dictionary(IntOrder);;
let ( <| ) d (k,x) = IntDict.update d (k,x);;
let dict = IntDict.empty();;
let dict = dict <| (1,"cat")<| (18,"elephant")<| (3,"dog")<| (4,"bird");;
IntDict.lookup dict 3;;
IntDict.lookup dict 5;;
let dict = dict <| (5,"parrot");;
IntDict.lookup dict 5;;
IntDict.lookup dict 18;;
IntDict.lookup dict 4;;
IntDict.lookup dict 1;;
IntDict.lookup dict 6;;
