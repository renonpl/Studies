using System;
using System.Collections;

namespace main
{
	
	class Elem
	{
		public int value;
		public Elem next = null;
		public Elem(int value)
		{
			if (value == int.MaxValue) {
				this.value = -1;
			} else {
				int i = value + 1;
				for (int j = 2; j <= Math.Sqrt (i); j++) {
					if (i % j == 0) {
						j = 1;
						i++;
						continue;
					}
				}
				this.value = i;
			}
		}
	}

	class Prime : IEnumerable
	{
		Elem start;
		public IEnumerator GetEnumerator()
		{
			start = new Elem (2);
			return new PrimeEnum (start);
		}
	}

	class PrimeEnum : IEnumerator
	{
		Elem start;
		private Elem curr;
		public PrimeEnum(Elem lis)
		{
			this.start = lis;
		}
		public bool MoveNext()
		{
			if (this.curr == null)
				this.curr = this.start;
			else {
				this.curr = this.curr.next;
			}
			this.curr.next = new Elem (this.curr.value);
				return this.curr.value != -1;
		}
		public object Current
		{
			get{
				return curr.value;
			}
		}	
		public void Reset()
		{
			this.curr = this.start;
		}
	}
	class Program
	{
		public static void Main()
		{
			Prime pc = new Prime();
			foreach (int p in pc)
				Console.WriteLine (p);
		}
	}
}
