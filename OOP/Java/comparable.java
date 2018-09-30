import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

class Elem implements Comparable<Elem>
{
    public Elem next = null;
    public int value;
    Elem(int value)
    {
        this.value = value;
    }

    public int compareTo(Elem o)
    {
        return this.value > o.value? 1 : -1;
    }
}

class List{
    private elem start = null;
    private int size;

    List() {
        this.size = 0;
    }

    public void add(int value) {
        size++;
        Elem nowy = new Elem(value);
        if (size == 1) {
            this.start = nowy;
            return;
        }
        Elem temp = this.start;
        Elem prev = null;
        while (temp.compareTo(nowy)==-1)
        {
            prev = temp;
            temp = temp.next;
            if(temp == null) break;
        }
        if(prev == null)
        {
            start = nowy;
            nowy.next = temp;
            return;
        }
        nowy.next = temp;
        prev.next = nowy;
        return;
    }

    public int pop() {
        size--;
        int exit = this.start.value;
        this.start = this.start.next;
        return exit;
    }
    public void print() {
        Elem temp = start;
        while (temp != null)
        {
            System.out.print(temp.value);
            System.out.print("  ");
            temp = temp.next;
        }
        return;
    }
}


abstract class rank implements Comparable<rank>
{
    protected String rank;
    public void print()
    {
        System.out.println(rank);
    }
}

class general extends  rank {
    general()
    {
        this.rank = "General";
    }
    public int compareTo(rank obj)
    {
        if(obj instanceof general) return 0;
        return -1 * obj.compareTo(this);
    }
}

class captain extends  rank {
    captain()
    {
        this.rank = "Captain";
    }
    public int compareTo(rank obj)
    {
        if(obj instanceof  general) return -1;
        if(obj instanceof captain) return 0;
        return -1 * obj.compareTo(this);
    }
}

class lieutenant extends  rank {
    lieutenant()
    {
        this.ranga = "Lieutenant";
    }
    public int compareTo(rank obj)
    {
        if(obj instanceof captain || obj instanceof general) return -1;
        if(obj instanceof lieutenant) return 0;
        return -1 * obj.compareTo(this);
    }
}
class priv extends  rank {
    szeregowy() { this.rank = "Private"; }
    public int compareTo(rank obj)
    {
        if(obj instanceof captain || obj instanceof general || obj instanceof lieutenant) return -1;
        if(obj instanceof priv) return 0;
        return -1 * obj.compareTo(this);
    }
}

class sergeant extends rank
{
    sergeant(){this.rank = "Sergeant"; }
    public int compareTo(ranga obj)
    {
        if(obj instanceof priv) return 1;
        if(obj instanceof captain || obj instanceof general || obj instanceof lieutenant) return -1;
        if(obj instanceof  sergeant) return 0;
        return -1 * obj.compareTo(this);
    }
}

class president extends  rank {
    president() {
        this.rank = "President";
    }

    public int compareTo(ranga obj) {
        if (obj instanceof captain || obj instanceof general || obj instanceof lieutenant) return -1;
        if (obj instanceof president) return 0;
        if (obj instanceof priv || obj instanceof sergeant) return 1;
        return -1 * obj.compareTo(this);
    }

}


public class zad1{
    public static void main(String[] args)
    {
        List x = new List();
        x.add(5);
        x.add(7);
        x.add(1);
        x.add(3);
        x.add(42);
        x.add(0);
        x.add(13);
        System.out.println("Wypisz posortowana liste");
        x.print


        List<rank> tab = new ArrayList<ranga>();
        tab.add(new priv());
        tab.add(new general());
        tab.add(new sergeant());
        tab.add(new president());
        tab.add(new captain());
        tab.add(new lieutenant());
        tab.add(new general());
        tab.add(new captain());
        tab.add(new lieutenant());
        tab.add(new priv());
        tab.add(new priv());
        tab.add(new priv());
        tab.add(new sergeant());
        tab.add(new president());
        tab.add(new sergeant());

        System.out.println("Wypisuje posortowane rangi");

        Collections.sort(tab);
        for (ranga z: tab) {
            z.print
        }
    }
    
}
