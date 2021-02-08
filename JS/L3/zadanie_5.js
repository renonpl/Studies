function sum()
{
    var s = 0;
    for(i = 0; i < arguments.length; i++)
    {
        s += arguments[i];
    }
    return s;
}

console.log(sum(1,2,3,4,5));
console.log(sum());
console.log(sum(-3,3,5));