function addSelects()
{
	var x = document.getElementById("portPath");
	var option = document.createElement("option");
	chrome.serial.getDevices(function(ports) {
		 for (var i = 0; i < ports.length; i++) {
			 var option = document.createElement("option");
			 option.text = ports[i].path;
			 x.add(option);
		 }
	});

}
addSelects();

var stringFile =[];

var ConnectionData;

var Remote_Connected = false;

var _options = {
  bitrate: 115200,
};

var isConnected=false;

var str2ab = function(str) {
  var encodedString = unescape(encodeURIComponent(str));
  var bytes = new Uint8Array(encodedString.length);
  for (var i = 0; i < encodedString.length; ++i) {
    bytes[i] = encodedString.charCodeAt(i);
  }
  return bytes.buffer;
};

var ab2str = function(buf) {
  var bufView = new Uint8Array(buf);
  var encodedString = String.fromCharCode.apply(null, bufView);
  return decodeURIComponent(escape(encodedString));
};

function onConnect(connectionInfo)
{
	ConnectionData = connectionInfo;
	console.log("Callback function");
	console.log(ConnectionData);
	if(ConnectionData.connectionId>0)
	{
		document.getElementById("connect").innerHTML="Disconnect";
		chrome.serial.onReceive.addListener(getData);
		isConnected=true;
	}
}

var lines='';
var serialLogging=false;

$('#logSerialCheck').on('change', function(){
	if(logSerialCheck.checked)
	{
		serialLogging=true;
	}
	else
	{
		serialLogging=false;
	}
});

$('#logSerialCheck').on('change', function(){
	if(logSerialCheck.checked)
	{
		serialLogging=true;
	}
	else
	{
		serialLogging=false;
	}
});

function handleLogging(inputData)
{
	if(serialLogging)
	{
		RecievedData +=inputData;
		$("#textBox").val(RecievedData); // This updates the text box
		textBox.scrollTop = textBox.scrollHeight;
	}
}

function onSend(sendInfo)
{
	//console.log(sendInfo);
}

function onClose(result)
{
	
}

$('#connect').click(function(){
	var ConnectString = document.getElementById("portPath").value;
	
	var connectState = document.getElementById("connect").innerHTML;
	if(connectState=="Connect")
	{
		console.log("Connecting to "+ConnectString);
		_options.bitrate=parseInt(baudRates.value);
		chrome.serial.connect(ConnectString,_options,onConnect);
		//chrome.serial.send(ConnectionData.connectionId,str2ab("WHO_AM_I\r"),onSend);
	}
	else
	{
		document.getElementById("connect").innerHTML="Connect";
		chrome.serial.onReceive.removeListener(getData);
		chrome.serial.disconnect(ConnectionData.connectionId, onClose);
		isConnected = false;
	}
});


function getSerialConnections(connections)
{
	//console.log(connections);
}

var RecievedData="";
var accTimer;

$('#sendData').click(function(){
	var startState = document.getElementById("sendData").innerHTML;
	if(startState=="Start Timer")
	{
		document.getElementById("sendData").innerHTML="Stop Timer";
		accTimer = window.setInterval(checkAcc,15);
	}
	else
	{
		document.getElementById("sendData").innerHTML="Start Timer";
		window.clearInterval(accTimer);
	}
});


var local_test = 0;


var FunctionList = [];

var Ok_To_Update_Motor = false;
var MAG_ENABLED = false;
var MOTOR_SPEED_COLLECTION = true;



function checkAcc()
{
	checkvar =local_test%6; 
	if(checkvar==0)
	{
		chrome.serial.send(ConnectionData.connectionId,str2ab("GET_ACC\r"),onSend);
		samples++;
	}
	else if(checkvar==1)
	{
		chrome.serial.send(ConnectionData.connectionId,str2ab("GET_GYRO\r"),onSend);
		gsamples++;
	}
	else if(checkvar==2)
	{
		if(document.getElementById('manualMotorSpeed').checked) // ignore mag data if in manual motor mode 
		{
			Manual_Motor_Mode_Update_Speeds();
		}
		else if(MAG_ENABLED)
		{
			chrome.serial.send(ConnectionData.connectionId,str2ab("GET_MAG\r"),onSend);
			msamples++;
		}
		else if(MOTOR_SPEED_COLLECTION)
		{
			chrome.serial.send(ConnectionData.connectionId,str2ab("GET_MTR\r"),onSend); // get drone motor speeds if ignoring mag data 
			speedSamples++;	
		}
		
	}
	else if(checkvar==3)
	{
		chrome.serial.send(ConnectionData.connectionId,str2ab("GET_K\r"),onSend);
		ksamples++;
	}
	else if(checkvar==4)
	{
		if(Remote_Connected)
		{
			chrome.serial.send(ConnectionData.connectionId,str2ab("GET_R\r"),onSend);
		}
		
	}
	else if(checkvar==5)
	{
		handleMetaDataCollection();
	}
	Ok_To_Update_Motor = true;
	local_test++;
}

var lastCharPressed="";

$(document).keypress(function(event){
    lastCharPressed =String.fromCharCode(event.which); 
 })

$('#textBox').on('input', function(){
	var inputString = textBox.value; 
	var inputStringLength = textBox.value.length;
	var bufferLength = RecievedData.length;
	var sendString = lastCharPressed; 
	if(isConnected)
	{
		if(serialLogging)
		{
			console.log("Sending: " + sendString);
			$("#textBox").val(RecievedData);
			chrome.serial.send(ConnectionData.connectionId,str2ab(sendString),onSend);
			console.log("Removed Typed Data");
		}
	}
	else
	{
		$("#textBox").val('');
	}

});




