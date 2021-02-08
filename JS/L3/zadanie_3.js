function forEach(a, f)
{
    for(var i = 0; i < a.length; i++)
    {
        f(a[i])
    }
}

function map(a, f)
{
    for(var i = 0; i < a.length; i++)
    {
        a[i] = f(a[i])
    }
}

function filter(a, f)
{
    for(var i = 0; i < a.length; i++)
    {
        if(!f(a[i])) a.splice(i);
    }
}
var a = [1,2,3,4];
forEach( a, _ => { console.log( _ ); } );
// [1,2,3,4]
filter( a, _ => _ < 3 );
console.log(a);
// [1,2]
a = [1,2,3,4];
map( a, _ => _ * 2 );
console.log(a);
// [2,4,6,8]
a = [1,2,3,4];
map(a, function(x){ return x*x*x;});
console.log(a);

