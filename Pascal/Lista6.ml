(*Dominik Hawryluk*)
type 'a bt = Empty | Node of 'a * 'a bt * 'a bt;;
let isspace ch = (ch =' ') || (ch ='\t') || (ch ='\n') || (ch = '\r') ;;

(*Zadanie 1*)
let zgadnij() =
  begin
    Random.self_init();
    let rand =  Random.int 101
    in let answer = ref 0
       in
       answer := int_of_string(read_line());
       while !answer != rand do
         if !answer < rand then
           print_endline "Moja jest wieksza";
         if !answer > rand then
           print_endline "Moja jest mniejsza";
         answer := int_of_string(read_line());
       done;
       print_endline "Zgadles. Brawo!";
  end;;


(*Zadanie 2*)

let printBT tree =
  let rec print prefix tree =
    match tree with
      Empty ->
       begin
         print_string prefix;
         print_endline "||";
       end
    | Node (value, left, right) ->
       begin
        print (prefix ^ "...") right;
        print_string prefix;
        print_int value;
        print_newline();
        print (prefix ^ "...") left
       end
  in print "" tree;;

(* Zadanie 3*)
(*Kod z wykladu*)
let input_int channel =
  let s = ref "" and  ch  = ref (input_char channel)
  in
  begin
    while isspace (!ch) do ch := input_char channel done;
    while not (isspace (!ch)) do
      s := !s^(String.make 1 !ch);
      ch := input_char channel
    done;
    int_of_string(!s)
  end;;

let sortuj_plik() =
  begin
    let fileName = ref "" in
    print_endline "Podaj nazwe pliku wej";
    fileName := read_line();
    let ic = open_in !fileName in
    let size = int_of_string(input_line ic) in
    let tab = Array.make size 0 in
    begin
      for index = 0 to size-1 do
        tab.(index) <- input_int ic;
      done;
      close_in ic;
      for i = 0 to size-1 do
        let min = ref tab.(i) in
        let minIndex = ref i in
        for j = i+1 to size-1 do
          if tab.(j) < !min then
            begin
              min := tab.(j);
              minIndex := j;
            end
        done;
        tab.(!minIndex) <- tab.(i);
        tab.(i) <- !min;
      done;
    end;
    print_endline "Podaj nazwe pliku wyj";
    fileName := read_line();
    let oc = open_out !fileName in
    for index = 0 to size-1 do
      output_string oc (string_of_int tab.(index));
      output_string oc "\n"
    done;
    close_out oc;
  end;;
