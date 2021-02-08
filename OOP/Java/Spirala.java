public class Spirala {
        public static boolean isPrime(int n)
        {
            if(n < 2) return false;
            for(int i = 2; i <= Math.sqrt(n); i++)
                if(n%i == 0) return false;
            return true;
        }


        public static int[][]makeArray(int n)
        {
            int[][] tab = new int[n][n];
            //middlepoints
            int k = n/2;
            int j = (n-1)/2;
            tab[k][j] = 1;
            int counter = 1;
            int way = 1;
            int number = 1;
            tab[k][j] = number++;
            while(true) {
                for (int i = 0; i < counter; i++){
                    j += way;
                    tab[k][j] = number++;
                    //end of spiral is in the left top or bottom right corner, depends of n
                    if (n%2 == 0 && k == 0 && j == 0 || n%2 == 1 && k == n-1 && j == n-1) return tab;
                }
                way *= -1;
                for(int i = 0; i < counter; i++) {
                    k+= way;
                    tab[k][j] = number++;
                }
                counter++;
            }
        }


        public static void printUlam(int n)
        {
            int[][] tab = makeArray(n);

            /*
            for(int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    System.out.print(tab[i][j]);
                    System.out.print("   ");
                }
                System.out.println();
            }*/

            for(int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if(!isPrime(tab[i][j])) tab[i][j] = 0;



            for(int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if(tab[i][j] > 0) System.out.print('*');
                    else System.out.print(" ");
                }
                System.out.println();
            }
        }




        public static void main(String[] args){
            if(args.length != 1)
                throw new IllegalArgumentException("Zla ilosc argumentow!");
            int n =  Integer.parseInt(args[0]);
            if(200 < n || n < 2)
                throw new IllegalArgumentException("parametr spoza zakresu 2...200");
            printUlam(n);
        }
}
