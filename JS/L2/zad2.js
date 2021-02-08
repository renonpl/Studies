var pizza = {
    toppings: ['cheese', 'sauce', 'pepperoni'],
    crust: 'deep dish',
    serves: 2 
}

console.log(pizza)
console.log(pizza.crust)
console.log(pizza['crust'])
console.log(pizza.toppings)
console.log(pizza['toppings'])

console.log(pizza[0])
console.log(pizza[1])

pizza[1] = 3
console.log(pizza[0])
console.log(pizza[1])
console.log(pizza)

var pizza2 = {
    toppings: ['ham', 'ananas', 'pepperoni'],
    crust: 'soft dish',
    serves: 1,
    toString: function()
    {
        return 'ppppp'
    }
}

console.log('Testy')
console.log( pizza2.toString() );

console.log(pizza[pizza2])
pizza[pizza2] = 'cos'
console.log(pizza[pizza2])

var keys = Object.keys(pizza);
console.log( keys );



var tab = [1,2,3]
console.log(tab[1])
console.log("Tab od napisu 1")
console.log(tab['hah'])
tab['hah'] = 5
tab['hahaa'] = 5
console.log(tab)
console.log(tab[3])
console.log("Tab od napisu 2")
console.log(tab['hah'])
console.log("Tab od obiektu")
console.log(tab[pizza])
tab[pizza] = 3
tab[pizza2] = 7
console.log("Tab od obiektu 2")
console.log(tab)
console.log(tab[pizza])
console.log(tab[pizza2])
console.log(tab[5])
console.log(tab[6])

console.log(tab.length)
tab.length = 10
console.log(tab)
tab.length = 2
console.log(tab)