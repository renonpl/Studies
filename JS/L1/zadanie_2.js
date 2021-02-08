

var lista = [];

for(var i = 1; i <= 100000; i++)
{
    var dzielna = true;
    var sum = 0;
    var s = i;
    while(s)
    {
        var d = s%10;
        sum += d;
        s = Math.floor(s/10);
        if(!d || i%d)
        {
            dzielna = false;
            break;
        }
    }
    if(dzielna && i%sum == 0) lista.push(i);
}

console.log(lista);