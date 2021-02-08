package struktury;

public class test {
    public static void main(String[] args) {
        ZbiorNaTablicy zb = new ZbiorNaTablicy(5);
        try {
            zb.wstaw(new Para("abc", 1));
            zb.wstaw(new Para("aaa", 2));
            zb.wstaw(new Para("bbb", 3));
            zb.ustaw(new Para("abc", 4));
            zb.ustaw(new Para("ccc", 5));
            System.out.println(zb.szukaj("abc").toString());
            zb.print();
            System.out.println(zb.czytaj("abc"));
            System.out.println(zb.czytaj("bbb"));
            System.out.println(zb.czytaj("ccc"));
            zb.usun("bbb");
            zb.ustaw(new Para("ddd", 50));
            zb.print();
            zb.ustaw(new Para("", 52));
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }
        ZbiorNaTablicyDynamicznej zb2 = new ZbiorNaTablicyDynamicznej();
        try {
            zb2.wstaw(new Para("abc", 1));
            zb2.wstaw(new Para("aaa", 2));
            zb2.wstaw(new Para("bbb", 3));
            zb2.ustaw(new Para("abc", 4));
            zb2.ustaw(new Para("ccc", 5));
            zb2.print();
            System.out.println(zb2.czytaj("abc"));
            System.out.println(zb2.czytaj("bbb"));
            System.out.println(zb2.czytaj("ccc"));
            zb2.ustaw(new Para("ddd", 50));
            zb2.ustaw(new Para("eee", 25));
            zb2.usun("abc");
            zb2.usun("ccc");
            zb2.usun("eee");
            zb2.print();
            zb2.usun("abc");
            zb2.usun("aaa");
            zb2.usun("bbb");
            zb2.print();
            zb2.ustaw(new Para(null, 52));
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }
    }
}
