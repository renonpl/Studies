function createGenerator(limit) 
{
    var _state = 0;
    return {
        next : function() 
        {
            return _state > limit?
            {done:true} :
            {
                value : _state++,
                done : false
            };
        }
    }
}

var foo = {[Symbol.iterator] : createGenerator.bind(this,100)};
for ( var f of foo ) console.log(f);
var foo2 = {[Symbol.iterator] : createGenerator.bind(this,10)};
for ( var f of foo2 ) console.log(Math.pow(2,f));
var foo3 = {[Symbol.iterator] : createGenerator.bind(this,20)};
for ( var f of foo3 ){
    if(f%2 == 0)
        console.log(f);
};