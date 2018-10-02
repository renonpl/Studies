using System;

namespace main
{

	public class Elem<T>
	{
		public T value;
		public Elem<T> next = null;
		public Elem<T> last = null;
		public Elem(T value)
		{
			this.value = value;
		}
	}

	public class Lista<T>
	{
		private Elem<T> start = null;	
		private Elem<T> end = null;
		private int size = 0;
		public void add_top(T value)
		{
			Elem<T> temp = new Elem<T> (value);
			if (size == 0) {
				start = temp;
				end = temp;
			} else {
				end.next = temp;
				temp.last = end;
				end = temp;
			}
			size++;
		}
		public void add_front(T value)
		{
			Elem<T> temp = new Elem<T> (value);
			if (size == 0) {
				start = temp;
				end = temp;
			} else {
				start.last = temp;
				temp.next = start;
				start = temp;
			}
			size++;
		}
		public T pop_top()
		{
		//			if (this.is_empty ())
		//					throw new System.("Lista pusta");
			Elem<T> temp = end;
			if (size == 1) {
				start = null;
				end = null;
				size--;
				return temp.value;
			}			
			end = temp.last;
			end.next = null;
			size--;
			return temp.value;
		}
		public T pop_front()
		{
			//		if (this.is_empty ())
			Elem<T> temp = start;
			if (size == 1) {
				start = null;
				end = null;
				size--;
				return temp.value;
			}
			start = temp.next;
			start.last = null;
			size--;
			return temp.value;
		}
		public bool is_empty()
		{
			return size == 0;
		}

	}

	class Program
	{
		public static void Main()
		{
			return;
		}
	}
}


