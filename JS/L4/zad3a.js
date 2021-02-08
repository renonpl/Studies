module.exports = {change_sign}

//odwoływanie się wzajemne jest możliwe
let b = require('./zad3b.js')


function change_sign(n)
{
    return n * -1;
}

console.log(b.absolute_value(-500));