using System;

namespace lazylist
	{
	class IntStream
	{
		protected int last = -1;
		virtual public int next(){
			if (this.eos () == true) 
				return -1;
			this.last++;
			return this.last;
		}
		virtual protected bool eos(){
			if (this.last == int.MaxValue)
				return true;
			return false;
		}
		public void reset(){
			this.last = -1;
		}
	}

	class PrimeStream : IntStream
	{
		override public int next()
		{
			if (this.eos () == true)
				return -1;
			int i = this.last + 1;
			if (i < 2)
				i = 2;
			for (int j = 2; j <= Math.Sqrt (i); j++){
				if (i % j == 0) {
					j = 1;
					i++;
					this.last = i;
					if (this.eos () == true)
						return -1;
					continue;
				}
			}
			this.last = i;
			return this.last;
		}
	}

	class RandomStream : IntStream
	{
		private Random rnd = new Random();

		protected override bool eos ()
		{
			return false;
		}
		override public int next()
		{
			return rnd.Next ();
		}
	}

	class RandomWorldStream
	{
		private PrimeStream index = new PrimeStream();
		private Random rnd = new Random();
		public string next(){
			int i = index.next ();
			if (i == -1)
				return "";
			string result = "";
			for (int j = 0; j < i; j++) {
				result += (char)('z'-rnd.Next(0,26));
			}
			return result;
		}
	}


	class Program
	{
		public static void Main()
		{
			IntStream test = new IntStream ();
			Console.Write (test.next ());
			Console.Write (test.next ());
			Console.Write (test.next ());
			Console.Write (test.next ());
			test.reset();
			Console.Write ("\n");

			Console.Write (test.next ());
			Console.Write (test.next ());
			Console.Write (test.next ());
			Console.Write (test.next ());
			Console.Write ("\n");

			IntStream test2 = new RandomStream ();
			Console.WriteLine (test2.next ());
			Console.WriteLine (test2.next ());
			Console.WriteLine (test2.next ());
			Console.WriteLine (test2.next ());

			IntStream test3 = new PrimeStream ();
			Console.WriteLine (test3.next ());
			Console.WriteLine (test3.next ());
			Console.WriteLine (test3.next ());
			Console.WriteLine (test3.next ());

			RandomWorldStream test4 = new RandomWorldStream ();
			Console.WriteLine (test4.next ());
			Console.WriteLine (test4.next ());
			Console.WriteLine (test4.next ());
			Console.WriteLine (test4.next ());


			System.Console.Read();

		}
	}
}
