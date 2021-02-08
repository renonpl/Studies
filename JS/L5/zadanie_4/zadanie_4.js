var http = require('http'); 
var express = require('express');
var app = express(); 


app.set('view engine', 'ejs'); 
app.set('views', './views');
app.use(express.urlencoded({extended:true}));

app.get( '/', (req, res) => {
	res.render('index',{username:'', surname:'', subject:''});  
	//res.end("Server is working"); 
}); 

const name_regex = RegExp('[A-Z][a-z]+');
//przedmiot może się składać ze słów (Wybrane elementy....) lub skrótu (WEPPO)
const subject_words_regex = RegExp('[A-Z][a-z]+{[a-z]+}*');
const subject_regex = RegExp('[A-Z]+');	
const task_regex = RegExp('[0-9]+');

app.post('/', (req, res) => {
	var username = req.body.username;
	var surname = req.body.surname;
	var subject = req.body.subject;
	if(!name_regex.test(username) || !name_regex.test(surname) ||
	 (!subject_words_regex.test(subject) && !subject_regex.test(subject) ))
	 {
		res.render('index',{username:username, surname:surname, subject:subject, err: 'Złe dane osobowe'});
		return;
	}
	//tworzy parametry get
	var taskget = '';
	for(var i = 1; i < 11; i++)
	{
		var task = req.body['z'+i];
		if(!task == '' && !task_regex.test(task)){
			res.render('index',{username:username, surname:surname, subject:subject, err: 'Złe zgłoszenie zadań'});
			return;
		}
		taskget += '&z'+ i + '=' + task;
	}
	res.redirect(`print?uname=${username}&sname=${surname}&subject=${subject}${taskget}`);
	});

app.get('/print', (req, res) => {
	res.render('print', {username:req.query.uname, surname:req.query.sname, subject:req.query.subject,
	z1:req.query.z1, z2:req.query.z2, z3:req.query.z3, z4:req.query.z4, z5:req.query.z5, z6:req.query.z6,
	z7:req.query.z7,z8:req.query.z8,z9:req.query.z9,z10:req.query.z10});
	res.end(req.query.z10);
	});
   

app.use( (err, req, res, next) => { 
	res.end( `Error handling request: ${err}`); });

http.createServer(app).listen(3000);