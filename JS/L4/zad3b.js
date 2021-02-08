module.exports = {absolute_value}

let a = require('./zad3a.js')

function absolute_value(n)
{
    if(n >= 0) return n;
    return a.change_sign(n)
}