const readline = require('readline');
const fs = require('fs');

const rl = readline.createInterface({
    input: fs.createReadStream("log.txt"),
    output: process.stdout
  });

  

  var iplist = {};
  rl.on('line', function (line) {
      var str = line.split(' ')
      if(iplist[str[1]] == undefined ) iplist[str[1]] = 0;
      iplist[str[1]]++;
  });

  rl.on('close', function(){
     // console.log(iplist)
        findMax(iplist)
        findMax(iplist)
        findMax(iplist)
    })


    function findMax(dict){
        var str, count = 0;
        for(let ip in dict){
            if(count < dict[ip]){
                count = dict[ip]
                str = ip
            }
        }
        delete dict[str]
        console.log(str)
    }