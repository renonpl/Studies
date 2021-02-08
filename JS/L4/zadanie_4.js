console.log("Podaj imie")
process.stdin.once('readable', () => {
  var input = process.stdin.read();
  console.log("Witaj " + input);
});