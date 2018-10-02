using System;
namespace main
{
	class Elem
	{
		public char symbol;
		private int size;
		private char[,] tab;
		public int ind;
		public Elem(int ile, char s)
		{
			ind = 0;
			symbol = s;
			size = ile;
			tab = new char[size,6];
		}
		public void insert_pro(string text)
		{
			if (ind == size)
				return;
			for (int i = 0; i < text.Length; i++) {
				tab [ind, i] = text [i];
			}
			tab [ind, text.Length] = '.';
			ind++;
		}
		public string tab_result(int i)
		{
			string res = "";
			int j = 0;
			while(tab[i,j] != '.')
			{		
				res += tab [i, j];
				j++;
			}
			return res;
		}
	}
	
	class Product
	{
		protected int size; 
		public Elem[] tab;
		protected int ind;
		protected char start;
		public Product(int ile, char s)
		{
			start = s;
			ind = 0;
			size = ile;
			tab = new Elem[size];
		}
		public Product()
		{
			start = 'S';
			size = 1;
			tab = new Elem[size];
		}
		protected int search(char w)
		{
			for(int i = 0; i < ind; i++)
			{
				if(tab[i].symbol == w)
					return i;
			}
			return -1;
		}
		public void inert_prod(char w, string t)
		{
			int i = search (w);
			if (-1 == i) {
				i = ind;
				tab [i] = new Elem(10,w);
				ind++;
			}
			tab [i].insert_pro (t);
		}
	}


	class RandomProduct : Product
	{
		private Random rnd = new Random();
		public string generator = "";
		public RandomProduct(int ile, char s)
		{
			start = s;
			size = ile;
			generator += s;
			tab = new Elem[size];
		}
		public void reset()
		{
			generator = "";
			generator += start;
		}
		public void generate()
		{
			for (int i = 0; i < generator.Length; i++) {
				int index = search (generator [i]);
				if (-1 == index)
					continue;
				Elem temp = tab [index];
				string res;
				int random = rnd.Next (0, temp.ind);
				res = temp.tab_result (random);
				generator = generator.Remove (i, generator.Length - i) + res + generator.Remove (0, i+1);
				Console.WriteLine (generator);
				i = -1;
			}
		}
	}

	
	class Program
	{
		public static void Main()
		{
			RandomProduct test =  new RandomProduct (4, 'S');
			test.inert_prod ('S', "FCXFC");

			test.inert_prod ('F', "FCXF");
			test.inert_prod ('F', "");

			test.inert_prod ('X', "+");
			test.inert_prod ('X', "*");
			test.inert_prod ('X', "-");
			test.inert_prod ('X', "/");


			test.inert_prod ('C', "1");
			test.inert_prod ('C', "2");
			test.inert_prod ('C', "3");
			test.inert_prod ('C', "4");
			test.inert_prod ('C', "5");
			test.inert_prod ('C', "6");
			test.inert_prod ('C', "7");
			test.inert_prod ('C', "8");
			test.inert_prod ('C', "9");
			test.inert_prod ('C', "CC");

			test.generate ();
			Console.WriteLine (test.generator);

		}
	}
}
