using System;

namespace len
	{
	class Elem
	{
		public int value;
		public Elem next;
		public Elem(int value)
		{
			this.value = value;
		}
	}

	class LazyList
	{
		private Elem start;	
		private Random rnd = new Random();

		public int element(int n){
			if(n < 1) return -1;
			if(start == null){
				start = new Elem(set_value());
			}
			Elem index = start;
			for(int i = 0; i < n-1; i++)
			{
				if (index.next == null) {
					index.next = new Elem (set_value ());
					index = index.next;
				} else {
					index = index.next;
				}
			}
			return index.value;
		}
		protected virtual int set_value()
		{
			return rnd.Next ();
		}
		public int size()
		{
			if (this.start == null)
				return 0;
			int i = 1;
			Elem temp = this.start;
			while (temp.next != null) {
				i++;
				temp = temp.next;
			}
			return i;
		}
	}

	class Prime : LazyList
	{
		private int last = 1;
		protected override int set_value ()
		{
			int i = this.last + 1;
			for (int j = 2; j <= Math.Sqrt (i); j++){
				if (i % j == 0) {
					j = 1;
					i++;
					continue;
				}
			}
			this.last = i;
			return this.last;
		}
	}

	class Program
	{
		public static void Main()
		{
			LazyList test = new LazyList ();
			Console.WriteLine (test.element (1));
			Console.WriteLine (test.size ());
			Console.WriteLine (test.element (100));
			Console.WriteLine (test.size ());
			Console.WriteLine (test.element (102));
			Console.WriteLine (test.size ());
			Console.WriteLine (test.element (100));
			Console.WriteLine (test.element (1));
			Console.WriteLine (test.element (42));
			System.Console.Read();
			Console.WriteLine ();

			LazyList test2 = new Prime ();
			Console.WriteLine (test2.element (1));
			Console.WriteLine (test2.size ());
			Console.WriteLine (test2.element (4));
			Console.WriteLine (test2.size ());
			Console.WriteLine (test2.element (102));
			Console.WriteLine (test2.size ());
			Console.WriteLine (test2.element (100));
			Console.WriteLine (test2.element (1));
			Console.WriteLine (test2.element (42));
			Console.WriteLine (test2.element (25));

		}
	}
}