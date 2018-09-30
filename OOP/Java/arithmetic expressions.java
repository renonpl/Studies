import java.io.*;

abstract class Expression
{
    protected Expression left;
    protected Expression right;
    public abstract int calculate();
    public abstract String toString();
}

class Root extends Expression
{
    private char operator;
    Root(char operator, Root left, Root right)
    {
        this.operator = operator;
        this.left = left;
        this.right = right;
    }
    public int calculate()
    {
        switch (operator) {
            case '*':
                return prawa.calculate() * lewa.calculate();
            case '+':
                return prawa.calculate() + lewa.calculate();
            case '-':
                return prawa.calculate() - lewa.calculate();
            case '/':
                return prawa.calculate() / lewa.calculate();
            default:
                return 0;
        }
    }
    public String toString()
    {
        return "(" + right.toString() + operator + left.toString() + ")";
    }
}

class Leaf extends Expression
{
    private int value;
    private String tag = "";
    private int[] hashtab;
    private int size;
    Lisc(int value)
    {
        this.wart = value;
        this.lewa = null;
        this.prawa = null;
    }
    Leaf(String tag, int[] tab, int size)
    {
        this.tag = tag;
        this.hashtab = tab;
        this.size = size;
        this.left = null;
        this.right = null;
    }
    public int calculate()
    {
        if(tag == "") return value;
        return hashtab[zmienna.hashCode()%size];
    }

    public String toString()
    {
       return Integer.toString(this.calculate());
    }
}

public class Main{
    public static void main(String[] args)
    {
        int[] hashtab = new int[10];
        for (int i = 0; i < 10; i++)
        {
            hashtab[i] = i+7*24;
        }
        Root root = new Root('+',new Root('*', new Leaf(7), new Leaf (12)), new Leaf(13));
        System.out.println(root.calculate());
        System.out.println(root.toString());
        Root root2 = new Root('+',new Root('*', new Leaf(7), new Leaf (12)), new Root('/', new Leaf("adz",hashtab,10), new Leaf("x",hashtab,10)));
        System.out.println(root2.calculate());
        System.out.println(root2.toString());
    }
}
