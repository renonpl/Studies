document.getElementById('dodaj').addEventListener("click",addposition);
document.getElementById('marka').addEventListener("change", loadModels);

window.onload =
	function(){
		addbrand("Ford");
		addmodel("Fiesta");
		addmodel("Focus");
		addbrand("Fiat");
		chooseSec();
		addmodel("500");
		addmodel("Panda");
		loadModels();
	}


var list_data = 
{
}

function chooseSec(){
	var sel = document.getElementById('marka');
	sel.value = "Fiat";
}

function loadModels(){
	debugger;
	var mar = document.getElementById('marka').value;
	var mod = document.getElementById('model');
	for(var i = mod.length; i; i--){
		mod.removeChild(mod[i-1]);
	}
	for(var i = 0; i < list_data[mar].length; i++){
		var opt = document.createElement('option');
		opt.text = list_data[mar][i];
		mod.add(opt);
	}
	
}

function addbrand(name){
	debugger;
	if(list_data[name]) return;
	var sel = document.getElementById('marka');
	var opt = document.createElement('option');
	opt.text = name;
	sel.add(opt);
	list_data[name] = [];
}

function addmodel(name){
	debugger;
	var brand = document.getElementById('marka').value;
	if(list_data[brand].includes(name)) return;
	var sel = document.getElementById('model');
	var opt = document.createElement('option');
	opt.text = name;
	sel.add(opt);
	list_data[brand].push(name)
}

function addposition(){
	debugger;
	var newpos = document.getElementById('nowa');
	if (document.getElementById('rodzaj1').checked)
		addmodel(newpos.value);		
	else
		if(document.getElementById('rodzaj2').checked)
			addbrand(newpos.value);
}