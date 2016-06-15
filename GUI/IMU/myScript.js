var testV = 0;

function myFunction(op) {
	if(op=="add")
	{
		testV++;
	}
	if(op=="minus")
	{
		testV--;
	}
	if(op=="reset")
	{
		testV=0;
	}
	document.getElementById("num").innerHTML = testV;
}

$('#plus').click(function(){
	myFunction('add');
});

$('#minus').click(function(){
	myFunction('minus');
});

$('#reset').click(function(){
	myFunction('reset');
});


var myGlobalTimer;

$('#startT').click(function(){
	var startState = document.getElementById("startT").innerHTML;
	if(startState=="Start Timer")
	{
		document.getElementById("startT").innerHTML="Stop Timer";
		myGlobalTimer = window.setInterval(timerFunction,50);
	}
	else
	{
		document.getElementById("startT").innerHTML="Start Timer";
		window.clearInterval(myGlobalTimer);
	}
});
//window.setInterval(timerFunction,50);


function timerFunction()
{
	testV++;
	//document.getElementById("num").innerHTML = testV;
	xR = xR + 10;
	xY = xY +5;
	if(xY>355)
		xY=0;
	if(xR>350)
		xR=0;
	document.getElementById("cube").style.transform = "translateZ( -100px ) rotateX("+xR+"deg) rotateY("+xY+"deg) rotateZ("+xZ+"deg)";
}

$('#sl1').on('input', function(){
	sliderFunctionX();
});

$('#sl2').on('input', function(){
	sliderFunctionY();
});

$('#sl3').on('input', function(){
	sliderFunctionZ();
});

var xR = 0;
var xY = 0;
var xZ = 0;

var myTranslate = "translateZ( 50px ) "

function sliderFunctionX() {
	xR = sl1.value;
	document.getElementById("s1").innerHTML= xR;
	//document.getElementById("cube").style.transform = myTranslate+"rotateX("+xR+"deg) rotateY("+xY+"deg) rotateZ("+xZ+"deg)"; // My inital 
	//document.getElementById("cube").style.transform = myTranslate+"rotateZ("+xZ+"deg) rotateY("+xY+"deg) rotateX("+xR+"deg) "; //My attempt at simualting roll pitch yaw, except, y is z... 
	document.getElementById("cube").style.transform = myTranslate+"rotateY("+xY+"deg) rotateX("+xR+"deg) rotateZ("+xZ+"deg)"; 
	
}

function sliderFunctionY() {
	xY = sl2.value;
	document.getElementById("s2").innerHTML= xY;
	//document.getElementById("cube").style.transform = myTranslate+"rotateX("+xR+"deg) rotateY("+xY+"deg) rotateZ("+xZ+"deg)";
	//document.getElementById("cube").style.transform = myTranslate+"rotateZ("+xZ+"deg) rotateY("+xY+"deg) rotateX("+xR+"deg) ";
	document.getElementById("cube").style.transform = myTranslate+"rotateY("+xY+"deg) rotateX("+xR+"deg) rotateZ("+xZ+"deg)";
}

function sliderFunctionZ() {
	xZ = sl3.value;
	document.getElementById("s3").innerHTML= xZ;
	//document.getElementById("cube").style.transform = myTranslate+"rotateX("+xR+"deg) rotateY("+xY+"deg) rotateZ("+xZ+"deg)";
	//document.getElementById("cube").style.transform = myTranslate+"rotateZ("+xZ+"deg) rotateY("+xY+"deg) rotateX("+xR+"deg) ";
	document.getElementById("cube").style.transform = myTranslate+"rotateY("+xY+"deg) rotateX("+xR+"deg) rotateZ("+xZ+"deg)";
}

myFunction();
