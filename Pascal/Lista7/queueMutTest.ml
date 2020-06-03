let menu (opt) =
  let numItems = Array.length opt-1
  in
    begin
      print_string "\n\n=================================================== \n";
      print_string opt.(0);print_newline();
      for i=1 to numItems do  print_int i; print_string (". "^opt.(i)); print_newline() done;
      print_string "\nSelect an option: ";
      flush stdout;
      let choice = ref (read_int())
      in 
	while !choice < 1 || !choice > numItems do 
	  print_string ("Choose number between 1 and " ^ string_of_int numItems ^ ": ");
	  choice := read_int();
	done; 
	!choice
    end
;;

let s = ref (QueueMut.create(5));;
let menuItems = Array.make 8 "";;
let quit = ref false;;
let choice = ref 9;;

menuItems.(0) <- "Queue Operations (implementation on mutable array)";
menuItems.(1) <- "create";
menuItems.(2) <- "enqueue";
menuItems.(3) <- "dequeue";
menuItems.(4) <- "first";
menuItems.(5) <- "isEmpty";
menuItems.(6) <- "isFull";
menuItems.(7) <- "quit testing";
while not !quit do
  begin
    choice := menu(menuItems);
    match !choice with
	1 ->
	  begin
	    print_string "Queue size = ";
	    s := QueueMut.create (read_int());
	  end  
      | 2 ->
	  begin
	    print_string "Queue item = ";
	    QueueMut.enqueue (read_int(), !s);
	  end  
      | 3 ->
	  begin
	    QueueMut.dequeue !s;
	    print_string "dequeued\n";
	  end
      | 4 ->
	  begin
	    begin
	      try print_int (QueueMut.first !s)  with 
		  QueueMut.Empty m -> print_string ("Exception: "^m);
	    end;
	    print_newline();
          end
      | 5 ->
	 print_string ("Queue is "^(if QueueMut.isEmpty !s then "" else "not ")^"empty.\n");
      | 6 ->
	    print_string ("Queue is "^(if QueueMut.isFull !s then "" else "not ")^"full.\n");
      | 7 ->
	    quit := true
      | _ ->
	    print_string "IMPOSSIBLE!!!\n"
  end
done
