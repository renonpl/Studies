import java.io.*;
import java.util.*;

class Elem<T>
{
    public Elem next = null;
    public T wart;
    Elem(T wart)
    {
        this.wart = wart;
    }
    Elem()
    {
    }
}

class Stack<T> implements Collection<T>{
    private Elem<T> start = null;
    private int size;

    Stack() {
        this.size = 0;
        Elem<T> temp = new Elem<>();
        start = temp;
    }

    public boolean add(Object obj) {
        size++;
        Elem nowy = new Elem(obj);
        if (size == 1) {
            this.start = nowy;
            return true;
        }
        Elem temp = this.start;
        while (temp.next != null) temp = temp.next;
        temp.next = nowy;
        return true;
    }

    public T pop() {
        size--;
        T zwrot = this.start.wart;
        this.start = this.start.next;
        return zwrot;
    }

    public boolean remove(Object obj) {
        try {
            Elem prev = null;
            Elem temp = start;
            while (temp != null) {
                if (temp.wart == obj) {
                    if (temp == start) {
                        start = temp.next;
                        size--;
                        return true;
                    }
                    prev.next = temp.next;
                    size--;
                    return true;
                }
                prev = temp;
                temp = temp.next;
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
        return false;
    }

    public void wypisz() {
        Elem temp = start;
        while (temp != null) {
            System.out.println(temp.wart);
            temp = temp.next;
        }
        return;
    }

    public void clear()
    {
        start = null;
        size = 0;
    }

    public boolean contains(Object t) {
        try {
            Elem temp = start;
            while (temp != null) {
                if (temp.wart == t) {
                    return true;
                }
                temp = temp.next;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }
    @Override
    public boolean retainAll(Collection st)
    {
        Elem prev = null;
        Elem temp = start;
        while(temp != null) {
            if (!st.contains(temp.wart)) {
                if (temp == start)
                {
                    size--;
                    temp = start.next;
                    start = temp;
                    continue;
                }
                size--;
                prev.next = temp.next;
                temp = temp.next;
                continue;
            }
            prev = temp;
            temp = temp.next;
        }
        return true;
    }
    @Override
    public boolean removeAll(Collection st)
    {
        Elem prev = null;
        Elem temp = start;
        while(temp != null) {
            if (st.contains(temp.wart)) {
                if (temp == start)
                {
                    temp = start.next;
                    start = temp;
                    size--;
                    continue;
                }
                prev.next = temp.next;
                temp = temp.next;
                size--;
                continue;
            }
            prev = temp;
            temp = temp.next;
        }
        return true;
    }

    public boolean containsAll(Collection st)
    {
        Elem temp = start;
        while(temp != null) {
            if (st.contains(temp)) {
                temp = temp.next;
                continue;
            }
            return false;
        }
        return true;
    }


    @Override
    public boolean addAll(Collection st)
    {
        Object[] tab = st.toArray();
        for(int i = 0; i < tab.length;i++)
        {
            this.add(tab[i]);
        }
        return true;
    }
    public int size()
    {
        return size;
    }
    public boolean isEmpty()
    {
        if(size == 0) return true;
        return false;
    }

    public Object[] toArray()
    {
        try {
            Object[] tab =  new Object[size];
            System.out.println(size);
            Elem temp = start;
            for (int i = 0; i < size; i++) {
                tab[i] = (T) temp.wart;
                temp = temp.next;
            }
            return tab;
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return null;
    }
    public Object[] toArray(Object[] type)
    {
        try {
            Object[] tab = new Object[size + type.length];
            Elem temp = start;
            for (int i = 0; i < type.length; i++) {
                tab[i] = (T) type[i];
            }
            for (int i = type.length; i < size + type.length; i++) {
                tab[i] = (T) temp.wart;
                temp = temp.next;
            }
            return tab;
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return null;
    }
    @Override
    public Iterator iterator() {
        return null;
    }
}

public class coll
{
    public static void main(String[] args)
    {
        List<Integer> lista = new ArrayList<Integer>();
        lista.add(7);
        lista.add(42);
        lista.add(245);
        lista.add(6161);;
        lista.add(14);
        Stack<Integer> st = new Stack<Integer>();
        st.add(132);
        st.add(42);
        System.out.println("Wypisuje po dodaniu dwoch");
        st.wypisz();
        st.retainAll(lista);
        System.out.println("Wypisuje po retainie");

        st.wypisz();
        st.addAll(lista);
        System.out.println("Wypisuje po addAllu");

        st.wypisz();
        st.add(0);
        st.add(5);
        st.removeAll(lista);
        System.out.println("Wypisuje po removie");

        st.wypisz();
        System.out.println("Rozmia");

        Object[] tab = st.toArray();
        System.out.println("Wypisuje element z tablicy");

        System.out.println(tab[1]);

        Collection<Integer>[] tab2 = new Collection[10];
        tab2[0] = lista;
    }
}
