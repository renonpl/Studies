function fiboiter()
{
    var _first = 0;
    var _second = 1;
    return {
        next : function(){
            var sum = _second + _first;
            var result = _first;
            _first = _second;
            _second = sum;
             return{
                   value : result,
                   done  : false
            }
        }
    }
}


var gen = fiboiter();

console.log(gen.next().value); // 0
console.log(gen.next().value); // 1
console.log(gen.next().value); // 1
console.log(gen.next().value); // 2
console.log(gen.next().value); // 3
console.log(gen.next().value); // 5

var _it = fiboiter();
/* duuzo wynikow
for ( var _result; _result = _it.next(), !_result.done; ) {
console.log( _result.value );
}*/


//to nie działa
/*
for ( var i of fiboiter() ) {
    console.log( i );
    }
*/

function *fibgen()
{
   var first = 0;
   var second = 1;
   while(true){
       yield first
       var temp = first + second;
       first = second;
       second = temp;
   }
}

var _it = fibgen();
//dużo wynikow
/*
for ( var _result; _result = _it.next(), !_result.done; ) {
console.log( _result.value );
}
*/
//dużo wyników i działa
/*
for ( var i of fibgen() ) {
    console.log( i );
    }
*/