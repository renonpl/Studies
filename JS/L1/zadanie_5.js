
function fibo_rek(n)
{
    if(n == 0 || n == 1) return n;
    return fibo_rek(n-1)+fibo_rek(n-2);
}

function fibo_iter(n)
{
    var f1 = 1;
    var f2 = 0;
    while(n)
    {
        n--;
        var temp = f2;
        f2 = f1;
        f1 = temp + f1;
    }
    return f2;
}


for(var i = 10; i < 39; i++)
{
    console.log("n = " + i);
    console.time("Rek:");
    var temp = fibo_rek(i);
   // console.log("Wynik " + temp);
    console.timeEnd("Rek:");
    console.time("Iter:");
     temp = fibo_iter(i);
    // console.log("Wynik " + temp);
    console.timeEnd("Iter:");
}