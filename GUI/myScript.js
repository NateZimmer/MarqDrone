
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
	var myStrings = testV.toString();
	
	chrome.storage.local.set({'testStorage':myStrings});
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


$('#testFileSystemWrite').click(function(){
	
chrome.fileSystem.chooseEntry({type: 'saveFile'}, function(writableFileEntry) {
    writableFileEntry.createWriter(function(writer) {
      writer.onerror = function(e) {
		  console.log('something went wrong!');
	  };
      writer.onwriteend = function(e) {
        console.log('write complete');
      };
      writer.write(new Blob(['1234567890'], {type: 'text/plain'}));
    }, errorHandler);
});
});


/*

chrome.fileSystem.chooseEntry(
 {
 type: 'openFile', accepts:[{
 extensions: ['html']
 }] 
 }, 
 function(fileEntry) {
 if (!fileEntry) {
$("#OuptutText").html("User did not choose a file");
 return;
 }
 fileEntry.file(function(file) {
 var reader = new FileReader();
 reader.onload = function(e) {
 document.getElementById("HTMLFile").value = e.target.result;
 };
 reader.readAsText(file);
 });

});
*/

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

$(function() {
	$( "#serialComs" ).resizable();
});
$(function() {
	$( "#KPlot" ).resizable({ handles: "se"});
});

$(function() {
	$( "#GyroPlot" ).resizable({ handles: "se"});
});

$(function() {
	$( "#AccPlot" ).resizable({ handles: "se"});
});


$('#AccPlot').on('resize', function(){
	var Xsize = parseInt(document.getElementById("AccPlot").style.width,10)-20;
	var Ysize = parseInt(document.getElementById("AccPlot").style.height,10)-50;
	document.getElementById("myPlot").style.width=Xsize.toString()+"px";
	document.getElementById("myPlot").style.height=Ysize.toString()+"px";
	generatePlot(myArray,myPlot,acc_options,3);
});


$('#GyroPlot').on('resize', function(){
	var Xsize = parseInt(document.getElementById("GyroPlot").style.width,10)-20;
	var Ysize = parseInt(document.getElementById("GyroPlot").style.height,10)-50;
	document.getElementById("gyroP").style.width=Xsize.toString()+"px";
	document.getElementById("gyroP").style.height=Ysize.toString()+"px";
	generatePlot(gyroArray,gyroP,gyro_options,3);
});

$('#KPlot').on('resize', function(){
	var Xsize = parseInt(document.getElementById("KPlot").style.width,10)-20;
	var Ysize = parseInt(document.getElementById("KPlot").style.height,10)-50;
	document.getElementById("kP").style.width=Xsize.toString()+"px";
	document.getElementById("kP").style.height=Ysize.toString()+"px";
	generatePlot(kArray,kP,k_options);
});


$(function() {
	$( "#MotorPlot" ).resizable({ handles: "se"});
});

$('#MotorPlot').on('resize', function(){
	var Xsize = parseInt(document.getElementById("MotorPlot").style.width,10)-20;
	var Ysize = parseInt(document.getElementById("MotorPlot").style.height,10)-50;
	document.getElementById("motorP").style.width=Xsize.toString()+"px";
	document.getElementById("motorP").style.height=Ysize.toString()+"px";
	generatePlot(speedArray,motorP,all_options,4);
});


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
