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


function* take(it, top) {
    for(var i = 0; i < top; i++)
        yield it.next().value
}

    // zwróc dokładnie 10 wartosci z potencjalnie
    // "nieskonczonego" generatora
    for (let num of take( fibgen(), 10 ) ) {
    console.log(num);
    }
    console.log()
        // zwróc dokładnie 10 wartosci z potencjalnie
    // "nieskonczonego" iteratora
    for (let num of take( fiboiter(), 10 ) ) {
        console.log(num);
        }