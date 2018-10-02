using System;

namespace Application
{
	public class generator
	{
		public Random rnd = new Random();
	}

	public class wektor
	{
		public int size = 0;
		public float tab;

		public wektor(int n)
		{
			this.tab = new float[n];

		}
		public void print()
		{
			foreach (float w in tab) {
				Console.Write (w);
				Console.Write ("  ");
			}
			Console.WriteLine ();
		}

		/*
		public wektor(float a, float b)
		{
			this.x = a;
			this.y = b;
		}
		public void print()
		{
			Console.Write (x);
			Console.Write ("  ");
			Console.Write (y);
			Console.Write ("\n");
		}*/



		public static wektor operator +(wektor t1, wektor t2)
		{
			return new wektor (t1.x + t2.x, t1.y + t2.y);
		}
		public static wektor operator *(wektor t1, float f)
		{
			return new wektor (t1.x * f, t1.y * f);
		}		
		public static float operator *(wektor t1, wektor t2)
		{
			return  (t1.x * t2.x + t1.y * t2.y);
		}
	}

	public class matrix
	{
		public int size = 0;
		public wektor[] tab;	
		public matrix(int i)
		{
			this.size = i;
			tab = new wektor[size];
		}
		public static matrix operator +(matrix t1, matrix t2)
		{
			if (t1.size != t2.size)
				return t1;
			matrix ex = new matrix (t1.size);
			for (int i = 0; i < ex.size; i++) {
				ex.tab [i] = t1.tab [i] + t2.tab [i];
			}
			return ex;
		}
		public static matrix operator *(matrix t1, float f)
		{
			matrix ex = new matrix (t1.size);
			for (int i = 0; i < ex.size; i++) {
				ex.tab [i] = t1.tab [i] * f;
			}
			return ex;
		}
		public static matrix operator *(matrix t1, matrix t2)
		{
			if (t2.size != 2)
				return t1;
			matrix ex = new matrix (t1.size);
			wektor m1 = new wektor(t2.tab[0].x,t2.tab[1].x);			
			wektor m2 = new wektor(t2.tab[0].y,t2.tab[1].y);

			for (int i = 0; i < ex.size; i++) {
				ex.tab [i] = new wektor(t1.tab[i]* m1, t1.tab[i]*m2);
			}
			return ex;
		}
		public static wektor operator *(matrix t1, wektor w)
		{
			if (t1.size != 2)
				return w;
			wektor ex = new wektor(0,0);
			ex.x = t1.tab [0].x * w.x + t1.tab [1].x * w.x;
			ex.y = t1.tab [0].y * w.y + t1.tab [1].y * w.y;
			return ex;
		}


		public void fill_rand(generator z)
		{
			for (int i = 0; i < this.size; i++) {
				float x = (float)z.rnd.NextDouble () * 10;
				float y = (float)z.rnd.NextDouble () * 10;
				wektor temp = new wektor (x, y);
				this.tab [i] =  temp;
			}
		}
		public void print()
		{
			foreach (wektor w in tab) {
				w.print ();
			}
			Console.WriteLine ();
		}
	}
	class Program
	{
		public static void Main()
		{	
			/*
			generator rand = new generator ();
			matrix t1 = new matrix (10);
			matrix t2 = new matrix (10);
			t1.fill_rand (rand);
			t1.print ();
			t2.fill_rand (rand);
			t2.print ();
			matrix t3 = t1 + t2;
			t3.print ();
			matrix t4 = t1 * 5;
			t4.print ();
			matrix t5 = new matrix (2);
			t5.fill_rand (rand);
			t5.print ();
			matrix t6 = t1 * t5;
			t6.print ();
			wektor w1 = new wektor((float)0.3, (float)0.5);
			w1.print ();
			wektor w2 = t5*w1;
c			w2.print ();*/
		}
	}
}

