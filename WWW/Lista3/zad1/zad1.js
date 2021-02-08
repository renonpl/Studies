document.getElementById('anumber').addEventListener("blur",validateAccount);
document.getElementById('date').addEventListener("blur",validateDate);
document.getElementById('email').addEventListener("blur",checkMail);
document.getElementById('pesel').addEventListener("blur",checkPesel);
document.getElementById('button').addEventListener("click", checkForm);
	
		function validateAccount(){		
		debugger;
		const raccount = /^[0-9]{26}$/
		var account = document.getElementById('anumber');
		if(raccount.test(account.value)) 
		{
			account.style.backgroundColor = "white";	
			return true;
		}
		account.style.backgroundColor = "red";
		return false;

	}
	
	function validateDate(){
		debugger;
		var date = document.getElementById('date');
		var now = new Date();
		if(date.valueAsDate > now) 
		{
			date.style.backgroundColor = "red";
			return false;
		}
		date.style.backgroundColor = "white";	
		return true;
	}

	function checkMail(){
		var mail = document.getElementById('email');
		debugger;
		const rmail = /(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:(2(5[0-5]|[0-4][0-9])|1[0-9][0-9]|[1-9]?[0-9]))\.){3}(?:(2(5[0-5]|[0-4][0-9])|1[0-9][0-9]|[1-9]?[0-9])|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])/
		if(!rmail.test(mail.value)) 
		{
			mail.style.backgroundColor = "red";	
			return false;
		}
		mail.style.backgroundColor = "white";	
		return true;
	}

	function checkPesel(){		
		debugger;
		const raccount = /^[0-9]{11}$/
		var pesel = document.getElementById('pesel');
		if(!raccount.test(pesel.value)) 
		{
			pesel.style.backgroundColor = "red";
			return false;
		}
		var dig = pesel.value.substring(0,11).split('');
		var mult = [9,7,3,1,9,7,3,1,9,7]
		var sum = 0;
		for(var i = 0; i < 10; i++){
			sum += mult[i]*dig[i];
		}
		if(!(sum%10 == dig[10])){
			pesel.style.backgroundColor = "red";
			return false;
		}
		
		pesel.style.backgroundColor = "white";
		return true;

	}
	
	function checkBirt(){
		debugger
		var date = document.getElementById('date').valueAsDate;
		var pesel = document.getElementById('pesel').value;
		var year = date.getYear();
		if(year >= 100) year -= 100;
		var month = date.getMonth() + 1;
		var day = date.getUTCDate();
		
		if(year == pesel.substring(0,2) && month == pesel.substring(2,4) && day == pesel.substring(4,6))
			return true;
		alert("Pesel nie zgadza się z datą");
		return false;
	}
	
	function checkForm(){
		if(checkPesel() && checkMail && validateAccount && validateDate)
		{
			return checkBirt();
		}
		alert("Musisz wypełnić formularz poprawnie");
		return false;
	}
	