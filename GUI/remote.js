// Nathan Zimmerman
// Remote Javascript 

var Remote_Throttle_Value = 0;
var Remote_Yaw_Value=0;
var Remote_Pitch_Value =0;
var Remote_Roll_Value = 0;

var R_CAL_MM = false;
var R_CAL_MID = false;

var whoami = "none";

function updateRemoteText()
{
	document.getElementById("Throttle_Text").innerHTML= Remote_Throttle_Value;	
	document.getElementById("Yaw_Text").innerHTML= Remote_Yaw_Value;
	document.getElementById("Roll_Text").innerHTML= Remote_Roll_Value;
	document.getElementById("Pitch_Text").innerHTML= Remote_Pitch_Value;
}

function handleRemote(inputStrings)
{
	var leftStickX = 0;
	var rightStickY =0;
	var rightStickY = 0;
	var rightStickX = 0;
	newArray=inputStrings.split(',');
	Remote_Throttle_Value =newArray[1];
	Remote_Yaw_Value =newArray[2]; 
	Remote_Roll_Value = newArray[3];
	Remote_Pitch_Value=newArray[4];
	
	leftStickX =45 - Remote_Yaw_Value/(100/45); 
	leftStickY = 90 - Remote_Throttle_Value*(90/100); 
	
	rightStickX = 45 - Remote_Roll_Value/(100/45);
	rightStickY = 45 - Remote_Pitch_Value/(100/45);
	
	document.getElementById("LeftStick").style.transform ="translateX("+leftStickX+"px) translateY("+leftStickY+"px)";
	document.getElementById("RightStick").style.transform ="translateX("+rightStickX+"px) translateY("+rightStickY+"px)";
	
	updateRemoteText();
}

$('#calMid').click(function(){
	if(isConnected)
	{
		if(R_CAL_MID)
		{
			R_CAL_MID = false;
			chrome.serial.send(ConnectionData.connectionId,str2ab("R_CAL_MID,0\r"),onSend);
			document.getElementById("calMid").innerHTML= "Calibrate Midpoint";
		}
		else
		{
			document.getElementById("calMid").innerHTML= "Finish";
			chrome.serial.send(ConnectionData.connectionId,str2ab("R_CAL_MID,1\r"),onSend);
			R_CAL_MID = true;
		}
	}
});

$('#calMin').click(function(){
	if(isConnected)
	{
		if(R_CAL_MM)
		{
			R_CAL_MM = false;
			chrome.serial.send(ConnectionData.connectionId,str2ab("R_CAL_MM,0\r"),onSend);
			document.getElementById("calMin").innerHTML= "Calibrate Min/Max";
		}
		else
		{
			document.getElementById("calMin").innerHTML= "Finish";
			chrome.serial.send(ConnectionData.connectionId,str2ab("R_CAL_MM,1\r"),onSend);
			R_CAL_MM = true;
		}
	}
});

$('#saveS').click(function(){
	if(isConnected)
	{
		chrome.serial.send(ConnectionData.connectionId,str2ab("SAVE\r"),onSend);
	}
});