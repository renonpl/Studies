import java.io.*;

class Elem implements Serializable
{
    public Elem next = null;
    public int value;
    elem(int value)
    {
        this.value = value;
    }

}

class Stack implements Serializable
{
    private Elem start = null;
    private int size;
    Stack()
    {
        this.size = 0;
    }
    public void add(int value) {
        size++;
        elem newElem = new elem(value);
        if (size == 1)
        {
            this.start = newElem;
            return;
        }
        elem temp = this.start;
        while(temp.next != null) temp = temp.next;
        temp.next = newElem;
        return;
    }
    public int pop()
    {
        size--;
        int exit = this.start.value;
        this.start = this.start.next;
        return exit;
    }
    public void print()
    {
        Elem temp = start;
        while(temp != null)
        {
            System.out.println(temp.value);
            temp = temp.next;
        }
        return;
    }
    public  void save(String FileName)
    {
        try {
            FileOutputStream file = new FileOutputStream(FileName);
            ObjectOutputStream output = new ObjectOutputStream(file);
            output.writeObject(this.size);
            Elem temp = this.start;
            while (temp != null) {
                output.writeObject(temp);
                temp = temp.next;
            }
            output.close();
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
    }

    public void read(String FileName)
    {
        try {
            FileInputStream file = new FileInputStream(FileName);
            ObjectInputStream input = new ObjectInputStream(file);
            this.size = (int) input.readObject();
            elem prev = null;
            for (int i = 0; i < size; i++)
            {
                Elem temp = (Elem)input.readObject();
                if(i == 0)
                {
                    start = temp;
                    prev = temp;
                    continue;
                }
                prev.next = temp;
                prev = temp;
                continue;
            }
            input.close();
        }
        catch(IOException | ClassNotFoundException e)
        {
            e.printStackTrace();
}
    }

}

public class main{
    public static void main(String[] args)
    {
       Stack x = new Stack();
       x.add(37);
       x.add(76);
       x.add(42);
       x.add(375215);
        x.add(2);
        x.add(421551);

        System.out.println("Wypisuje");

        x.print();

       String nazwa = "heh.txt";
       x.save(nazwa);

        System.out.println("Wyzerowane x");

        x = null;
       Stack y = new Stack();
        System.out.println("Czytam z pliku");

        y.read(nazwa);
       y.print();
    }
}
