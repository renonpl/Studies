var Foo = (function Foo(){
  var _name;

  //konstruktor
  function Foo(name){
    this._name = name;
  }

  //prywatna funkcja
  var Qux = function(){
    return "Private function";
  }

  //publiczna metoda
  Foo.prototype.Bar = function(){
    console.log(Qux());
    return "Bar " + this._name;
  }

  return Foo;

}());

var f = new Foo("Heh");
//console.log(Qux()) //-> Qux jest prywatne
//console.log(Foo.Qux());// -> to też nie zadziała
console.log(f.Bar())