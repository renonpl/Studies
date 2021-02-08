

var lista = [2];

for(var i = 3; i <= 100000; i += 2)
{
    var pierwsza = true;
    var sum = 0;
    var s = i;
    for(var j = 3; j < i; j += 2)
    {
        if(i%j == 0)
        {
            pierwsza = false;
            break; 
        }
    }
     if(pierwsza)lista.push(i);
}

console.log(lista);