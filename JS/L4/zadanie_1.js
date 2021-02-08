function Tree(val, left, right) {
    this.left = left;
    this.right = right;
    this.val = val;
}
/*
Tree.prototype[Symbol.iterator] = function*() {
    yield this.val;
    if ( this.left ) yield* this.left;
    if ( this.right ) yield* this.right;
}*/

var root = new Tree( 1,new Tree( 2, new Tree( 3 ) ), new Tree( 4 ));
var tre = new Tree(5, new Tree(3, null, new Tree(0, new Tree(10,null,null), new Tree(-1, new Tree(-100,null,null), null))), new Tree(4, null, new Tree(2,null,null)))

Tree.prototype[Symbol.iterator] = function*(){
    
    var tab = [];
    tab.splice(0,0,this)


    while(tab.length != 0){
            var nd = tab[0];
            tab.splice(0,1);
            if(nd.right)tab.splice(tab.length,0,nd.right);
            if(nd.left)tab.splice(tab.length,0,nd.left);
            yield nd.val;
        }
}

for ( var e of root ) {
    console.log( e );
}

for ( var e of tre ) {
    console.log( e );
}

//Tutaj w przypadku stosu - dostajemy przeszukiwanie wglab
Tree.prototype[Symbol.iterator] = function*(){
    
    var tab = [];
    tab.splice(0,0,this)


    while(tab.length != 0){
            var nd = tab[tab.length-1];
            tab.splice(-1,1);
            if(nd.right)tab.splice(tab.length,0,nd.right);
            if(nd.left)tab.splice(tab.length,0,nd.left);
            yield nd.val;
        }
}


for ( var e of root ) {
    console.log( e );
}

for ( var e of tre ) {
    console.log( e );
}