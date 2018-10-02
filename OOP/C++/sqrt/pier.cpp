#include"pier.h"

int64_t string_to_int(string a)
{
    int i = 0;
    while(a[i] != 0)
    {
        if(a[i] < '0' || a[i] > '9')
        {
            if(a[i] == '-' && i == 0)
            {
                i++;
                continue;
            }
            cerr << "Argument nie jest liczba " << a << endl;
            return 0;
        }
        i++;
    }
    i = 0;
    int sign = 1;
    int64_t result = 0;
    if(a == "-9223372036854775808") return -9223372036854775808;
    while(a[i] != 0)
    {
        if(a[i] == '-' && i == 0) sign = -1;
        else
        {
            int64_t last_result = result;
            result = result*10+ (a[i] - '0');
                            //if((result - (a[i] - '0')) == (1<<63)/10*(-1)) return result;

            if((result > 0 && last_result < 0) || (result < 0 && last_result > 0))
            {
                cerr << "Argument wykracza poza zakres  " << a << endl;
                return 0;
            }
        }
        i++;
     //   cout << "  To  " << result << " ZNak =  " << sign;
    }
    return sign*result;
}


vector<int64_t> prime_numbers(int64_t a)
{
    //cout << "TO JEST LICZBA  " << a << endl;
    vector<int64_t> result;
    if(a == 0 || a == 1)
    {
        result.push_back(a);
        return result;
    }
    if(a < 0)
    {
        result.push_back(-1);
        if(a == (-9223372036854775808))
        {
            result.push_back(2);
            a = a/2;
        }
        a = a * (-1);
    }
    if(is_prime(a))
    {
      //  cout << "hahh" << a << endl;
        result.push_back(a);
        return result;
    }
    for(int i = 2; i <= a; i++)
    {
        while(a%i == 0)
        {
            result.push_back(i);
            a /= i;
        }
    }
    return result;
}

bool is_prime(int64_t a)
{
    int64_t temp = sqrt(a);
    for(int64_t i = 2; i <= temp; i++)
    {
        if(a % i == 0) return 0;
    }
    return 1;
}



void print_primes(vector<int64_t> tab)
{
    int i = 1;
    for(int64_t &t:tab)
    {
        if(i == 1)
        {
            i = 0;
        }
        else
        {
            cout << " * ";
        }
        cout << t;
    }
    return;
}


void read(int argc, char** argv)
{
    if(argc == 1)
    {
        cerr << "Prosze podac liczby do rozkladu na czynniki pierwsze";
        return;
    }
    for(int i = 1; i < argc; i++)
    {
        string temp(argv[i]);
        int64_t temp_number = string_to_int(temp);
        if(temp_number == 0 && temp[0] != '0') continue;
        cout << temp_number << " = ";
        print_primes(prime_numbers(temp_number));
        cout << endl;
    }
    return;
}
