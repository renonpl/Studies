var car = {
    _maxv : 200,

    get maxspeed(){
        return this._maxv;
    },
    set maxspeed(n){
        this._maxv = n;
    },

    startengine : function(){
        return "Brum!";
    }

}

//zwykłe dodanie pola
car.cost = 1000000;

//do właściwości get/set Object.defineProperty jest wymagane
Object.defineProperty(car,'model', {
    get : function(){
        return car._model;
    },
    set : function(s){
        car._model = s;
    }
});

//zwykłe dodanie metody
car.crash = function (){
    return "BUM!";
}

car.maxspeed = 150
console.log(car.maxspeed)
console.log(car.startengine())
console.log(car.cost)
car.model = "Ferrari";
console.log(car.model)
console.log(car.crash())

